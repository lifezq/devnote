package main

import "testing"

func TestBigEndian(t *testing.T) {
	v := 0x12345678
	var b int8
	b = int8(v)
	if b == 0x12 {
		t.Log("it's big endian")
	} else {
		t.Log("it's small endian")
	}
}
