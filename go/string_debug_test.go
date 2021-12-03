package main

import (
	"fmt"
	"testing"
)

type S struct {
	a, b int
}

// String 实现了接口 fmt.Stringer
func (s *S) String() string {
	return fmt.Sprintf("%d.%d", s.a, s.b) // 调用 Sprintf 时会默认调用 s.String()
}

func TestStringDebug(t *testing.T) {
	s := &S{a: 1, b: 2}
	t.Logf("%v", s) //由内部调用String产生循环调用! 栈溢出！
}
