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
  Int a = readln.split.map!(to!Int).reduce!((a, b) => a + b);
  Int b = readln.split.map!(to!Int).reduce!((a, b) => a + b);
  int n = readln.split.map!(to!int).array[0];
  debug writeln(a);
  debug writeln(b);
  debug writeln(n);

  auto rem = new Int[n];

  {
    rem[] = 5;
    while ( a > 0 && ! rem.empty ) {
      if ( rem.empty ) {
        writeln("NO");
        return;
      }
      auto d = min(a, 5);
      a -= d;
      rem.front -= d;
      if ( rem.front <= 0 ) {
        rem.popFront();
      }
    }
    if ( ! rem.empty && rem.front < 5 ) {
      rem.popFront();
    }
  }

  debug writeln(rem);

  {
    rem[] = 10;
    while ( b > 0 && ! rem.empty ) {
      if ( rem.empty ) {
        writeln("NO");
        return;
      }
      auto d = min(b, 10);
      b -= d;
      rem.front -= d;
      if ( rem.front <= 0 ) {
        rem.popFront();
      }
    }
    if ( ! rem.empty && rem.front < 10 ) {
      rem.popFront();
    }
  }

  if ( a > 0 || b > 0 ) {
    writeln("NO");
  } else {
    writeln("YES"); 
  }
}
