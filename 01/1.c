#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int sum = 0;
  char c;
  while (c != EOF) {
    int first = -1;
    int last = -1;
    while ((c = fgetc(stdin)) != 10 && c != EOF) {
      int i = c - 48;
      if (i < 0 || i > 9)
        continue;
      if (first == -1) {
        first = i;
      }
      last = i;
    }
    if (first != -1) {
      sum += 10 * first;
      sum += last;
    }
  }
  printf("%d\n", sum);
}
