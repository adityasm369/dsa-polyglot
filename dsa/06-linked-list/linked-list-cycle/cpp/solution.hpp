#pragma once

// linked-list-cycle. Time O(n), Space O(1). Floyd's tortoise and hare.
//
// `const ListNode*`: the list is read, never written. The test checks that the
// pointers are unchanged afterwards, which is invariant 2 made observable.
struct ListNode {
    int val;
    ListNode* next;
};

inline bool has_cycle(const ListNode* head) {
    const ListNode* slow = head;
    const ListNode* fast = head;
    while (fast && fast->next) {     // fast->next is safe only when fast is non-null
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;   // pointer identity: the gap closed
    }
    return false;
}
