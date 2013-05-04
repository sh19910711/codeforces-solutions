package main

import . "fmt"

func get_string( s string ) string {
    n := len(s)
    if n > 10 {
        return Sprintf("%c%s%c", s[0], Sprintf("%d", n - 2), s[n - 1])
    }
    return s
}

func main() {
    var n int
    Scanf("%d\n", &n)
    for i := 0; i < n; i ++ {
        var s string
        Scanf("%s\n", &s)
        Printf("%s\n", get_string(s))
    }
}

