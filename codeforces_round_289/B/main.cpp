#include <iostream>
#include <algorithm>
#include <array>
using namespace std;

const int SIZE = 100 + 11;

typedef long long Int;
typedef array<Int, SIZE> IntArray;

Int N;
Int K;
IntArray A;

bool input() {
  if ( cin >> N >> K ) {
    for ( int i = 0; i < N; ++ i ) {
      cin >> A[i];
    }
    return true;
  }
  return false;
}

bool check() {
  for ( int i = 1; i <= K; ++ i ) {
    IntArray cnt;
    for ( int j = 0; j < N; ++ j ) {
      cnt[j] = 0;
      for ( int k = 0; k < A[j]; ++ k ) {
        if ( ( k % K + 1 ) == i ) {
          cnt[j] ++;
        }
      }
    }
    if ( *max_element(begin(cnt), begin(cnt) + N) - *min_element(begin(cnt), begin(cnt) + N) > 1 ) return false;
  }
  return true;
}

bool solve() {
  return check();
}

int main() {
  while ( input() ) {
    if ( solve() ) {
      cout << "YES" << endl;
      for ( int i = 0; i < N; ++ i ) {
        for ( int j = 0; j < A[i]; ++ j ) {
          cout << j % K + 1 << " ";
        }
        cout << endl;
      }
    } else {
      cout << "NO" << endl;
    }
  }
  return 0;
}
