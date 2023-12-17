#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P(i) ((i - 1) / 2)
#define L(i) (2 * i + 1)
#define R(i) (2 * i + 2)

typedef struct state_s {
  int r;
  int c;
  int dir;
  int dc;
} state;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

state *q = NULL;
int qsize = 1;
int qcap = 0;
char board[1024][1024];
int rc;
int cc;
unsigned int cost[1024][1024][4][3];
unsigned int cest[1024][1024][4][3];

int from(state s, state *out) {
  int s_count = 0;
  for (int i = -1; i < 2; i++) {
    int newdir = (s.dir + i + 4) % 4;
    int nr = s.r + dr[newdir];
    int nc = s.c + dc[newdir];
    int dc = i == 0 ? s.dc + 1 : 0;
    if (s.r == 0 && s.c == 0) {
      dc = i == 0 ? s.dc : 0;
    }
    if (nr < 0 || nc < 0 || nr >= rc || nc >= cc) {
      continue;
    }
    if (dc == 3) {
      continue;
    }
    state ns = {
        .r = nr,
        .c = nc,
        .dir = newdir,
        .dc = dc,
    };
    out[s_count++] = ns;
  }
  return s_count;
}

typedef struct heap_s {
  int size;
  int cap;
  state *arr;
} pq;

// was going to do A*, but djikstra works fine
int h(state s) { return 0; }

int s_cost(state s) { return cest[s.r][s.c][s.dir][s.dc]; }

int state_cmp(state *a, state *b) { return s_cost(*a) - s_cost(*b); }

void pq_insert(pq *p, state s);

state pq_remove(pq *p);

int pq_contains(pq *p, state s);

#define MAX_STATES 10000000

int main(void) {
  q = (state *)malloc(sizeof(state) *
                      MAX_STATES); // more queue than we should need (hopefully)
  qcap = MAX_STATES;
  memset(board, 0, 1024 * 1024);
  memset(cost, -1, 1024 * 1024 * 4 * 4 * 3);
  rc = 0;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin)) {
      break;
    }
    strcpy(board[rc++], buf);
  }
  cc = strlen(board[0]) - 1;
  state init = {
      .r = 0,
      .c = 0,
      .dc = 0,
      .dir = 1,
  };
  q[0] = init;
  cost[0][0][1][0] = 0;
  cest[0][0][1][0] = h(init);
  pq prio = {
      .arr = q,
      .cap = qcap,
      .size = 1,
  };
  do {
    state s = pq_remove(&prio);
    if (s.r == rc - 1 && s.c == cc - 1) {
      printf("%d\n", cost[s.r][s.c][s.dir][s.dc]);
      break;
    }
    state new[3];
    int count = from(s, new);
    for (int i = 0; i < count; i++) {
      int t_cost =
          cost[s.r][s.c][s.dir][s.dc] + board[new[i].r][new[i].c] - '0';
      if (t_cost < cost[new[i].r][new[i].c][new[i].dir][new[i].dc]) {
        cost[new[i].r][new[i].c][new[i].dir][new[i].dc] = t_cost;
        cest[new[i].r][new[i].c][new[i].dir][new[i].dc] = t_cost + h(new[i]);
        if (!pq_contains(&prio, new[i])) {
          pq_insert(&prio, new[i]);
        }
      }
    }
  } while (1);
}

void swap(pq *p, int a, int b) {
  state t = p->arr[a];
  p->arr[a] = p->arr[b];
  p->arr[b] = t;
}

void pq_insert(pq *p, state s) {
  assert(p->size < p->cap);
  p->arr[p->size] = s;
  int index = p->size;
  while (state_cmp(&p->arr[index], &p->arr[P(index)]) < 0) {
    swap(p, index, P(index));
    index = P(index);
  }
  p->size++;
}

state pq_remove(pq *p) {
  assert(p->size > 0);
  state r = p->arr[0];
  swap(p, 0, --(p->size));
  int index = 0;
  while ((L(index) < p->size &&
          state_cmp(&p->arr[L(index)], &p->arr[index]) < 0) ||
         (R(index) < p->size &&
          state_cmp(&p->arr[R(index)], &p->arr[index]) < 0)) {
    if (R(index) >= p->size ||
        state_cmp(&p->arr[L(index)], &p->arr[R(index)]) < 0) {
      swap(p, index, L(index));
      index = L(index);
    } else {
      swap(p, index, R(index));
      index = R(index);
    }
  }
  return r;
}

int state_eq(state *a, state *b) {
  if (a->r == b->r && a->c == b->c && a->dc == b->dc && a->dir == b->dir) {
    return 1;
  } else {
    return 0;
  }
}

int pq_contains(pq *p, state s) {
  for (int i = 0; i < p->size; i++) {
    if (state_eq(&p->arr[i], &s)) {
      return 1;
    }
  }
  return 0;
}
