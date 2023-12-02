#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) a < b ? b : a

int main(void) {
  char *colors[3] = {"red", "green", "blue"};
  int r_max = 12;
  int sum = 0;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    strtok(buf, " "); // eat Game
    char *id_s = strtok(0, " ");
    int id = strtol(id_s, NULL, 10);
    int possible = 1;
    int min_r = 0;
    int min_g = 0;
    int min_b = 0;
    while (1) {
      char *count_s = strtok(NULL, " ");
      char *color_s = strtok(NULL, " ");
      if (!count_s) {
        break;
      }
      int c = strtol(count_s, NULL, 10);
      for (int i = 0; i < 3; i++) {
        int cmp = strncmp(color_s, colors[i], strlen(colors[i]));
        if (cmp == 0) {
          if (i == 0) {
            min_r = MAX(min_r, c);
          } else if (i == 1) {
            min_g = MAX(min_g, c);
          } else if (i == 2) {
            min_b = MAX(min_b, c);
          }
        }
      }
    }
    sum += min_r * min_g * min_b;
  }
  printf("%d\n", sum);
}
