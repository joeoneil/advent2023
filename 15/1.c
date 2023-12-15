#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int sum = 0;
  unsigned char h = 0;
  char c;
  while ((c = fgetc(stdin))) {
    if (feof(stdin)) {
      break;
    }
    if (c == '\n') {
      continue;
    }
    if (c == ',') {
      sum += h;
      h = 0;
    } else {
      h += c;
      h *= 17;
    }
  }
  sum += h;
  printf("%d\n", sum);
}
