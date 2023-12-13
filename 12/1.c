#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valid(char *r, int *d, int g) {
  char c;
  int cur = 0;
  int groups = 0;
  int index = 0;
  while ((c = r[index++])) {
    if (c == '#') {
      cur++;
      continue;
    } else if (c == '.' && cur > 0) {
      if (cur != d[groups++]) {
        return 0;
      }
      cur = 0;
    }
  }
  if (r[index - 2] == '#') {
    if (cur != d[groups]) {
      return 0;
    }
    groups++;
  }
  if (groups != g) {
    return 0;
  }
  return 1;
}

int count(char *r, int *d, int g) {
  int q[1024];
  int qcount = 0;
  char c;
  int index = 0;
  while ((c = r[index])) {
    if (c == '?') {
      q[qcount++] = index;
    }
    index++;
  }
  int count = 0;
  for (int i = 0; i < 1 << qcount; i++) {
    for (int j = 0; j < qcount; j++) {
      if (i >> j & 1) {
        r[q[j]] = '.';
      } else {
        r[q[j]] = '#';
      }
    }
    if (valid(r, d, g)) {
      count++;
    }
  }
  return count;
}

int main(void) {
  int sum = 0;
  char rows[1024][1024];
  int damaged[1024][1024];
  memset(rows, 0, 1024 * 1024);
  memset(damaged, -1, 1024 * 1024 * sizeof(int));
  int r = 0;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    char *line = strtok(buf, " ");
    strcpy(rows[r], line);
    int dcount = 0;
    char *s;
    while ((s = strtok(NULL, ","))) {
      if (!strtol(s, NULL, 10))
        break;
      damaged[r][dcount++] = strtol(s, NULL, 10);
    }
    r++;
  }
  for (int i = 0; i < r; i++) {
    int j = 0;
    while (damaged[i][j] != -1)
      j++;
    int c = count(rows[i], damaged[i], j);
    sum += c;
  }
  printf("%d\n", sum);
}
