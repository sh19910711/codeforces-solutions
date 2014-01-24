#include <iostream>
using namespace std;

const int SIZE = 10000000 + 11;
bool v[SIZE];
int p[SIZE];
int pc;

int main() {
  std::fill(v, v + SIZE, false);
  v[2] = true;
  for ( int i = 3; i < SIZE; i += 2 )
    v[i] = true;
  for ( int i = 3; i < SIZE; i += 2 ) {
    if ( ! v[i] )
      continue;
    for ( int j = i + i; j < SIZE; j += i )
      v[j] = false;
  }

  int cnt = 0;
  for ( int i = 0; i < SIZE; ++ i ) {
    if ( v[i] ) {
      cnt ++;
    }
  }
  cout << "cnt = " << cnt << endl;

  pc = 0;
  for ( int i = 0; i < SIZE; ++ i ) {
    if ( v[i] ) {
      p[pc ++] = i;
    }
  }

  int cnt2 = 0;
  for ( int i = 0; i < pc; ++ i ) {
    for ( int j = p[i]; j < SIZE; j += p[i] ) {
      cnt2 ++;
    }
  }
  cout << cnt2 << endl;

  return 0;
}

