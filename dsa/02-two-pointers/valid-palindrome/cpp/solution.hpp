#pragma once
#include <cctype>
#include <string_view>

// valid-palindrome. Time O(n), Space O(1).
//
// std::string_view, not std::string: a view borrows, so calling this cannot
// copy the caller's string and cannot modify it. Taking `const std::string&`
// would also avoid the copy but would refuse a `const char*` without building
// one. This is C++'s nearest thing to Rust's &str.
inline bool is_palindrome(std::string_view s) {
    if (s.empty()) return true;
    std::size_t i = 0, j = s.size() - 1;
    while (i < j) {
        // Both skips re-check i < j: without it ".,!" walks past the end, and
        // with unsigned indices j-- at zero wraps rather than going negative.
        while (i < j && !std::isalnum(static_cast<unsigned char>(s[i]))) ++i;
        while (i < j && !std::isalnum(static_cast<unsigned char>(s[j]))) --j;
        if (std::tolower(static_cast<unsigned char>(s[i])) !=
            std::tolower(static_cast<unsigned char>(s[j]))) return false;
        ++i;
        if (j == 0) break;
        --j;
    }
    return true;
}
