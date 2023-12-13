#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_ROW(r, d, g)                                                     \
  printf("%s ", r);                                                            \
  for (int __i = 0; __i < g; __i++) {                                          \
    printf("%d ", d[__i]);                                                     \
  }                                                                            \
  puts("");

int window(char *r, int len, int lookback) {
  if (lookback && r[-1] == '#') {
    return 0;
  }
  if (r[len] == '#') {
    return 0;
  }
  for (int i = 0; i < len; i++) {
    if (r[i] == '.') {
      return 0;
    }
  }
  return 1;
}

int groups(char *r) {
  int gc = 0;
  int lookback = 0;
  do {
    if ((*r == '.' || *r == '?') && lookback && *(r - 1) == '#') {
      gc++;
    }
    lookback = 1;
  } while (*(r++));
  if (*(r - 1) == '#') {
    gc++;
  }
  return gc;
}

long count(char *r, int n, int *d, int g, int roff, long memo[][n]) {

  if (g == 0) {
    for (int i = roff; i < n; i++) {
      if (r[i] == '#') {
        return 0;
      }
    }
    return 1;
  }
  long sum = 0;
  for (int i = roff; i < n - d[0] + 1; i++) {
    if (memo[g][i] != -1) {
      sum += memo[g][i];
      continue;
    }
    if (r[i - 1] == '#') {
      return sum;
    }
    if (window(r + i, d[0], i > 0)) {
      long ret = count(r, n, d + 1, g - 1, i + d[0] + 1, memo);
      memo[g][i] = ret;
      sum += ret;
    }
  }
  return sum;
};

void dup(char *r, int *d, int g) {
  int len = strlen(r);
  r[len++] = '?';
  for (int i = 1; i < 5; i++) {
    for (int j = 0; j < len; j++) {
      r[i * len + j] = r[j];
    }
    for (int j = 0; j < g; j++) {
      d[i * g + j] = d[j];
    }
  }
  r[len * 5 - 1] = '\0';
}

int main(void) {
  long sum = 0;
  char _ = '.';
  char rows[1024][1024];
  int damaged[1024][30];
  memset(rows, 0, 1024 * 1024);
  memset(damaged, -1, 1024 * 30 * sizeof(int));
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
    long c;
    long *memo = (long *)malloc(sizeof(long) * strlen(rows[i]) * j * 5 * 10);
    memset(memo, -1, sizeof(long) * strlen(rows[i]) * j * 5 * 10);
    if (1) {
      dup(rows[i], damaged[i], j);
      c = count(rows[i], strlen(rows[i]), damaged[i], j * 5, 0, memo);
    } else {
      c = count(rows[i], strlen(rows[i]), damaged[i], j, 0, memo);
    }
    sum += c;
  }
  printf("%ld\n", sum);
}
