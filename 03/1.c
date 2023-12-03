#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int d1[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int d2[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
  char buf[1024][1024];
  int r = 1; // rows
  int sum = 0;
  while (1) {
    char line[1024];
    fgets(line, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    memcpy(buf[r++] + 1, line, 1024);
  }
  int c = strlen(buf[1] + 1) + 1;
  for (int i = 1; i < r; i++) {
    for (int j = 1; j < c; j++) {
      int include = 0;
      int total = 0;
      while (isdigit(buf[i][j])) {
        total *= 10;
        total += buf[i][j] - '0';
        for (int k = 0; k < 8; k++) {
          char adj = buf[i + d1[k]][j + d2[k]];
          if (!isdigit(adj) && adj != '.' && adj != '\0' && adj != '\n') {
            include = 1;
          }
        }
        j++;
      }
      if (include) {
        sum += total;
      }
    }
  }
  printf("%d\n", sum);
  return 0;
}
