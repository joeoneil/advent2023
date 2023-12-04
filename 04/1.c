#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int sum = 0;
  while (1) {
    char buf[1024];
    int deck[64]; // hopefully not more than 64 numbers lmao
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    strtok(buf, " "); // Eat Card
    strtok(NULL, " ");
    char *word;
    int count = 0;
    do {
      word = strtok(NULL, " ");
      if (!strcmp(word, "|")) {
        break;
      }
      deck[count] = strtol(word, NULL, 10);
    } while (++count);
    int val = 1;
    while (1) {
      word = strtok(NULL, " ");
      if (!word) {
        break;
      }
      int num = strtol(word, NULL, 10);
      for (int i = 0; i < count; i++) {
        if (num == deck[i]) {
          val <<= 1;
        }
      }
    }
    val >>= 1;
    sum += val;
  }
  printf("%d\n", sum);
}
