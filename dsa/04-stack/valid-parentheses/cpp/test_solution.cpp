#include "solution.hpp"
#include <cassert>
#include <cstdio>
#include <string>

static int checks = 0;
static void expect(const char* name, const std::string& s, bool want) {
    bool got = is_valid(s);
    if (got != want) { std::printf("  FAIL %s\n", name); assert(false); }
    std::printf("  PASS %-20s %s\n", name, want ? "valid" : "invalid");
    ++checks;
}

int main() {
    expect("single opener", "(", false);
    expect("single closer", ")", false);
    expect("simple", "()", true);
    expect("all three types", "()[]{}", true);
    expect("nested", "([{}])", true);
    expect("interleaved", "([)]", false);
    expect("closes too early", ")(", false);
    expect("left open", "(((", false);
    expect("empty string", "", true);
    expect("long balanced", std::string(5000, '(') + std::string(5000, ')'), true);
    std::printf("\n  %d checks passed\n", checks);
    return 0;
}
