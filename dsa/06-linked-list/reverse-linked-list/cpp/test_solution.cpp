#include "solution.hpp"
#include <cassert>
#include <cstdio>
#include <vector>

static int checks = 0;

static ListNode* build(const std::vector<int>& v) {
    ListNode* head = nullptr;
    for (auto it = v.rbegin(); it != v.rend(); ++it) head = new ListNode{*it, head};
    return head;
}

static void free_list(ListNode* h) {
    while (h) { ListNode* n = h->next; delete h; h = n; }
}

static std::vector<int> collect(const ListNode* h) {
    std::vector<int> out;
    for (; h; h = h->next) out.push_back(h->val);
    return out;
}

static void expect(const char* name, std::vector<int> in, std::vector<int> want) {
    ListNode* orig = build(in);
    ListNode* r = reverse_list(orig);
    assert(collect(r) == want);
    if (!in.empty()) assert(orig->next == nullptr);   // invariant 2
    free_list(r);                                     // the test owns the nodes
    std::printf("  PASS %-22s len %zu\n", name, in.size());
    ++checks;
}

int main() {
    expect("empty", {}, {});
    expect("one node", {1}, {1});
    expect("two nodes", {1, 2}, {2, 1});
    expect("odd length", {1, 2, 3}, {3, 2, 1});
    expect("negatives and zero", {-1, 0, 1}, {1, 0, -1});

    ListNode* h = build({1, 2, 3});
    h = reverse_list(reverse_list(h));
    assert(collect(h) == (std::vector<int>{1, 2, 3}));
    free_list(h);
    std::printf("  PASS %-22s\n", "reverse twice"); ++checks;

    std::vector<int> big(100000);
    for (int i = 0; i < 100000; ++i) big[i] = i;
    ListNode* lst = reverse_list(build(big));
    assert(lst->val == 99999);
    free_list(lst);
    std::printf("  PASS %-22s\n", "100k nodes"); ++checks;

    std::printf("\n  %d checks passed\n", checks);
    return 0;
}
