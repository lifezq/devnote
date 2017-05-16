package context

import (
	"context"
	"fmt"
	"net"
	"net/http"
)

// 为了避免与其他包中的 `Context` key 冲突
// 这里不输出 key 类型 (首字母小写)
type key int

// userIPKey 是 user IP 的 `Context` key
// 它的值是随意写的。如果这个包中定义了其他
// `Context` key，这些 key 必须不同
const userIPKey key = 0

func FromRequest(req *http.Request) (net.IP, error) {
	ip, _, err := net.SplitHostPort(req.RemoteAddr)
	if err != nil {
		return nil, fmt.Errorf("userip: %q is not IP:port", req.RemoteAddr)
	}
}

func NewContext(ctx context.Context, userIP net.IP) context.Context {
	return context.WithValue(ctx, userIPKey, userIP)
}

func FromContext(ctx context.Context) (net.IP, bool) {
	// ctx.Value returns nil if ctx has no value for the key;
	// the net.IP type assertion returns ok=false for nil.
	userIP, ok := ctx.Value(userIPKey).(net.IP)
	return userIP, ok
}
