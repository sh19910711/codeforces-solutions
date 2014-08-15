import std.stdio;
import std.string;
import std.bigint;
import std.array;
import std.ascii;
import std.math;
import std.numeric;
import std.algorithm;
import std.container;
import std.conv;
import core.bitop;

alias Int = int;
immutable Int N_MAX = pow(10, 3) + 11;
immutable Int D_MAX = pow(10, 3) + 11;
immutable Int K_MAX = pow(10, 9) + 11;

Int T[D_MAX][N_MAX];

mixin template Inputter() {
  Int N;
  Int K;
  Int D;

  bool input(T)(T s) {
    if ( readf(" %s %s %s", &N, &K, &D) ) {
      debug writefln("N = %s, K = %s, D = %s", N, K, D);
      return true;
    }
    return false;
  }
}

mixin template Outputter() {
  bool ok;

  void output() {
    if ( ok ) {
      foreach ( i; 0 .. D ) {
        foreach ( j; 0 .. N ) {
          writef("%s ", T[i][j]);
        }
        writeln("");
      }
    } else {
      writefln("-1");
    }
  }
}

mixin template Solver() {
  void init() {
  }
  
  void solve() {
    foreach ( i; 0 .. D ) {
      T[i][0] = 1;
    }
    ok = find(1);
  }

  bool find( int c ) {
    debug writefln("@find: c = %s", c);
    if ( c >= N ) return true;
    foreach ( i; 0 .. D ) {
      T[i][c] = T[i][c - 1];
    }
    if ( ! add(c, 0) ) return false;
    return find(c + 1);
  }

  bool add( int c, int r ) {
    if ( r >= D ) return false;
    debug writefln("@add: c = %s, r = %s", c, r);
    if ( T[r][c] + 1 > K ) {
      T[r][c] = 1;
      return add(c, r + 1);
    }
    T[r][c] ++;
    return true;
  }
}

// Runner {{{
mixin template Runner() {
  void run() {
    while ( input(stdin) ) {
      init();
      solve();
      output();
    }
  }
}
// }}}

// Solution {{{
struct Solution {
  mixin Solver;
  mixin Inputter;
  mixin Outputter;
  mixin Runner;
}
// }}}

// main() {{{
Solution s;
void main() {
  s.run();
}
// }}}
