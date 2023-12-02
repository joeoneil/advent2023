#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
          if (c > 12 + i) {
            possible = 0;
          }
        }
      }
    }
    if (possible) {
      sum += id;
    }
  }
  printf("%d\n", sum);
}
