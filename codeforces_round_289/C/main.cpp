#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

typedef long long Int;
typedef vector<Int> IntVector;
const Int N_MAX = 300 + 11;

Int N;
Int B[N_MAX];

bool input() {
  if ( cin >> N ) {
    for ( int i = 0; i < N; ++ i ) {
      cin >> B[i];
    }
    return true;
  }
  return false;
}

struct LessThan {
  bool operator()(const string& l, const string& r) const {
    return false;
  }
};

typedef IntVector Node;
typedef priority_queue<string, vector<string>, LessThan> Queue;

IntVector f(Int sum) {
  IntVector res(10, 0);
  for ( int i = 9; i >= 1; -- i ) {
    res[i] = sum / i;
    sum -= res[i] * i;
  }
  return res;
}

char min_char(IntVector& v) {
  for ( int i = 1; i <= 9; ++ i ) {
    if ( v[i] > 0 ) {
      v[i] --;
      return '0' + i;
    }
  }
  return ' ';
}

string g(IntVector v) {
  string res = string() + min_char(v);
  cout << res << endl;
  for ( int i = 0; i <= 9; ++ i ) {
    Int x = v[i];
    while ( x ) {
      res += string() + (char)('0' + i);
      x --;
    }
  }
  return res;
}

void print( const IntVector& v ) {
  for ( auto& x : v ) {
    cout << x << ", ";
  }
  cout << endl;
}

void solve() {
  cout << g(f(300)) << endl;
  for ( int i = 0; i < N; ++ i ) {
    // print(f(B[i]));
  }
  cout << endl;
}

int main() {
  while ( input() ) {
    solve();
  }
  return 0;
}
