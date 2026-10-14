#include "solution.hpp"
#include <cassert>
#include <climits>
#include <cstdio>
#include <string>
#include <vector>

static int checks = 0;
static void expect(const char* name, std::vector<int> a, int t,
                   std::optional<std::size_t> want) {
    auto got = search(a, t);
    if (got != want) { std::printf("  FAIL %-24s\n", name); assert(false); }
    if (got) assert(a[*got] == t);
    std::printf("  PASS %-24s %s\n", name,
                got ? std::to_string(*got).c_str() : "none");
    ++checks;
}

int main() {
    expect("empty array", {}, 5, std::nullopt);
    expect("one element present", {5}, 5, 0);
    expect("one element absent", {5}, 3, std::nullopt);
    expect("target is first", {1,2,3,4,5}, 1, 0);
    expect("target is last", {1,2,3,4,5}, 5, 4);
    expect("absent below range", {1,2,3}, 0, std::nullopt);
    expect("absent above range", {1,2,3}, 9, std::nullopt);
    expect("absent in a gap", {1,3,5,7}, 4, std::nullopt);
    expect("two elements", {1,2}, 2, 1);
    expect("negatives", {-5,-3,-1}, -3, 1);
    expect("extreme values", {INT_MIN,0,INT_MAX}, INT_MAX, 2);
    expect("extreme low", {INT_MIN,0,INT_MAX}, INT_MIN, 0);

    std::vector<int> big(10000);
    for (std::size_t i = 0; i < big.size(); ++i) big[i] = static_cast<int>(i * 2);
    for (std::size_t i = 0; i < big.size(); ++i) {
        assert(search(big, static_cast<int>(i * 2)) == i);
        assert(!search(big, static_cast<int>(i * 2 + 1)));
    }
    std::printf("  PASS %-24s\n", "10k: all found/rejected"); ++checks;

    auto [idx, steps] = search_counting(big, big.back());
    assert(steps <= 14);
    std::printf("  PASS %-24s (%d steps for n=10000)\n", "is logarithmic", steps); ++checks;

    for (int k = 0; k < 12; ++k) {                 // invariant 2: terminates
        std::vector<int> small(static_cast<std::size_t>(k));
        for (int i = 0; i < k; ++i) small[static_cast<std::size_t>(i)] = i;
        for (int t = -2; t < k + 3; ++t) (void)search(small, t);
    }
    std::printf("  PASS %-24s\n", "terminates everywhere"); ++checks;

    std::printf("\n  %d checks passed\n", checks);
    return 0;
}
