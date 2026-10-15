#pragma once
#include <array>
#include <string>
#include <unordered_map>
#include <vector>

// group-anagrams. Time O(n*k), Space O(n*k).
//
// A detail worth stopping on: std::array<int,26> would be the natural key, and
// it works with std::map, which only needs operator< -- std::array has one. It
// does NOT work with std::unordered_map, because the standard library ships no
// std::hash specialisation for std::array. You either write the specialisation
// or encode the counts into a type that is already hashable. This uses a short
// std::string, which keeps the example to one idea.
inline std::vector<std::vector<std::string>>
group_anagrams(const std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::size_t> index;  // key -> slot in out
    std::vector<std::vector<std::string>> out;

    for (const auto& s : strs) {
        std::array<int, 26> counts{};
        for (unsigned char c : s) {
            if (c >= 'a' && c <= 'z') counts[c - 'a']++;
        }
        // '#' separates the fields so {1,11} and {11,1} cannot encode alike.
        std::string key;
        key.reserve(52);
        for (int n : counts) {
            key += std::to_string(n);
            key += '#';
        }
        auto it = index.find(key);
        if (it == index.end()) {
            index.emplace(std::move(key), out.size());
            out.push_back({s});
        } else {
            out[it->second].push_back(s);
        }
    }
    return out;
}
