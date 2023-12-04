#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int sum = 0;
  int copies[1024];
  int max_card = 0;
  for (int i = 0; i < 1024; i++) {
    copies[i] = 0;
  }
  while (1) {
    char buf[1024];
    int deck[64]; // hopefully not more than 64 numbers lmao
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    strtok(buf, " "); // Eat Card
    int card = strtol(strtok(NULL, " "), NULL, 10);
    max_card = card;
    copies[card] += 1;
    char *word;
    int count = 0;
    do {
      word = strtok(NULL, " ");
      if (!strcmp(word, "|")) {
        break;
      }
      deck[count] = strtol(word, NULL, 10);
    } while (++count);
    int wins = 0;
    while (1) {
      word = strtok(NULL, " ");
      if (!word) {
        break;
      }
      int num = strtol(word, NULL, 10);
      for (int i = 0; i < count; i++) {
        if (num == deck[i]) {
          wins += 1;
        }
      }
    }
    for (int j = 1; j <= wins; j++) {
      copies[card + j] += copies[card];
    }
  }
  for (int i = 0; i <= max_card; i++) {
    sum += copies[i];
  }
  printf("%d\n", sum);
}
