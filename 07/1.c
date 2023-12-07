#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A 14
#define K 13
#define Q 12
#define J 11
#define T 10

typedef struct {
  char *hand;
  int bid;
} hand;

int card_score(char c) {
  int score;
  if (isdigit(c)) {
    score = c - '0';
  } else {
    switch (c) {
    case 'A':
      score = A;
      break;
    case 'K':
      score = K;
      break;
    case 'Q':
      score = Q;
      break;
    case 'J':
      score = J;
      break;
    case 'T':
      score = T;
      break;
    }
  }
  return score;
}

int score_hand(hand *h) {
  int cards[15];
  for (int i = 0; i < 15; i++) {
    cards[i] = 0;
  }
  for (int i = 0; i < 5; i++) {
    cards[card_score(h->hand[i])]++;
  }
  int two = 0, three = 0, four = 0, five = 0;
  for (int i = 0; i < 15; i++) {
    if (cards[i] == 2) {
      two++;
    } else if (cards[i] == 3) {
      three++;
    } else if (cards[i] == 4) {
      four++;
    } else if (cards[i] == 5) {
      five++;
    }
  }
  int score = 0;
  if (five) {
    score = 25;
  } else if (four) {
    score = 24;
  } else if (three && two) {
    score = 23;
  } else if (three) {
    score = 22;
  } else if (two == 2) {
    score = 21;
  } else if (two) {
    score = 20;
  } else {
    score = 0;
  }
  score *= 10;
  for (int i = 0; i < 5; i++) {
    score *= 15;
    score += card_score(h->hand[i]);
  }
  return score;
}

int hand_cmp(const void *h1, const void *h2) {
  return score_hand((hand *)h1) - score_hand((hand *)h2);
}

int main(void) {
  long sum = 0;
  hand h[1024];
  int h_count;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    char *hand_s = strtok(buf, " ");
    hand h_s = {.hand = strdup(hand_s),
                .bid = strtol(strtok(NULL, " "), NULL, 10)};
    h[h_count++] = h_s;
  }
  qsort(h, h_count, sizeof(hand), hand_cmp);
  for (long i = 0; i < h_count; i++) {
    sum += h[i].bid * (i + 1);
  }
  printf("%ld\n", sum);
}
