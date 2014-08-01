import std.stdio;
import std.string;
import std.bigint;
import std.array;
import std.ascii;
import std.math;
import std.numeric;
import std.algorithm;
import std.container;
import core.bitop;

alias Int = long;
immutable Int N_MAX = pow(10, 2) + 11;

void main() {
  int n;
  int m;
  auto a = new Int [N_MAX];
  readf(" %s", &n);
  readf(" %s", &m);
  a.length = n;
  foreach (	i; 0 .. n ) {
    readf(" %s", &a[i]);
  }

  auto c = new Int [n];
  foreach ( i; 0 .. n ) {
    c[i] = i + 1;
  }
  

  debug writeln(a);
  debug writeln(c);

  while ( ! a.empty ) {
    if ( a.length == 1 ) {
      writeln(c.front);
      break;
    }
    a[0] -= m;
    if ( a[0] <= 0 ) {
      a.popFront();
      c.popFront();
    } else {
      a ~= a.front;
      a.popFront();
      c ~= c.front;
      c.popFront();
    }
 }
}
