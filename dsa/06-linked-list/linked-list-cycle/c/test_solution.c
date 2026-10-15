#include "solution.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int checks = 0;

static struct node *build(const int *a, size_t n, struct node **nodes) {
    struct node *head = NULL, **tail = &head;
    for (size_t i = 0; i < n; i++) {
        struct node *x = malloc(sizeof *x);
        if (!x) abort();
        x->val = a[i]; x->next = NULL;
        *tail = x; tail = &x->next;
        if (nodes) nodes[i] = x;
    }
    return head;
}

static void free_list(struct node *h) {
    while (h) { struct node *n = h->next; free(h); h = n; }
}

static void check(const char *name, int got, int want) {
    if (got != want) { printf("  FAIL %-26s got %d want %d\n", name, got, want); assert(0); }
    printf("  PASS %-26s %s\n", name, want ? "cycle" : "no cycle");
    checks++;
}

int main(void) {
    check("empty", has_cycle(NULL), 0);

    struct node *one = build((int[]){1}, 1, NULL);
    check("one node, no cycle", has_cycle(one), 0);
    free_list(one);

    struct node *two = build((int[]){1, 2}, 2, NULL);
    check("two nodes, no cycle", has_cycle(two), 0);
    free_list(two);

    struct node *self = build((int[]){1}, 1, NULL);
    self->next = self;
    check("one node, self-loop", has_cycle(self), 1);
    self->next = NULL; free_list(self);

    struct node *nodes[4];
    struct node *h = build((int[]){1, 2, 3}, 3, nodes);
    nodes[2]->next = nodes[0];
    check("cycle back to head", has_cycle(h), 1);
    nodes[2]->next = NULL; free_list(h);

    struct node *m[4];
    h = build((int[]){1, 2, 3, 4}, 4, m);
    m[3]->next = m[1];
    check("cycle to middle", has_cycle(h), 1);
    m[3]->next = NULL; free_list(h);

    /* equal values, distinct nodes: identity, not value */
    h = build((int[]){7, 7, 7, 7}, 4, NULL);
    check("equal values, no cycle", has_cycle(h), 0);
    free_list(h);

    /* 10,000 nodes, both shapes */
    enum { N = 10000 };
    int vals[N];
    for (int i = 0; i < N; i++) vals[i] = i;
    struct node *ns[N];
    h = build(vals, N, ns);
    check("long, no cycle", has_cycle(h), 0);
    ns[N - 1]->next = ns[0];
    check("long, cycle at end", has_cycle(h), 1);
    ns[N - 1]->next = NULL; free_list(h);

    printf("\n  %d checks passed\n", checks);
    return 0;
}
