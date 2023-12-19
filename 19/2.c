#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct rpart_s {
  int start;
  int end;
} rpart;

typedef struct range_s {
  rpart r[4];
  flow *flow;
  int accept;
} range;

// This is the worst function I have ever written in my entire programming
// career.
void split_on_rule(range r, rule l, range **accept, range **reject) {
  int rc = 0;
  if (l.uncond) {
    **accept = r;
    (*accept)->accept = l.a;
    (*accept)->flow = l.dst;
    *reject = NULL;
  } else {
    int start = r.r[l.var].start;
    int end = r.r[l.var].end;
    // don't look at this
    if (l.lt) {
      if (end < l.val) {
        **accept = r;
        (*accept)->accept = l.a;
        (*accept)->flow = l.dst;
        *reject = NULL;
      } else if (start > l.val) {
        *accept = NULL;
        **reject = r;
      } else {
        // range spans threshold
        **accept = r;
        (*accept)->accept = l.a;
        (*accept)->flow = l.dst;
        **reject = r;
        (*accept)->r[l.var].end = l.val;
        (*reject)->r[l.var].start = l.val;
      }
    } else {
      if (start >= l.val) {
        **accept = r;
        (*accept)->accept = l.a;
        (*accept)->flow = l.dst;
        *reject = NULL;
      } else if (end < l.val) {
        *accept = NULL;
        **reject = r;
      } else {
        // range spans threshold
        **accept = r;
        (*accept)->accept = l.a;
        (*accept)->flow = l.dst;
        **reject = r;
        // this off by one took the better part of an hour to find
        // the way I found it was 'what if this is it' and it was.
        (*accept)->r[l.var].start = l.val + 1;
        (*reject)->r[l.var].end = l.val + 1;
      }
    }
  }
}

int split_range(range r, range *out, int max) {
  assert(out);
  assert(max);
  assert(r.flow);
  int rc = 0;
  range a = r;
  range b = r;
  for (int i = 0; i < r.flow->rc; i++) {
    range *ar = &a;
    range *br = &b;
    split_on_rule(r, r.flow->rs[i], &ar, &br);
    if (ar != NULL) {
      out[rc++] = *ar;
    }
    if (br != NULL) {
      r = *br;
      a = *br;
    } else {
      break;
    }
  }
  return rc;
}

long range_val(range r) {
  long sum = 1;
  for (int i = 0; i < 4; i++) {
    sum *= r.r[i].end - r.r[i].start;
  }
  return sum;
}

int hash(char *s, int n) {
  int hash = 0;
  for (int i = 0; i < n; i++) {
    hash *= 26;
    hash += s[i] - 'a';
  }
  return hash;
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

  range ranges[10000];
  int rcnt = 1;
  int roff = 0;
  {
    rpart p = {
        .start = 1,
        .end = 4001,
    };
    range init = {
        .r = {p, p, p, p},
        .flow = f + hash("in", 2),
        .accept = 0,
    };
    ranges[0] = init;
  }

  unsigned long sum = 0;

  while (roff < rcnt) {
    range out[20]; // way more than needed
    int ret = split_range(ranges[roff], out, 20);

    for (int i = 0; i < ret; i++) {
      if (out[i].flow == NULL) {
        // range terminated
        if (out[i].accept == 1) {
          sum += range_val(out[i]);
        }
      } else {
        ranges[rcnt++] = out[i];
      }
    }

    roff++;
  }

  printf("%ld\n", sum);
}
