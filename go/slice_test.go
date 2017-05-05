package main

import "testing"

// slice复制时，引用了旧slice指针，所以新slice值改变时，旧slice同时改变
// 避免:
// 1.新slice不要通过父slice指针复制，相反，逐个赋值到新slice
// 2.当新slice长度超过旧slice容量时，会为新slice重新分配一个内存块用来存储更多的元素，
//  同时将旧slice元素复制进来, 此后，新slice再做任何改变都不会影响旧slice

func TestSlice00(t *testing.T) {
	s := make([]int, 3)
	s = []int{1, 2, 3}

	s1 := make([]int, 2)
	// s1 = s[1:3]

	t.Logf("len:%d cap:%d s:%v\n", len(s), cap(s), s)     // len:3 cap:3 s:[1 2 3]
	t.Logf("len:%d cap:%d s1:%v\n", len(s1), cap(s1), s1) // len:2 cap:2 s1:[0 0]

	s1[0] = s[0]
	t.Logf("s:%v\n", s)   // s:[1 2 3]
	t.Logf("s1:%v\n", s1) // [1,0]

	s2 := s[2:]
	s2[0] = 888
	t.Logf("len:%d cap:%d s2:%v\n", len(s2), cap(s2), s2) // len:1 cap:1 s2:[888]
	t.Logf("len:%d cap:%d s:%v\n", len(s), cap(s), s)     // len:3 cap:3 s:[1 2 888]

	//ss := [...]int{1, 2, 3}
	//t.Logf("len:%d cap:%d ss:%v\n", len(ss), cap(ss), ss)

	sss := []int{1, 2, 3, 4, 5}
	sss1 := sss[2:4]
	t.Logf("len:%d cap:%d p:%v sss1:%v\n", len(sss1), cap(sss1), &sss1[0], sss1)

	//sss1[2] = 3333 // index out of range
	sss1 = append(sss1, 3333)
	sss1 = append(sss1, 4444)
	sss1[0] = 9999999999

	t.Logf("len:%d cap:%d p:%v sss1:%v\n", len(sss1), cap(sss1), &sss1[0], sss1)
	t.Logf("len:%d cap:%d p:%v sss:%v\n", len(sss), cap(sss), &sss[2], sss)
}

func TestSlice0(t *testing.T) {

	s := []int{1, 2, 3}

	s1 := s[1:3]

	t.Logf("len:%d cap:%d s:%v\n", len(s), cap(s), s)     // [1,2,3]
	t.Logf("len:%d cap:%d s1:%v\n", len(s1), cap(s1), s1) // [2,3]

	s1[0] = 99
	t.Logf("s:%v\n", s)   // [1,99,3]
	t.Logf("s1:%v\n", s1) // [99,3]
}

// len cap
// 每次长度饱和后，再向其加入新元素，会申请容量，
// 每次申请的容量是上次容量的两倍
// append 时，会从当前已有(已分配)长度向下追加，当容量不够时，申请容量

func TestSlice1(t *testing.T) {

	s := make([]int, 4, 4)
	if cap(s) != 4 {
		t.Errorf("Cap Error : %d\n", cap(s))
	}

	t.Logf("len:%d cap:%d s:%v\n", len(s), cap(s), s)
	// len:4 cap:4 s:[0 0 0 0]

	s = append(s, []int{1, 2, 3, 4}...)

	t.Logf("len:%d cap:%d s:%v\n", len(s), cap(s), s)
	// len:8 cap:8 s:[0 0 0 0 1 2 3 4]

	s = append(s, 5)
	t.Logf("len:%d cap:%d s:%v\n", len(s), cap(s), s)
	// len:9 cap:16 s:[0 0 0 0 1 2 3 4 5]

	s = append(s, []int{6, 7, 8, 9, 10, 11, 12, 13}...)
	t.Logf("len:%d cap:%d s:%v\n", len(s), cap(s), s)
	// len:17 cap:32 s:[0 0 0 0 1 2 3 4 5 6 7 8 9 10 11 12 13]
}

func TestSlice2(t *testing.T) {

	s := make([]int, 4, 4)
	if cap(s) != 4 {
		t.Errorf("Cap Error : %d\n", cap(s))
	}

	t.Logf("len:%d cap:%d s:%v\n", len(s), cap(s), s)
	// len:4 cap:4 s:[0 0 0 0]

	s1 := s[2:]

	s1[0] = 111
	t.Logf("len:%d cap:%d s1:%v\n", len(s1), cap(s1), s1)
	// len:4 cap:4 s1:[111 0]

	s1 = append(s1, []int{88, 99}...)

	t.Logf("len:%d cap:%d s1:%v\n", len(s1), cap(s1), s1)
	// len:4 cap:4 s1:[111 0 88 99]

	t.Logf("len:%d cap:%d s:%v\n", len(s), cap(s), s)
	// len:4 cap:4 s:[0 0 111 0]
}
