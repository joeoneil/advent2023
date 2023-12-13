#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define I(r, c) (((r)*1024) + (c))

int h_reflect(int n, int m, char *arr) {
  for (int i = 0; i < n - 1; i++) { // line of reflection below i
    int ok = 1;
    for (int j = 0; j <= i; j++) { // row to check
      if ((2 * i) - j + 1 >= n)
        continue;
      for (int k = 0; k < m; k++) { // col to check
        if (arr[I(j, k)] != arr[I((2 * i) - j + 1, k)]) {
          ok = 0;
        }
      }
    }
    if (ok) {
      return i + 1;
    }
  }
  return -1;
}

int v_reflect(int n, int m, char *arr) {
  for (int i = 0; i < m - 1; i++) { // line of reflection left of i
    int ok = 1;
    for (int j = 0; j < n; j++) {    // row to check
      for (int k = 0; k <= i; k++) { // col to check
        if ((2 * i) - k + 1 >= m)
          continue;
        if (arr[I(j, k)] != arr[I(j, (2 * i) - k + 1)]) {
          ok = 0;
        }
      }
    }
    if (ok) {
      return i + 1;
    }
  }
  return -1;
}

int main(void) {
  int sum = 0;
  char buf[1024][1024];
  while (1) {
    int n = 0;
    if (feof(stdin)) {
      break;
    }
    memset(buf, 0, 1024 * 1024);
    while (1) {
      char l[1024];
      fgets(l, 1024, stdin);
      if (feof(stdin)) {
        break;
      }
      if (l[0] == '\n')
        break;
      memcpy(buf[n++], l, 1024);
    }
    int m = strlen(buf[1]) - 1;
    int h = h_reflect(n, m, (char *)buf);
    int v = v_reflect(n, m, (char *)buf);

    if (h != -1) {
      sum += h * 100;
    }
    if (v != -1) {
      sum += v;
    }
  }
  printf("%d\n", sum);
}
