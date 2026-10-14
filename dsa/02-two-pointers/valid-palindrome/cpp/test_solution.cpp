#include "solution.hpp"
#include <cassert>
#include <cstdio>
#include <string>

static int checks = 0;
static void expect(const char* name, std::string_view s, bool want) {
    bool got = is_palindrome(s);
    if (got != want) { std::printf("  FAIL %-24s\n", name); assert(false); }
    std::printf("  PASS %-24s %s\n", name, want ? "true" : "false");
    ++checks;
}

int main() {
    expect("empty", "", true);
    expect("one character", "a", true);
    expect("only punctuation", ".,!", true);
    expect("mixed case", "Aa", true);
    expect("digits count", "0P", false);
    expect("the textbook one", "A man, a plan, a canal: Panama", true);
    expect("nearly", "race a car", false);
    expect("all skipped but one", "...a...", true);
    expect("spaces only", "   ", true);
    expect("digits palindrome", "12321", true);
    expect("digits not", "12345", false);
    expect("200k characters", std::string(200000, 'a'), true);
    std::printf("\n  %d checks passed\n", checks);
    return 0;
}
