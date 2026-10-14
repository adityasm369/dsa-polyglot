#pragma once
#include <cstddef>
#include <optional>
#include <span>

// binary-search. Time O(log n), Space O(1).
//
// std::span, not const vector&: a span is a non-owning view over any
// contiguous range, so this works on a vector, a C array or a subrange without
// copying and without a template. It is C++'s answer to Rust's &[T].
//
// Signed overflow is undefined behaviour in C++ exactly as in C, so (lo+hi)/2
// is not merely wrong, it is the kind of wrong an optimiser is licensed to
// exploit. -fsanitize=undefined catches it; `make asan` is one command away.
inline std::optional<std::size_t> search(std::span<const int> nums, int target) {
    if (nums.empty()) return std::nullopt;
    std::size_t lo = 0, hi = nums.size() - 1;
    for (;;) {
        const std::size_t mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) {
            if (mid == hi) return std::nullopt;   // unsigned: no -1 to lean on
            lo = mid + 1;
        } else {
            if (mid == lo) return std::nullopt;
            hi = mid - 1;
        }
    }
}

inline std::pair<std::optional<std::size_t>, int>
search_counting(std::span<const int> nums, int target) {
    int steps = 0;
    if (nums.empty()) return {std::nullopt, 0};
    std::size_t lo = 0, hi = nums.size() - 1;
    for (;;) {
        ++steps;
        const std::size_t mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return {mid, steps};
        if (nums[mid] < target) { if (mid == hi) return {std::nullopt, steps}; lo = mid + 1; }
        else                    { if (mid == lo) return {std::nullopt, steps}; hi = mid - 1; }
    }
}
