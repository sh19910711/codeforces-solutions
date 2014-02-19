#include <iostream>
using namespace std;

typedef long long Int;

Int f( const Int& n, const Int& u, const Int& d ) {
  if ( n <= 0 )
    return u;
  return f(n - 1, u * 3 + d * 1, u * 1 + d * 3);
}

int main() {
  for ( int i = 1; i <= 10; ++ i ) {
    cout << f(i, 1, 0) << ",";
  }
  cout << endl;
  return 0;
}
