#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZZZ ((26 * 26 * 26) - 1)

int str_to_int(char *s) {
  return ((s[0] - 'A') * 26 * 26) + ((s[1] - 'A') * 26) + (s[2] - 'A');
}

int main(void) {
  int steps = 0;
  int lr[1024];
  int left[ZZZ + 1];
  int right[ZZZ + 1];
  for (int i = 0; i < ZZZ + 1; i++) {
    left[i] = -1;
    right[i] = -1;
  }
  char c;
  int lr_total = 0;
  while ((c = fgetc(stdin)) != '\n') {
    lr[lr_total++] = c == 'L' ? 1 : 0;
  }
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    char *from = strtok(buf, " ");
    strtok(NULL, " ");
    char *l_s = strtok(NULL, " ") + 1;
    char *r_s = strtok(NULL, " ");
    if (!l_s || !r_s) {
      continue;
    }
    l_s[3] = 0;
    r_s[3] = 0;
    int index = str_to_int(from);
    left[index] = str_to_int(l_s);
    right[index] = str_to_int(r_s);
  }
  int lr_index = 0;
  int maps[1024];
  int map_z_first[1024];
  int map_z_second[1024];
  int map_count = 0;
  for (int i = 0; i < ZZZ + 1; i++) {
    if (left[i] == -1) {
      continue; // no map
    }
    if (i % 26 == 0) { // last char is A
      maps[map_count++] = i;
    }
  }
  for (int i = 0; i < 1024; i++) {
    map_z_first[i] = 0;
  }
  while (1) {
    steps++;
    for (int i = 0; i < map_count; i++) {
      if (lr[lr_index]) {
        maps[i] = left[maps[i]];
      } else {
        maps[i] = right[maps[i]];
      }
      assert(maps[i] != -1);
    }
    if (++lr_index == lr_total) {
      lr_index = 0;
    }
    int all_z = 1;
    for (int i = 0; i < map_count; i++) {
      if (maps[i] % 26 != 25) {
        all_z = 0;
      } else {
        if (!map_z_first[i]) {
          printf("Map %d reaches z at step %d\n", i, steps);
          map_z_first[i] = steps;
        } else if (!map_z_second[i]) {
          printf("Map %d loops every %d steps\n", i, steps - map_z_first[i]);
          map_z_second[i] = steps;
        }
      }
    }
    if (all_z) {
      break;
    }
  }
  printf("%d\n", steps);
}
