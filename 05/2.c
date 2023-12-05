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
  unsigned long seed_r[1024][2];
  int seedcount = 0;
  char buf[1024];
  fgets(buf, 1024, stdin);
  strtok(buf, " ");
  while (1) {
    char *seed_s1 = strtok(NULL, " ");
    char *seed_s2 = strtok(NULL, " ");
    if (!seed_s1 || !seed_s2) {
      break;
    }
    seed_r[seedcount][0] = strtol(seed_s1, NULL, 10);
    seed_r[seedcount++][1] = strtol(seed_s2, NULL, 10);
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
  // Fuck it, we'll cook my CPU. 1.2 billion seeds here we go
  for (int h = 0; h < seedcount; h++) {
    for (unsigned long i = seed_r[h][0]; i < seed_r[h][0] + seed_r[h][1]; i++) {
      unsigned long num = i;
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
  }
  printf("%lu\n", min);
}
