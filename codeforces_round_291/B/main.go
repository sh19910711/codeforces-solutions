package main

// @snippet <contest.go#0.0.1:header/import.go>
import "fmt"
import "io"
import "os"
import "strings"
// @snippet <contest.go#0.0.1:header/typedef.go>
type Int int64
type IntSlice []Int
// @snippet<contest.go#0.0.1:utils/read.go>
var in io.Reader

func ReadInt(n *Int) bool {
  _, err := fmt.Fscan(in, n)
  return err != io.EOF
}

func ReadString(s *string) bool {
  _, err := fmt.Fscan(in, s)
  return err != io.EOF
}

// @snippet <contest.go#0.0.1:utils/stream.go>
func Stdin() io.Reader {
  return os.Stdin
}

func Strin(s string) io.Reader {
  return strings.NewReader(s)
}
// @snippet <contest.go#0.0.1:utils/min.go>

func MinRune(a rune, b rune) rune {
  if a < b {
    return a
  } else {
    return b
  }
}

func MinInt(a Int, b Int) Int {
  if a < b {
    return a
  } else {
    return b
  }
}
// @snippet <contest.go#0.0.1:main.go>

func GcdInt(a Int, b Int) Int {
  if b == 0 {
    return a
  } else {
    return GcdInt(b, a % b)
  }
}

type Solver struct {
  N Int
  X0 Int
  Y0 Int
  X IntSlice
  Y IntSlice
}

func (s *Solver) input() bool {
  if ReadInt(&s.N) {
    if ReadInt(&s.X0) && ReadInt(&s.Y0) {
      s.X = make(IntSlice, s.N)
      s.Y = make(IntSlice, s.N)
      for i := Int(0); i < s.N; i += 1 {
        ReadInt(&s.X[i])
        ReadInt(&s.Y[i])
        s.X[i] -= s.X0
        s.Y[i] -= s.Y0
      }
      return true
    }
  }
  return false
}

type pos struct {
  X Int
  Y Int
}

func AbsInt(x Int) Int {
  if x > 0 {
    return x
  } else {
    return -x
  }
}

func main() {
  in = Stdin()
  s := &Solver{}
  for s.input() {
    m := make(map[pos]bool)
    for i := Int(0); i < s.N; i += 1 {
      if s.X[i] == 0 && s.Y[i] == 0 {
        p := pos{0, 0}
        m[p] = true
      } else if s.X[i] == 0 {
        p := pos{0, 1}
        m[p] = true
      } else if s.Y[i] == 0 {
        p := pos{1, 0}
        m[p] = true
      } else {
        g := GcdInt(s.X[i], s.Y[i])
        p := pos{s.X[i] / g, s.Y[i] / g}
        m[p] = true
      }
    }
    offset := 0
    if m[pos{0, 0}] && (m[pos{0, 1}] || m[pos{1, 0}]) {
      offset = 1
    }
    fmt.Println(len(m) - offset)
  }
}

