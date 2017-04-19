package main

import "fmt"

type S struct {
        a, b int
}

// String 实现了接口 fmt.Stringer
func (s *S) String() string {
        return fmt.Sprintf("%s", s) // 调用 Sprintf 时会默认调用 s.String()
}

func main() {
        s := &S{a: 1, b: 2}
        fmt.Println(s) //由内部调用String产生循环调用! 栈溢出！
}
