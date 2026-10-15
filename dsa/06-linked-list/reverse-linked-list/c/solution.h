#ifndef REVERSE_LIST_H
#define REVERSE_LIST_H
#include <stddef.h>

struct node {
    int val;
    struct node *next;
};

/* Reverses the list in place. Returns the new head (the old tail), or NULL for
 * an empty list. Allocates nothing and frees nothing: the caller owns every
 * node before and after the call. */
struct node *reverse_list(struct node *head);
#endif
