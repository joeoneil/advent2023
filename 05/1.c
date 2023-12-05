#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct map_s {
  unsigned long dst;
  unsigned long src;
  unsigned long count;
} Map;

int in_map(Map m, unsigned long src) {
  return (m.src <= src && m.src + m.count > src);
}

unsigned long map(Map m, unsigned long src) {
  if (in_map(m, src)) {
    return m.dst + (src - m.src);
  } else {
    return src;
  }
}

int main(void) {
  Map maps[1024][7];
  int map_counts[7];
  unsigned long min = ULONG_MAX;
  unsigned long seed[1024];
  int seedcount = 0;
  char buf[1024];
  fgets(buf, 1024, stdin);
  strtok(buf, " ");
  while (1) {
    char *seed_s = strtok(NULL, " ");
    if (!seed_s) {
      break;
    }
    seed[seedcount++] = strtol(seed_s, NULL, 10);
  }
  int map_num = -1;
  int map_index = 0;
  while (1) {
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      map_counts[map_num] = map_index;
      break;
    }
    int cmp = strncmp(buf + strlen(buf) - 5, "map:", 4);
    if (!cmp) {
      map_counts[map_num] = map_index;
      map_num++;
      map_index = 0;
      continue;
    }
    if (buf[0] == '\n') {
      continue;
    }
    Map m = {.dst = strtoull(strtok(buf, " "), NULL, 10),
             .src = strtoull(strtok(NULL, " "), NULL, 10),
             .count = strtoull(strtok(NULL, " "), NULL, 10)};
    maps[map_index++][map_num] = m;
  }
  for (int i = 0; i < seedcount; i++) {
    unsigned long num = seed[i];
    for (int j = 0; j < 7; j++) {
      for (int k = 0; k < map_counts[j]; k++) {
        if (in_map(maps[k][j], num)) {
          unsigned long new = map(maps[k][j], num);
          num = new;
          break;
        }
      }
    }
    if (num < min) {
      min = num;
    }
  }
  printf("%ld\n", min);
}
