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
  for (int i = 0; i < 4; i++) {
    int dir = i;
    int x = sx;
    int y = sy;
    int steps = 0;
    while (1) {
      travel(dir, &x, &y);
      dir = new_dir(dir, grid[y][x]);
      steps++;
      if (dir == -1) {
        break;
      }
    }
    if (grid[y][x] == S) {
      printf("%d\n", steps / 2);
    } else {
    }
  }
}
