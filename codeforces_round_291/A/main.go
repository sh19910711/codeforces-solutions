package main

// @snippet <contest.go#0.0.0:header/import.go>
import "fmt"
import "io"
import "os"
import "strings"
import "text/scanner"
// @snippet <contest.go#0.0.0:header/typedef.go>
type Int int64
type IntSlice []Int
// @snippet <contest.go#0.0.0:utils/read.go>
var sc scanner.Scanner

func ReadInt(n *Int) bool {
  tok := sc.Scan()
  if tok != scanner.EOF {
    fmt.Sscan(sc.TokenText(), &n)
    return true
  } else {
    return false
  }
}

func ReadString(s *string) bool {
  tok := sc.Scan()
  if tok != scanner.EOF {
    *s = sc.TokenText()
    return true
  } else {
    return false
  }
}
// @snippet <contest.go#0.0.0:utils/stream.go>
func Stdin() io.Reader {
  return os.Stdin
}

func Strin(s string) io.Reader {
  return strings.NewReader(s)
}
// @snippet <contest.go#0.0.0:main.go>

func min(a rune, b rune) rune {
  if a < b {
    return a
  } else {
    return b
  }
}

func findMin(s string) string {
  res := ""
  for i, c := range s {
    if i == 0 && c == '9' {
      res += "9"
    } else {
      res += string(min(c, '9' - c + '0'))
    }
  }
  return res
}

func main() {
  sc.Init(Stdin())
  var s string
  for ReadString(&s) {
    fmt.Println(findMin(s))
  }
}

