#include "solution.hpp"
#include <cassert>
#include <cstdio>

static int checks = 0;
static void expect(int n, std::uint64_t want) {
    auto got = climb_stairs(n);
    if (got != want) { std::printf("  FAIL n=%d\n", n); assert(false); }
    std::printf("  PASS n=%-3d %llu\n", n, static_cast<unsigned long long>(got));
    ++checks;
}

int main() {
    expect(1, 1); expect(2, 2); expect(3, 3); expect(4, 5);
    expect(5, 8); expect(10, 89); expect(45, 1836311903ULL);
    for (int n = 1; n <= 45; ++n) assert(climb_stairs(n) > 0);
    std::printf("  PASS every n in 1..45 is positive\n"); ++checks;
    std::printf("\n  %d checks passed\n", checks);
    return 0;
}
