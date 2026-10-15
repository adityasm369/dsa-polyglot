/* reverse-linked-list. Time O(n), Space O(1).
 *
 * Here the ownership question is not theoretical. Every node was malloc'd, so
 * exactly one party must free each one, exactly once. This function does
 * neither -- it only rewires pointers -- which is why it can be correct.
 *
 * The iterative form matters for a second reason: the recursive version uses
 * one stack frame per node, and a 100 000-node list overflows the default
 * 8 MB stack. The tests check that.
 */
#include "solution.h"

struct node *reverse_list(struct node *head) {
    struct node *prev = NULL;
    while (head) {
        struct node *next = head->next; /* save the rest BEFORE rewriting */
        head->next = prev;              /* flip this link */
        prev = head;                    /* the reversed part grows by one */
        head = next;                    /* step into the unreversed rest */
    }
    return prev;
}
