#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int total = 0;
  long times;
  long records;
  char time_s[1024];
  char rec_s[1024];
  fgets(time_s, 1024, stdin);
  fgets(rec_s, 1024, stdin);
  char time2_s[1024];
  char rec2_s[1024];
  int time2 = 0;
  int rec2 = 0;
  for (int i = 0; i < strlen(time_s); i++) {
    if (isdigit(time_s[i])) {
      time2_s[time2++] = time_s[i];
    }
    if (isdigit(rec_s[i])) {
      rec2_s[rec2++] = rec_s[i];
    }
  }
  times = strtol(time2_s, NULL, 10);
  records = strtol(rec2_s, NULL, 10);
  printf("%ld, %ld\n", times, records);
  for (int i = 0; i < times; i++) {
    if (i * (times - i) > records) {
      total++;
    }
  }
  printf("%d\n", total);
}
