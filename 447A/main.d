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
import std.conv;

alias Int = long;

void main() {
  int p, n;
  readf(" %s", &p);
  readf(" %s", &n);
  auto list = new bool[300 + 1];
  list[] = false;
  foreach ( i; 0 .. n ) {
    Int x;
    readf(" %s", &x);
    if ( list[x % p] ) {
      writeln(i + 1);
      return;
    }
    list[x % p] = true;
  }
  writeln(-1);
}
