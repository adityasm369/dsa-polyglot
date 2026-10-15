package climbingstairs

import "testing"

func TestSpecCases(t *testing.T) {
	for _, c := range []struct {
		n    int
		want int64
	}{{1, 1}, {2, 2}, {3, 3}, {4, 5}, {5, 8}, {10, 89}, {45, 1836311903}} {
		if got := ClimbStairs(c.n); got != c.want {
			t.Errorf("ClimbStairs(%d) = %d, want %d", c.n, got, c.want)
		}
	}
}

func TestEveryAnswerPositive(t *testing.T) {
	for n := 1; n <= 45; n++ {
		if ClimbStairs(n) <= 0 {
			t.Errorf("ClimbStairs(%d) not positive", n)
		}
	}
}

func BenchmarkClimbStairs(b *testing.B) {
	for i := 0; i < b.N; i++ {
		ClimbStairs(45)
	}
}
