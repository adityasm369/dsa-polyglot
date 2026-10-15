#include "solution.hpp"
#include <cassert>
#include <cstdio>
#include <vector>

static int checks = 0;

static std::vector<ListNode*> build(const std::vector<int>& v) {
    std::vector<ListNode*> ns;
    for (int x : v) ns.push_back(new ListNode{x, nullptr});
    for (size_t i = 0; i + 1 < ns.size(); ++i) ns[i]->next = ns[i + 1];
    return ns;
}

static void free_all(std::vector<ListNode*>& ns) {
    for (auto* n : ns) delete n;
    ns.clear();
}

static void check(const char* name, bool got, bool want) {
    if (got != want) { std::printf("  FAIL %s\n", name); assert(false); }
    std::printf("  PASS %-26s %s\n", name, want ? "cycle" : "no cycle");
    ++checks;
}

int main() {
    check("empty", has_cycle(nullptr), false);

    auto one = build({1});
    check("one node, no cycle", has_cycle(one.empty() ? nullptr : one[0]), false);
    free_all(one);

    auto two = build({1, 2});
    check("two nodes, no cycle", has_cycle(two[0]), false);
    free_all(two);

    auto self = build({1});
    self[0]->next = self[0];
    check("one node, self-loop", has_cycle(self[0]), true);
    self[0]->next = nullptr; free_all(self);

    auto three = build({1, 2, 3});
    three[2]->next = three[0];
    check("cycle back to head", has_cycle(three[0]), true);
    three[2]->next = nullptr; free_all(three);

    auto four = build({1, 2, 3, 4});
    four[3]->next = four[1];
    check("cycle to middle", has_cycle(four[0]), true);
    four[3]->next = nullptr; free_all(four);

    auto same = build({7, 7, 7, 7});
    check("equal values, no cycle", has_cycle(same[0]), false);
    free_all(same);

    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) v[i] = i;
    auto big = build(v);
    check("long, no cycle", has_cycle(big[0]), false);
    big.back()->next = big[0];
    check("long, cycle at end", has_cycle(big[0]), true);
    big.back()->next = nullptr; free_all(big);

    std::printf("\n  %d checks passed\n", checks);
    return 0;
}
