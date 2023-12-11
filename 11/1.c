#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct xy_s {
  int x;
  int y;
} xy;

int xy_cmp_x(const void *a, const void *b) {
  return ((xy *)a)->x - ((xy *)b)->x;
}

int xy_cmp_y(const void *a, const void *b) {
  return ((xy *)a)->y - ((xy *)b)->y;
}

int main(void) {
  long sum = 0;
  char b[1024][1024];
  int rows = 0;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    memcpy(b[rows++], buf, 1024);
  }
  int cols = strlen(b[0]);
  int gcount = 0;
  int gr[1024];
  int gc[1024];
  int gr2[1024];
  int gc2[1024];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (b[i][j] == '#') {
        gr[gcount] = i;
        gr2[gcount] = i;
        gc[gcount] = j;
        gc2[gcount] = j;
        gcount++;
      }
    }
  }

  for (int i = 0; i < rows; i++) {
    int g = 0;
    for (int j = 0; j < cols; j++) {
      if (b[i][j] == '#') {
        g = 1;
      }
    }
    if (!g) {
      for (int k = 0; k < gcount; k++) {
        if (gr[k] > i) {
          gr2[k] += 1;
        }
      }
    }
  }
  for (int j = 0; j < rows; j++) {
    int g = 0;
    for (int i = 0; i < cols; i++) {
      if (b[i][j] == '#') {
        g = 1;
      }
    }
    if (!g) {
      for (int k = 0; k < gcount; k++) {
        if (gc[k] > j) {
          gc2[k] += 1;
        }
      }
    }
  }

  for (int i = 0; i < gcount; i++) {
    for (int j = 0; j < i; j++) {
      long dx = gr2[i] - gr2[j];
      long dy = gc2[i] - gc2[j];
      sum += dx > 0 ? dx : -dx;
      sum += dy > 0 ? dy : -dy;
    }
  }

  printf("%ld\n", sum);
}
