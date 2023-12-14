#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cycle(int n, int m, int dr, int dc, char *board) {
  for (int i = 0; i < (n > m ? n : m); i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < m; k++) {
        if (j + dr < 0 || j + dr >= n)
          continue;
        if (k + dc < 0 || k + dc >= m)
          continue;
        if (board[j * 1024 + k] != 'O')
          continue;
        if (board[(j + dr) * 1024 + (k + dc)] != '.')
          continue;
        board[(j + dr) * 1024 + (k + dc)] = 'O';
        board[(j)*1024 + k] = '.';
      }
    }
  }
}

int eq(int n, int m, char *b1, char *b2) {
  for (int i = 0; i < 1024 * 1024; i++) {
    if (b1[i] != b2[i])
      return 0;
  }
  return 1;
}

int weight(int n, int m, char *b) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (b[i * 1024 + j] == 'O') {
        sum += n - i;
      }
    }
  }
  return sum;
}

int main(void) {
  int dr[] = {-1, 0, 1, 0};
  int dc[] = {0, -1, 0, 1};
  int sum = 0;
  char b[1024][1024];
  int rc = 0;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    memcpy(b[rc++], buf, 1024);
  }
  int cc = strlen(b[0]) - 1;
  int pw[1024];
  int w = 0;
  memset(pw, 0, 1024 * sizeof(int));
  while (1) {
    for (int i = 0; i < 4; i++) {
      cycle(rc, cc, dr[i], dc[i], (char *)b);
    }
    pw[w++] = weight(rc, cc, (char *)b);
    if (w == 1024)
      w = 0;
    int found = 0;
    for (int i = 0; i < 1024; i++) {
      for (int j = 2; j < 1024 - i; j++) { // loop of length j starting at i
        int bad = 0;
        for (int k = 0; k < j; k++) {
          if (pw[i + k] != pw[i - j + k] || pw[i + k] == 0) {
            bad = 1;
            break;
          }
        }
        if (!bad) {
          printf("%d\n", pw[i + ((1000000000 - i - 1) % j)]);
          found = 1;
          break;
        }
      }
      if (found)
        break;
    }
    if (found)
      break;
  }
  return 0;
}
