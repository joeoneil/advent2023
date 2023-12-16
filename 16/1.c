#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int dr[] = {-1, 0, 1, 0}; // NESW
const int dc[] = {0, 1, 0, -1}; // NESW
const char *dname[] = {"NORTH", "EAST", "SOUTH", "WEST"};
const int fref[] = {1, 0, 3, 2};
const int bref[] = {3, 2, 1, 0};

#define ROW br[i]
#define COL bc[i]
#define DIR bd[i]
#define B buf[ROW][COL]

int newdir(int dir, char tile) {
  switch (tile) {
  case '/':
    return fref[dir];
  case '\\':
    return bref[dir];
  case 'O':
    return -1;
  }
  return dir;
}

int split(int dir, char tile) {
  switch (tile) {
  case '-':
    if (dir == 0 || dir == 2) {
      return 1;
    }
    break;
  case '|':
    if (dir == 1 || dir == 3) {
      return 1;
    }
    break;
  }
  return 0;
}

int main(void) {
  char buf[1024][1024];
  int en[128][128];
  memset(en, 0, sizeof(int) * 128 * 128);
  en[0][0] = 1;
  int br[1024];
  int bc[1024];
  int bd[1024];
  bd[0] = 1;
  br[0] = 0;
  bc[0] = 0;
  int rc = 0;
  while (1) {
    char l[1024];
    fgets(l, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    strcpy(buf[rc++], l);
  }
  int cc = strlen(buf[0]) - 1;

  int beams = 1;
  int active[1024];
  active[0] = 1;
  while (1) {
    for (int i = 0; i < rc; i++) {
      for (int j = 0; j < cc; j++) {
        if (buf[i][j] == '2') {
          buf[i][j] = '1';
        } else if (buf[i][j] == '1') {
          buf[i][j] = 'O';
        }
      }
    }
    for (int i = 0; i < beams; i++) {
      if (!active[i]) {
        continue;
      }
      DIR = newdir(DIR, B);
      ROW += dr[DIR];
      COL += dc[DIR];
      if (DIR == -1) {
        active[i] = 0;
        continue;
      }
      if (br[i] >= rc || bc[i] >= cc || br[i] < 0 || bc[i] < 0) {
        active[i] = 0;
        continue;
      }
      if (split(DIR, B)) {
        en[ROW][COL] = 1;
        buf[ROW][COL] = '2'; // splitter should only hit once
        en[ROW][COL] = 1;
        bd[beams] = (DIR + 3) % 4;
        br[beams] = ROW;
        bc[beams] = COL;
        active[beams] = 1;
        DIR = (DIR + 1) % 4;
        beams++;
        continue;
      }
      en[ROW][COL] = 1;
    }
    int brk = 1;
    for (int i = 0; i < beams; i++) {
      if (active[i]) {
        brk = 0;
      }
    }
    if (brk)
      break;
  }

  int sum = 0;
  for (int i = 0; i < rc; i++) {
    for (int j = 0; j < cc; j++) {
      if (en[i][j]) {
        sum++;
      }
    }
  }
  printf("%d\n", sum);
}
