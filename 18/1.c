#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char trench[1024][1024];

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

const int dr2[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc2[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int ldir(char l) {
  switch (l) {
  case 'U':
    return 0;
  case 'R':
    return 1;
  case 'D':
    return 2;
  case 'L':
    return 3;
  }
  return -1;
}

int main(void) {
  int sum = 0;
  memset(trench, '.', 1024 * 1024);
  int r = 261 + 401;
  int c = 208 - 135;
  int minr = 1024;
  int minc = 1024;
  int mr = 0;
  int mc = 0;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    char *dir = strtok(buf, " ");
    int d = ldir(dir[0]);
    int amt = strtol(strtok(NULL, " "), NULL, 10);
    for (int i = 0; i < amt; i++) {
      r += dr[d];
      c += dc[d];
      trench[r][c] = '#';
      if (r <= minr)
        minr = r;
      if (r >= mr)
        mr = r + 1;
      if (c <= minc)
        minc = c;
      if (c >= mc)
        mc = c + 1;
    }
  }
  for (int i = minr; i < mr; i++) {
    int brk = 0;
    for (int j = minc; j < mc; j++) {
      if (trench[i][j] == '.') {
        trench[i][j] = 'A';
        brk = 1;
        break;
      }
    }
    if (brk) {
      break;
    }
  }
  minr--;
  minc--;
  mr++;
  mc++;
  while (1) {
    int change = 0;
    for (int i = minr; i < mr; i++) {
      for (int j = minc; j < mc; j++) {
        for (int k = 0; k < 8; k++) {
          int nr = i + dr2[k];
          int nc = j + dc2[k];
          if (trench[nr][nc] == 'A' && trench[i][j] == '.') {
            trench[i][j] = 'A';
            change = 1;
            break;
          }
        }
      }
    }
    if (!change) {
      break;
    }
  }
  int a = 0;
  int dot = 0;
  int hash = 0;
  for (int i = minr; i < mr; i++) {
    int astart = a;
    int dstart = dot;
    int hstart = hash;
    for (int j = minc; j < mc; j++) {
      if (trench[i][j] == '.') {
        dot++;
      }
      if (trench[i][j] == 'A') {
        a++;
      }
      if (trench[i][j] == '#') {
        hash++;
      }
    }
  }
  printf(".: %d, A: %d\n", dot + hash, a + hash);
}
