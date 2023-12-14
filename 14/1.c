#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int sum = 0;
  char b[1024][1024];
  int rc = 0;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    memcpy(b[rc++], buf, 1024);
  }
  int cc = strlen(b[0]) - 1;
  for (int k = 0; k < rc; k++) {
    for (int i = 1; i < rc; i++) {
      for (int j = 0; j < cc; j++) {
        if (b[i - 1][j] == '.' && b[i][j] == 'O') {
          b[i - 1][j] = 'O';
          b[i][j] = '.';
        }
      }
    }
  }
  for (int i = 0; i < rc; i++) {
    for (int j = 0; j < cc; j++) {
      if (b[i][j] == 'O') {
        sum += rc - i;
      }
    }
  }
  printf("%d\n", sum);
  return 0;
}
