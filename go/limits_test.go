package main

import (
	"testing"

	"github.com/lifezq/goutils/math"
)

func TestLimits(t *testing.T) {
	t.Logf("int8   max:%d\n", math.INT8_MAX)
	t.Logf("uint8  max:%d\n", math.UINT8_MAX)
	t.Logf("int16  max:%d\n", math.INT16_MAX)
	t.Logf("uint16 max:%d\n", math.UINT16_MAX)
	t.Logf("int32  max:%d\n", math.INT32_MAX)
	t.Logf("uint32 max:%d\n", math.UINT32_MAX)
	t.Logf("int64  max:%d\n", math.INT64_MAX)
	t.Logf("uint64 max:%d\n", math.UINT64_MAX)
}
