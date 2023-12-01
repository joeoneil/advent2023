#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int sum = 0;
  char buf[1024];
  char *nums[] = {"zero", "one", "two",   "three", "four",
                  "five", "six", "seven", "eight", "nine"};
  int line = 0;
  while (1) {
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    int l = strlen(buf);
    buf[l - 1] = 0;
    int first = -1;
    int last = -1;
    for (int i = 0; i < l; i++) {
      char c = buf[i];
      int _i = c - 48;
      if (_i > 0 && _i < 10) {
        if (first == -1) {
          first = _i;
        }
        last = _i;
        continue;
      }
      for (int j = 0; j < 10; j++) {
        int cmp = strncmp(buf + i, nums[j], strlen(nums[j]));
        if (cmp == 0) {
          if (first == -1) {
            first = j;
          }
          last = j;
        }
      }
    }
    if (first != -1) {
      sum += first * 10 + last;
    }
    line++;
  }
  printf("%d\n", sum);
}
