#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOWER 1024
#define UPPER 65536

FILE *fptr;
const char *INPUT_FILE = "input.txt";

char *getInput() {
  if ((fptr = fopen(INPUT_FILE, "r")) == NULL) {
    perror("fopen");
    exit(1);
  };

  size_t increase = LOWER;
  size_t allocated = increase;
  char *string = malloc(allocated);
  size_t total = 0;

  while (!feof(fptr) && !ferror(fptr)) {
    string[total] = fgetc(fptr);
    total++;
    if (total >= allocated) {
      if (increase >= UPPER)
        increase = UPPER;

      allocated += increase;

      string = realloc(string, allocated);

      increase *= 2;
    };
  }
  if (ferror(fptr)) {
    perror("ferror");
    exit(1);
  }

  string = realloc(string, total);
  string[total - 1] = '\0';
  return string;
}

int validateID(int id) {
  char *s_id = malloc(LOWER);
  sprintf(s_id, "%d", id);
  int idlen = strlen(s_id);
  if (idlen == 1 || idlen % 2 != 0) {
    return 0;
  };

  if (s_id[0] == '0') {
    return 1;
  };
  int digits_qtd = idlen / 2;
  char *first_half = malloc(digits_qtd + 1);
  char *second_half = malloc(digits_qtd + 1);
  int id_i = 0;
  int half_i = 0;

  while (half_i < digits_qtd) {
    first_half[half_i] = s_id[id_i];
    half_i++;
    id_i++;
  };
  half_i = 0;
  while (half_i < digits_qtd) {
    second_half[half_i] = s_id[id_i];
    half_i++;
    id_i++;
  };

  if (atoi(first_half) == atoi(second_half)) {
    free(first_half);
    free(second_half);
    return 1;
  };
  return 0;
}

void makeRangeArray(int init, int end, int *arr) {
  int total = end - init + 1;
  int curr = init;
  for (int i = 0; arr[total - 1] != end; i++) {
    arr[i] = curr;
    curr += 1;
  };
}


int main() {
  char *input = getInput();
  size_t increase = LOWER;
  size_t allocated = increase;
  char *init = malloc(allocated);
  char *end = malloc(allocated);

  char *current = init;
  size_t index = 0;
  int curr_index = 0;
  int total_sum = 0;
  while (0 == 0) {
    char curr_c = input[index];
    if (index >= allocated) {
      if (increase >= UPPER)
        increase = UPPER;

      allocated += increase;
      increase *= 2;

      current = realloc(current, allocated);
    };

    if (curr_c == '-') {
      init = strcpy(init, current);
      curr_index = 0;
      free(end);
      end = malloc(allocated);
      current = end;
    } else if (curr_c == ',' || curr_c == '\0') {
      end = strcpy(end, current);
      curr_index = 0;
      int i_init = atoi(init);
      int i_end = atoi(end);
      printf("init: %d\tend: %d\n", i_init, i_end);
      int total = i_end - i_init + 1;
      int range[total];

      makeRangeArray(i_init, i_end, range);
      for (int i = 0; i + 1 < total; i++) {
        int result = validateID(range[i]);
        if (result != 0) {
          total_sum += range[i];
        };
      };

      free(init);
      init = malloc(allocated);
      current = init;
    } else {
      current[curr_index] = curr_c;
      curr_index += 1;
    }

    if (curr_c == '\0') {
      free(init);
      free(end);
      free(input);
      break;
    }
    index += 1;
  }

  printf("total sum: %d\n", total_sum);

  return 0;
}
