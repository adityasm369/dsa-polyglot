// Tests from SPEC.md. assert, not a framework: nothing to install, and the
// students can read the whole harness.
#include "solution.hpp"
#include <cassert>
#include <cstdio>

static int checks = 0;

static void expect(const char* name, std::vector<int> nums, long long target,
                   int wi, int wj) {
    const std::vector<int> before = nums;
    auto got = two_sum(nums, target);
    if (!got || got->first != wi || got->second != wj) {
        std::printf("  FAIL %-26s want (%d,%d)\n", name, wi, wj);
        assert(false);
    }
    assert(got->first < got->second);
    assert(static_cast<long long>(nums[got->first]) + nums[got->second] == target);
    assert(nums == before);                       // invariant 3
    std::printf("  PASS %-26s (%d,%d)\n", name, got->first, got->second);
    ++checks;
}

int main() {
    expect("minimum size",          {1, 2},             3,          0, 1);
    expect("answer at the ends",    {3, 2, 4, 1},       4,          0, 3);
    expect("duplicate values",      {3, 3},             6,          0, 1);
    expect("same value, one pair",  {3, 2, 3},          6,          0, 2);
    expect("negatives",             {-1, -2, -3, -4},   -6,         1, 3);
    expect("zero target and zeros", {0, 0},             0,          0, 1);
    expect("overflow guard",        {1000000000, 1000000000}, 2000000000LL, 0, 1);
    expect("answer in the middle",  {1, 5, 2, 7, 3},    9,          2, 3);

    assert(!two_sum({1, 2, 3}, 100).has_value());
    std::printf("  PASS %-26s\n", "no pair -> nullopt"); ++checks;
    assert(!two_sum({1}, 1).has_value());
    std::printf("  PASS %-26s\n", "n<2 -> nullopt"); ++checks;

    std::vector<int> big(2000);
    for (int i = 0; i < 2000; ++i) big[i] = i;
    expect("2000 keys", std::move(big), 1999 + 1998, 1998, 1999);

    std::printf("\n  %d checks passed\n", checks);
    return 0;
}
