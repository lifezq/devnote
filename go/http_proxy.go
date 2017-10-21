package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
)

func main() {

	http.HandleFunc("/proxy", func(w http.ResponseWriter, r *http.Request) {

		urlString := r.URL.String()
		if len(urlString) > 11 {
			fmt.Fprintf(w, "Hello, %s", r.URL.Path)
			return
		}

		req, err := http.NewRequest("GET", urlString[11:], nil)

		req.Header.Add("Accept", r.Header.Get("Accept"))
		req.Header.Add("Accept-Language", r.Header.Get("Accept-Language"))
		req.Header.Add("Cache-Control", r.Header.Get("Cache-Control"))
		req.Header.Add("User-Agent", r.Header.Get("User-Agent"))
		req.Header.Add("Cookie", r.Header.Get("Cookie"))

		client := &http.Client{}
		resp, err := client.Do(req)
		if err != nil {
			fmt.Fprintf(w, "Something error %s", err.Error())
			return
		}
		defer resp.Body.Close()
		body, err := ioutil.ReadAll(resp.Body)
		if err != nil {
			fmt.Fprintf(w, "Something error %s", err.Error())
			return
		}

		w.Header().Set("Content-Type", resp.Header.Get("Content-Type"))
		w.Header().Set("Set-Cookie", resp.Header.Get("Set-Cookie"))
		w.Header().Set("Expires", resp.Header.Get("Expires"))
		w.Header().Set("Cache-Control", resp.Header.Get("Cache-Control"))
		w.Header().Set("X-Powered-By", resp.Header.Get("X-Powered-By"))
		w.Header().Set("Vary", resp.Header.Get("Vary"))
		fmt.Fprint(w, string(body))
	})

	log.Fatal(http.ListenAndServe(":8081", nil))
}
