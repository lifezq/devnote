package main

import (
	"testing"
)

func TestArraySlice(t *testing.T) {
	a1 := [10]int{}
	t.Logf("a1.len:%d", len(a1))
	a1[0] = 1
	a1[1] = 2
	a1[2] = 3
	t.Logf("%v", a1)
	//删除数据元素
	a1[1] = 0
	t.Logf("%v", a1)

	s1 := []int{}
	t.Logf("s1.len:%d s1.cap:%d", len(s1), cap(s1))
	s1[0] = 1 //panic: runtime error: index out of range [0] with length 0
	s1[1] = 2 //panic: runtime error: index out of range [0] with length 0
	s1[2] = 3 //panic: runtime error: index out of range [0] with length 0
	t.Logf("%v", s1)
}
