// Package validparentheses solves valid-parentheses. Time O(n), Space O(n).
//
// Go has no stack type. A slice is the stack: append pushes, the last element
// is the top, and reslicing pops. Nothing here is hidden behind a library call,
// which is the point of doing it in Go.
package validparentheses

// IsValid reports whether s is a balanced, correctly nested sequence of ()[]{}.
func IsValid(s string) bool {
	opener := map[byte]byte{')': '(', ']': '[', '}': '{'}
	stack := make([]byte, 0, len(s)/2+1)
	for i := 0; i < len(s); i++ {
		c := s[i]
		if want, isCloser := opener[c]; isCloser {
			if len(stack) == 0 || stack[len(stack)-1] != want {
				return false // empty stack, or the top is the wrong type
			}
			stack = stack[:len(stack)-1] // pop
		} else if c == '(' || c == '[' || c == '{' {
			stack = append(stack, c) // push
		} else {
			return false // outside the spec
		}
	}
	return len(stack) == 0
}
