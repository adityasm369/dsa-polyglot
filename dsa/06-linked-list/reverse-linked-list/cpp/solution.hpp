#pragma once

// reverse-linked-list. Time O(n), Space O(1).
//
// Raw pointers on purpose. Ownership is not this function's business: it
// rewires links and frees nothing. The test harness owns the nodes and frees
// them, and AddressSanitizer's leak check proves nothing is lost.
//
// The modern alternative -- std::unique_ptr<ListNode> next -- would make the
// ownership explicit in the type, but then a reversal has to move unique_ptrs
// around, which is the same problem Rust solves with Option<Box<T>>.
struct ListNode {
    int val;
    ListNode* next;
};

inline ListNode* reverse_list(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* next = head->next; // save the rest BEFORE rewriting
        head->next = prev;           // flip this link
        prev = head;                 // the reversed part grows by one
        head = next;                 // step into the unreversed rest
    }
    return prev;
}
