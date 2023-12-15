#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char hash(char *c, int max_c) {
  int index = 0;
  unsigned char h = 0;
  while (1) {
    if (index > max_c)
      break;
    if (c[index] == ',')
      break;
    if (c[index] == '\n')
      break;
    h *= 17;
    h += c[index++];
  }
  return h;
}

int main(void) {
  int sum = 0;
  char buf[1024 * 32];
  fgets(buf, 1024 * 32, stdin);

  char boxes[256][16][16];
  int boxv[256][16];
  int boxc[256];
  memset(boxc, 0, 256 * sizeof(int));

  char *s = strtok(buf, ",\n");
  do {
    if (s[strlen(s) - 1] == '\n') {
      s[strlen(s) - 1] = 0;
    }
    int v = strtol(s + (strlen(s) - 1), NULL, 10);
    if (!v) { // remove lens
      s[strlen(s) - 1] = 0;
      unsigned char h = hash(s, strlen(s));
      int found = 0;
      for (int i = 0; i < boxc[h]; i++) {
        if (found) {
          strcpy(boxes[h][i - 1], boxes[h][i]);
          boxv[h][i - 1] = boxv[h][i];
        }
        if (!strcmp(s, boxes[h][i])) {
          found = 1;
        }
      }
      if (found) {
        boxc[h]--;
      }
    } else {
      s[strlen(s) - 2] = 0;
      unsigned char h = hash(s, strlen(s));
      int found = 0;
      for (int i = 0; i < boxc[h]; i++) {
        if (!strcmp(s, boxes[h][i])) {
          boxv[h][i] = v;
          found = 1;
          break;
        }
      }
      if (!found) {
        boxv[h][boxc[h]] = v;
        strcpy(boxes[h][boxc[h]++], s);
      }
    }
  } while ((s = strtok(NULL, ",")));

  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < boxc[i]; j++) {
      sum += boxv[i][j] * (j + 1) * (i + 1);
    }
  }

  printf("%d\n", sum);
}
