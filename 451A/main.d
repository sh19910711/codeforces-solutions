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

void main() {
  Int n, m;
  readf(" %s", &n);
  readf(" %s", &m);
  if ( min(n, m) % 2 == 0 ) {
    writeln("Malvika");
  } else {
    writeln("Akshat");
  }
}
