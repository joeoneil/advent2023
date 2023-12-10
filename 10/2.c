#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NS '|'
#define EW '-'
#define NE 'L'
#define NW 'J'
#define SW '7'
#define SE 'F'
#define GND '.'
#define S 'S'

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

const int left[4] = {3, 0, 1, 2};
const int right[4] = {1, 2, 3, 0};
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void travel(int dir, int *x, int *y) {
  switch (dir) {
  case NORTH:
    (*y)--;
    break;
  case EAST:
    (*x)++;
    break;
  case SOUTH:
    (*y)++;
    break;
  case WEST:
    (*x)--;
    break;
  }
}

int new_dir(int dir, char pipe) {
  switch (pipe) {
  case NS:
    if (dir == NORTH) {
      return NORTH;
    } else if (dir == SOUTH) {
      return SOUTH;
    }
    break;
  case EW:
    if (dir == EAST) {
      return EAST;
    } else if (dir == WEST) {
      return WEST;
    }
    break;
  case NE:
    if (dir == SOUTH) {
      return EAST;
    } else if (dir == WEST) {
      return NORTH;
    }
    break;
  case NW:
    if (dir == SOUTH) {
      return WEST;
    } else if (dir == EAST) {
      return NORTH;
    }
    break;
  case SW:
    if (dir == NORTH) {
      return WEST;
    } else if (dir == EAST) {
      return SOUTH;
    }
    break;
  case SE:
    if (dir == NORTH) {
      return EAST;
    } else if (dir == WEST) {
      return SOUTH;
    }
    break;
  }
  return -1;
}

int main(void) {
  char grid[1024][1024];
  int rows = 0;
  while (1) {
    fgets(grid[rows++] + 1, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
  }
  int cols = strlen(grid[0] + 1);
  int sx = 0, sy = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == S) {
        sx = j;
        sy = i;
      }
    }
  }
  int realdir = 0;
  for (int i = 0; i < 4; i++) {
    int dir = i;
    int x = sx;
    int y = sy;
    int steps = 0;
    while (1) {
      // printf("@%d, %d (%c) dir %d -> ", x, y, grid[y][x], dir);
      travel(dir, &x, &y);
      dir = new_dir(dir, grid[y][x]);
      // printf("@%d, %d (%c) dir %d\n", x, y, grid[y][x], dir);
      steps++;
      if (dir == -1) {
        break;
      }
    }
    if (grid[y][x] == S) {
      if (realdir == 0) {
        realdir = i;
      }
      printf("%d\n", steps);
    }
  }
  char inout[1024][1024];
  for (int i = 0; i < 1024; i++) {
    for (int j = 0; j < 1024; j++) {
      inout[i][j] = 0;
    }
  }
  for (int i = 0; i < rows + 1; i++) {
    for (int j = 0; j < cols + 1; j++) {
      inout[i][j] = ' ';
    }
  }
  int x = sx, y = sy;
  int olddir = realdir, newdir = realdir;
  while (1) {
    int lx = x, rx = x, ly = y, ry = y;
    int ldir = left[olddir];
    int rdir = right[olddir];
    travel(ldir, &lx, &ly);
    travel(rdir, &rx, &ry);
    if (inout[ly][lx] != '.') {
      inout[ly][lx] = 'L';
    }
    if (inout[ry][rx] != '.') {
      inout[ry][rx] = 'R';
    }
    lx = x, rx = x, ly = y, ry = y;
    ldir = left[newdir];
    rdir = right[newdir];
    travel(ldir, &lx, &ly);
    travel(rdir, &rx, &ry);
    if (inout[ly][lx] != '.') {
      inout[ly][lx] = 'L';
    }
    if (inout[ry][rx] != '.') {
      inout[ry][rx] = 'R';
    }
    inout[y][x] = '.';
    travel(newdir, &x, &y);
    olddir = newdir;
    newdir = new_dir(olddir, grid[y][x]);
    if (newdir == -1) {
      break;
    }
  }
  // leaving these in because they look cool as hell actually
  for (int i = 0; i < rows; i++) {
    printf("%s\n", inout[i]);
  }
  puts("");
  // flood fill inout
  while (1) {
    int change = 0;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (inout[i][j] == ' ') {
          for (int k = 0; k < 8; k++) {
            char c = inout[i + dy[k]][j + dx[k]];
            if (c == 'L' || c == 'R') {
              inout[i][j] = c;
              change = 1;
              break;
            }
          }
        }
      }
    }
    if (!change) {
      break;
    }
  }
  int l = 0, r = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (inout[i][j] == 'L') {
        l++;
      } else if (inout[i][j] == 'R') {
        r++;
      }
    }
  }
  for (int i = 0; i < rows; i++) {
    printf("%s\n", inout[i]);
  }
  printf("Left: %d\nRight: %d\n", l, r);
}
