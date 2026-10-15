/* linked-list-cycle. Time O(n), Space O(1). Floyd's tortoise and hare.
 *
 * `const struct node *`: the signature proves invariant 2 -- the list is not
 * modified -- so the function cannot relink a node or mark one visited.
 * Comparing pointers compares node identity, which is the question asked.
 */
#include "solution.h"

int has_cycle(const struct node *head) {
    const struct node *slow = head, *fast = head;
    /* fast->next is only dereferenceable when fast is non-null, so both
     * conditions are needed. */
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;   /* the gap closed inside the cycle */
    }
    return 0;
}
