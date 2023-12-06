#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int total = 1;
  int times[4];
  int records[4];
  char time_s[1024];
  char rec_s[1024];
  fgets(time_s, 1024, stdin);
  fgets(rec_s, 1024, stdin);
  strtok(time_s, " ");
  for (int i = 0; i < 4; i++) {
    times[i] = strtol(strtok(NULL, " "), NULL, 10);
  }
  strtok(rec_s, " ");
  for (int i = 0; i < 4; i++) {
    records[i] = strtol(strtok(NULL, " "), NULL, 10);
  }
  for (int i = 0; i < 4; i++) {
    int count = 0;
    for (int j = 0; j < times[i]; j++) {
      if (j * (times[i] - j) > records[i]) {
        count++;
      }
    }
    total *= count;
  }
  printf("%d\n", total);
}
