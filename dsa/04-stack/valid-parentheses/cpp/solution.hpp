#pragma once
#include <stack>
#include <string_view>

// valid-parentheses. Time O(n), Space O(n).
//
// std::stack is an ADAPTOR over a deque, not a separate data structure. The
// standard library builds a stack out of a sequence and restricts its
// interface -- which is the discipline this problem is about, in library form.
inline bool is_valid(std::string_view s) {
    std::stack<char> st;
    for (char c : s) {
        switch (c) {
            case '(': case '[': case '{':
                st.push(c);
                break;
            case ')': case ']': case '}': {
                // top() on an empty std::stack is undefined behaviour, so the
                // empty check must come first.
                if (st.empty()) return false;
                const char open = st.top();
                st.pop();
                if ((c == ')' && open != '(') ||
                    (c == ']' && open != '[') ||
                    (c == '}' && open != '{'))
                    return false;
                break;
            }
            default:
                return false;   // not a bracket: outside the spec
        }
    }
    return st.empty();
}
