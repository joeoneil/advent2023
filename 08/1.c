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
    printf("%s, %s, %s\n", from, l_s, r_s);
    int index = str_to_int(from);
    printf("%s, %d\n", from, index);
    if (index == ZZZ) {
      continue;
    }
    left[index] = str_to_int(l_s);
    right[index] = str_to_int(r_s);
  }
  int lr_index = 0;
  int map = 0;
  while (1) {
    steps++;
    if (lr[lr_index++]) {
      map = left[map];
    } else {
      map = right[map];
    }
    if (map == ZZZ) {
      break;
    }
    if (lr_index == lr_total) {
      lr_index = 0;
    }
  }
  printf("%d\n", steps);
}
