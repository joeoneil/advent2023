#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  long sum = 0;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    int history[64][64];
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 64; j++) {
        history[i][j] = 0;
      }
    }
    int c = 0;
    char *s = strtok(buf, " ");
    history[0][c++] = strtol(s, NULL, 10);
    while ((s = strtok(NULL, " "))) {
      history[0][c++] = strtol(s, NULL, 10);
    }
    int i = 1;
    for (;;) {
      for (int j = 0; j < c - i; j++) {
        history[i][j] = history[i - 1][j + 1] - history[i - 1][j];
      }
      int all_zero = 1;
      for (int j = 0; j < 64; j++) {
        if (history[i][j]) {
          all_zero = 0;
        }
      }
      if (all_zero) {
        break;
      }
      i++;
    }
    int predict = 0;
    for (int i = c - 1; i >= 0; i--) {
      predict *= -1;
      predict += history[i][0];
    }
    sum += predict;
  }
  printf("%ld\n", sum);
}
