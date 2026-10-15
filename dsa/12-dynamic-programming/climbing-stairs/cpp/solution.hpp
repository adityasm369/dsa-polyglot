#pragma once
#include <cstdint>

// climbing-stairs. Time O(n), Space O(1).
//
// std::uint64_t for the accumulator: n = 45 fits in 32 bits, but the same
// recurrence overflows signed 64-bit at n = 92. Signed overflow is undefined
// behaviour in C++; unsigned wraps, which is at least defined, and the spec's
// constraint keeps the answer far below that.
inline std::uint64_t climb_stairs(int n) {
    if (n <= 2) return n < 1 ? 0 : static_cast<std::uint64_t>(n);
    std::uint64_t prev = 1, cur = 2;
    for (int i = 3; i <= n; ++i) {
        const std::uint64_t next = prev + cur;
        prev = cur;
        cur = next;
    }
    return cur;
}
