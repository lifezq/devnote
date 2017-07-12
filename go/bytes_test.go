package main

import (
	"bytes"
	"testing"
)

func TestBytesBuffer(t *testing.T) {

	var (
		b   [10]byte
		b2  [20]byte
		buf = bytes.NewBuffer(b[:])
	)

	buf.Write([]byte{0x01, 0x02})
	t.Logf("buf:%v\n", buf.Bytes())
	// output: buf:[0 0 0 0 0 0 0 0 0 0 1 2]

	n, err := buf.Read(b2[:])
	t.Logf("n:%d err:%v b2:%v\n", n, err, b2)
	// output: n:12 err:<nil> b2:[0 0 0 0 0 0 0 0 0 0 1 2 0 0 0 0 0 0 0 0]
}
