#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADJ buf[i + d1[k]][j + d2[k] + offset]
#define ROW (i + d1[k])
#define COL (j + d2[k])

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
      if (buf[i][j] == '*') {
        int n1 = 0, n1r = 0, n1c = 0, n2 = 0, n2r = 0, n2c = 0;
        int skip = 0;
        for (int k = 0; k < 8; k++) {
          int offset = 0;
          char adj = ADJ;
          if (!isdigit(adj))
            continue;

          while (isdigit(adj = ADJ)) {
            offset--;
          };
          offset++;
          int num = strtol(&buf[ROW][COL + offset], NULL, 10);
          if (!n1) {
            n1 = num;
            n1r = ROW;
            n1c = COL + offset;
          } else if ((ROW != n1r || COL + offset != n1c) && !n2) {
            n2 = num;
            n2r = ROW;
            n2c = COL + offset;
          } else if ((ROW != n2r || COL + offset != n2c) && n1 && n2) {
            skip = 1;
          }
        }
        if (!skip) {
          sum += n1 * n2;
        }
      }
    }
  }
  printf("%d\n", sum);
  return 0;
}
