#include "solution.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int checks = 0;

/* Build a list from an array. Returns NULL for n == 0. */
static struct node *build(const int *a, size_t n) {
    struct node *head = NULL, **tail = &head;
    for (size_t i = 0; i < n; i++) {
        struct node *x = malloc(sizeof *x);
        if (!x) abort();
        x->val = a[i];
        x->next = NULL;
        *tail = x;
        tail = &x->next;
    }
    return head;
}

/* Frees every node. The test owns the list after reverse_list returns it. */
static void free_list(struct node *h) {
    while (h) {
        struct node *n = h->next;
        free(h);
        h = n;
    }
}

/* Copies the values into out. Returns the count, or -1 if out is too small. */
static long to_array(const struct node *h, int *out, size_t cap) {
    size_t k = 0;
    for (; h; h = h->next) {
        if (k >= cap) return -1;
        out[k++] = h->val;
    }
    return (long)k;
}

static void expect(const char *name, const int *in, size_t n,
                   const int *want, size_t m) {
    struct node *orig = build(in, n);
    struct node *r = reverse_list(orig);

    int got[256];
    long k = to_array(r, got, 256);
    assert(k == (long)m);
    for (size_t i = 0; i < m; i++) assert(got[i] == want[i]);

    /* Invariant 2: the original head is now the tail. */
    if (n > 0) assert(orig->next == NULL);

    free_list(r);
    printf("  PASS %-22s len %zu\n", name, n);
    checks++;
}

int main(void) {
    const int one[] = {1}, two[] = {1, 2}, three[] = {1, 2, 3};
    const int rtwo[] = {2, 1}, rthree[] = {3, 2, 1};
    const int neg[] = {-1, 0, 1}, rneg[] = {1, 0, -1};

    expect("empty", NULL, 0, NULL, 0);
    expect("one node", one, 1, one, 1);
    expect("two nodes", two, 2, rtwo, 2);
    expect("odd length", three, 3, rthree, 3);
    expect("negatives and zero", neg, 3, rneg, 3);

    /* Reverse twice is identity: the flips compose. */
    struct node *h = build(three, 3);
    h = reverse_list(reverse_list(h));
    int got[8];
    assert(to_array(h, got, 8) == 3);
    for (int i = 0; i < 3; i++) assert(got[i] == three[i]);
    free_list(h);
    printf("  PASS %-22s\n", "reverse twice"); checks++;

    /* 100,000 nodes: iterative, so no stack overflow. */
    size_t big = 100000;
    int *vals = malloc(big * sizeof *vals);
    if (!vals) abort();
    for (size_t i = 0; i < big; i++) vals[i] = (int)i;
    struct node *lst = reverse_list(build(vals, big));
    assert(lst != NULL && lst->val == (int)(big - 1));
    free_list(lst);
    free(vals);
    printf("  PASS %-22s\n", "100k nodes, no overflow"); checks++;

    printf("\n  %d checks passed\n", checks);
    return 0;
}
