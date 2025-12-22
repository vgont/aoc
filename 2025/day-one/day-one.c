#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr;
const char *INPUT_FILE = "input.txt";
const int STRING_SIZE = 100;

enum Side { L, R };

struct Action {
  enum Side side;
  int value;
};

struct Action getAction(char *input) {
  char side = input[0];
  struct Action action;
  switch (side) {
  case 'L':
    action.side = L;
    break;
  case 'R':
    action.side = R;
    break;
  default:
    return action;
  };

  char *str_value;
  str_value = malloc(2);
  strcpy(str_value, &input[1]);
  strcat(str_value, &input[2]);

  action.value = atoi(str_value);

  free(str_value);
  return action;
}

int eval(int dial, struct Action action) {
  int i;
  if (action.side == L) {
    printf("Result of %d-%d: ", dial, action.value);
    for (i = 0; i < action.value; i++) {
      dial -= 1;
      if (dial == -1) {
        dial = 99;
      };
    };
  } else {
    printf("Result of %d+%d: ", dial, action.value);
    for (i = 0; i < action.value; i++) {
      dial += 1;
      if (dial == 100) {
        dial = 0;
      };
    };
  }
  printf("%d\n", dial);
  return dial;
}

int main() {
  fptr = fopen(INPUT_FILE, "r");
  int dial = 50;
  int password = 0;

  char content[STRING_SIZE];
  int line = 1;
  while (fgets(content, STRING_SIZE, fptr)) {
    printf("current line: %d\n", line);
    struct Action act = getAction(content);
    if (act.side != L && act.side != R) {
      printf("Invalid side on line %d\npossible values: 'L' or 'R'\n", line);
      return 1;
    }
    dial = eval(dial, act);
    if (dial == 0)
      password += 1;
    line += 1;
  }

  printf("password is: %d\n", password);

  fclose(fptr);

  return 0;
}
