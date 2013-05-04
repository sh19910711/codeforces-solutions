package main

import "fmt"

func get_string( s string ) string {
    n := len(s)
    if n > 10 {
        return fmt.Sprintf("%c%s%c", s[0], fmt.Sprintf("%d", n - 2), s[n - 1])
    }
    return s
}

func main() {
    var n int
    fmt.Scanf("%d\n", &n)
    for i := 0; i < n; i ++ {
        var s string
        fmt.Scanf("%s\n", &s)
        fmt.Printf("%s\n", get_string(s))
    }
}

