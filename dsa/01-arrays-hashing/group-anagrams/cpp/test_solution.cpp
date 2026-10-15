#include "solution.hpp"
#include <algorithm>
#include <cassert>
#include <cstdio>

static int checks = 0;

static bool is_anagram(const std::string& a, const std::string& b) {
    std::string x = a, y = b;
    std::sort(x.begin(), x.end());
    std::sort(y.begin(), y.end());
    return x == y;
}

// Invariant 2 in both directions, plus invariant 1.
static void check_partition(const char* name, const std::vector<std::string>& strs,
                            std::size_t want_groups) {
    auto groups = group_anagrams(strs);
    if (groups.size() != want_groups) {
        std::printf("  FAIL %-26s got %zu groups, want %zu\n", name, groups.size(), want_groups);
        assert(false);
    }
    // Every string appears exactly once.
    std::vector<std::string> flat;
    for (const auto& g : groups) flat.insert(flat.end(), g.begin(), g.end());
    std::vector<std::string> want = strs;
    std::sort(flat.begin(), flat.end());
    std::sort(want.begin(), want.end());
    assert(flat == want);
    // Grouped together exactly when anagrams.
    for (std::size_t gi = 0; gi < groups.size(); ++gi) {
        for (const auto& a : groups[gi]) {
            for (const auto& b : groups[gi]) assert(is_anagram(a, b));
            for (std::size_t gj = 0; gj < groups.size(); ++gj) {
                if (gi == gj) continue;
                for (const auto& b : groups[gj]) assert(!is_anagram(a, b));
            }
        }
    }
    std::printf("  PASS %-26s %zu strings, %zu groups\n", name, strs.size(), groups.size());
    ++checks;
}

int main() {
    check_partition("single string", {"a"}, 1);
    check_partition("empty string", {""}, 1);
    check_partition("all empty", {"", ""}, 1);
    check_partition("no anagrams", {"abc", "def"}, 2);
    check_partition("classic", {"eat", "tea", "tan", "ate", "nat", "bat"}, 3);
    check_partition("same letters diff counts", {"aab", "abb"}, 2);
    check_partition("repeated string", {"ab", "ab"}, 1);
    check_partition("empty mixed in", {"eat", "tea", "tan", "ate", "nat", "bat", "", "aab"}, 5);

    // The '#' separator earns its place: without it these two would collide.
    auto g = group_anagrams({std::string(1, 'a') + std::string(11, 'b'),
                             std::string(11, 'a') + std::string(1, 'b')});
    assert(g.size() == 2);
    std::printf("  PASS %-26s a+11b vs 11a+b stay apart\n", "key separator");
    ++checks;

    std::printf("\n  %d checks passed\n", checks);
    return 0;
}
