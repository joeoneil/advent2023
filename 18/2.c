#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};
const char *dname[] = {"UP", "RIGHT", "DOWN", "LEFT"};

typedef struct range_s {
  int col;
  int start;
  int end;
  int dir;
  int tdir;
  int bdir;
} range;

int range_cmp(const void *a, const void *b) {
  return ((range *)a)->col - ((range *)b)->col;
}

int in_range(int v, range r) { return v >= r.start && v <= r.end; }

int end_of(int v, range r) {
  if (v == r.start) {
    return 1;
  }
  if (v == r.end) {
    return 2;
  }
  return 0;
}

int ldir(char l) {
  switch (l) {
  case 'U':
    return 0;
  case 'R':
    return 1;
  case 'D':
    return 2;
  case 'L':
    return 3;
  }
  return -1;
}

int main(void) {
  unsigned long sum = 0;
  int r = 1 >> 23;
  int c = 1 >> 23;
  int minr = INT_MAX;
  int minc = INT_MAX;
  int maxr = 0;
  int maxc = 0;
  range rng[1024];
  int rcnt = 0;
  int prevdir;
  int extra_dir;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    int a = ldir(strtok(buf, " ")[0]);
    int b = strtol(strtok(NULL, " "), NULL, 10);

    char *hex = strtok(NULL, " ");
    hex += 2;
    char dir = hex[5];
    hex[5] = 0;
    int amt = strtol(hex, NULL, 16);
    int d = (dir - '0' + 1) % 4;

    if (d % 2 == 0) {
      int e1 = r;
      int e2 = r + (amt * dr[d]);
      range ran = {.col = c,
                   .start = e1 < e2 ? e1 : e2,
                   .end = e1 < e2 ? e2 : e1,
                   .dir = d,
                   .tdir = prevdir};
      rng[rcnt++] = ran;
    } else {
      if (rcnt == 0) {
        extra_dir = dc[d];
      }
      rng[rcnt - 1].bdir = d;
    }
    c += dc[d] * amt;
    r += dr[d] * amt;
    if (c <= minc)
      minc = c;
    if (c >= maxc)
      maxc = c;
    if (r <= minr)
      minr = r;
    if (r >= maxr)
      maxr = r;

    prevdir = d;
  }
  rng[rcnt - 1].bdir = extra_dir;
  qsort(rng, rcnt, sizeof(range), range_cmp);
  for (int i = 0; i < rcnt; i++) {
    if (rng[i].dir == 0) {
      int tmp = rng[i].tdir;
      rng[i].tdir = rng[i].bdir;
      rng[i].bdir = tmp;
    }
  }

  minr--;
  minc--;
  maxr++;
  maxc++;

  for (int i = minr; i < maxr; i++) {
    int found = 0;
    range prev;
    for (int j = 0; j < rcnt; j++) {
      if (in_range(i, rng[j])) {
        if (!found) {
          found = 1;
          prev = rng[j];
          continue;
        }
        range cur = rng[j];
        int s_start = sum;
        if (cur.dir == prev.dir) {
          sum += cur.col - prev.col;

        } else if (prev.dir == 0) {
          sum += cur.col - prev.col + 1;
        } else if (end_of(i, prev) && end_of(i, prev) == end_of(i, cur)) {
          if (end_of(i, prev) == 2 && prev.tdir == 1) {
            sum += cur.col - prev.col - 1;
          }
          if (end_of(i, prev) == 1 && prev.tdir == 3) {
            sum += cur.col - prev.col - 1;
          }
        }
        prev = cur;
      }
    }
  }

  printf("%ld\n", sum);
}
