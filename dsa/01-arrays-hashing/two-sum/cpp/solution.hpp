#pragma once
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

// Time O(n) average, Space O(n).
//
// `const&` on the input: invariant 3 says the array is not modified, and in C++
// the compiler can enforce that rather than a test having to check it.
// std::optional rather than a sentinel pair: "no answer" is a different kind of
// thing from an answer, and the type should say so.
inline std::optional<std::pair<int, int>>
two_sum(const std::vector<int>& nums, long long target) {
    if (nums.size() < 2) return std::nullopt;

    std::unordered_map<long long, int> seen;   // value -> first index seen at
    seen.reserve(nums.size() * 2);             // avoid rehashing mid-loop
    for (int j = 0; j < static_cast<int>(nums.size()); ++j) {
        // long long, deliberately: nums[j] reaches 1e9 and target reaches 2e9,
        // so this subtraction overflows int32 at the spec's limits.
        const long long want = target - static_cast<long long>(nums[j]);
        if (auto it = seen.find(want); it != seen.end())
            return std::make_pair(it->second, j);   // it->second < j, so i < j
        // emplace, not operator[]: on a duplicate the first index must win, and
        // emplace leaves an existing key alone. operator[] would overwrite it
        // and [3,3] would return (1,1).
        seen.emplace(static_cast<long long>(nums[j]), j);
    }
    return std::nullopt;
}
