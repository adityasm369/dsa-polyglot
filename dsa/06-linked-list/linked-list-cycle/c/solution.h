#ifndef LINKED_LIST_CYCLE_H
#define LINKED_LIST_CYCLE_H
struct node { int val; struct node *next; };
/* 1 if following `next` from head revisits a node, else 0. Does not modify the list. */
int has_cycle(const struct node *head);
#endif
