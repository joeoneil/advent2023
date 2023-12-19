#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct part_s {
  int x;
  int m;
  int a;
  int s;
} part;

struct flow_s;

typedef struct rule_s {
  int var;
  int lt;
  int val;
  int a;      // -1 reject, 1 accept, 0 goto flow
  int uncond; // unconditional accept / reject (a must be != 0)
  struct flow_s *dst;
} rule;

typedef struct flow_s {
  rule *rs;
  int rc;
  char name[4];
} flow;

int hash(char *s, int n) {
  int hash = 0;
  for (int i = 0; i < n; i++) {
    hash *= 26;
    hash += s[i] - 'a';
  }
  return hash;
}

int rating(part p) { return p.x + p.m + p.a + p.s; }

int matches(rule r, part p) {
  if (r.uncond) {
    return 1;
  } else {
    int var = ((int *)(&p))[r.var]; // C moment
    if (r.lt) {
      return var < r.val;
    } else {
      return var > r.val;
    }
  }
}

flow f[26 * 26 * 26]; // flows are at most 3 chars

rule parse_rule(char *in) {
  rule r = {.var = 0, .lt = 0, .val = 0, .a = 0, .dst = 0, .uncond = 0};
  switch (in[0]) {
  case 'x':
    r.var = 0;
    break;
  case 'm':
    r.var = 1;
    break;
  case 'a':
    r.var = 2;
    break;
  case 's':
    r.var = 3;
    break;
  default:
    r.var = -1;
    break;
  }
  if (r.var != -1 && (in[1] != '<' && in[1] != '>'))
    r.var = -1;      // dst starts with x, m, a, s
  if (r.var == -1) { // unconditional rule
    r.uncond = 1;
    if (strlen(in) == 1) {
      r.a = in[0] == 'A' ? 1 : -1;
    } else {
      r.a = 0;
      r.dst = f + hash(in, strlen(in));
    }
    return r;
  }
  r.uncond = 0;
  r.lt = in[1] == '<' ? 1 : 0;
  char *eptr;
  r.val = strtol(in + 2, &eptr, 10);
  eptr++;                  // skip ':'
  if (strlen(eptr) == 1) { // result is accept / reject
    r.a = eptr[0] == 'A' ? 1 : -1;
  } else {
    r.a = 0;
    r.dst = f + hash(eptr, strlen(eptr));
  }
  return r;
}

int main(void) {
  memset(f, 0, sizeof(flow) * 26 * 26 * 26);
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (buf[0] == '\n') {
      break; // goto part parsing
    }
    rule r[16];
    int rc = 0;
    char *fname = strtok(buf, "{");
    flow *fl = &f[hash(fname, strlen(fname))];
    char *rl;
    while ((rl = strtok(NULL, ","))) {
      if (rl[strlen(rl) - 2] == '}') {
        rl[strlen(rl) - 2] = 0;
      }
      r[rc++] = parse_rule(rl);
    }
    fl->rc = rc;
    fl->rs = (rule *)malloc(sizeof(rule) * rc);
    memcpy(fl->rs, r, sizeof(rule) * rc);
    memcpy(fl->name, fname, strlen(fname) + 1);
  }

  part p[1024];
  int pc = 0;
  while (1) {
    char buf[1024];
    fgets(buf, 1024, stdin);
    if (feof(stdin))
      break;

    char *eptr = buf + 3;
    part pt;
    pt.x = strtol(eptr, &eptr, 10);
    eptr += 3;
    pt.m = strtol(eptr, &eptr, 10);
    eptr += 3;
    pt.a = strtol(eptr, &eptr, 10);
    eptr += 3;
    pt.s = strtol(eptr, NULL, 10);
    p[pc++] = pt;
  }

  long sum = 0;

  for (int i = 0; i < pc; i++) {
    flow fl = f[hash("in", 2)];
    while (1) {
      int j;
      for (j = 0; !matches(fl.rs[j], p[i]); j++)
        ;
      if (fl.rs[j].a) {
        if (fl.rs[j].a == 1) {
          sum += rating(p[i]);
        }
        break;
      }
      fl = *fl.rs[j].dst;
    }
  }

  printf("%ld\n", sum);
}
