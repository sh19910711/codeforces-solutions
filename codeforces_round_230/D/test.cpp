#include <iostream>
using namespace std;

typedef long long Int;

Int hanoi( const Int& N, const Int& A, const Int& B, const Int& C ) {
  Int res = 0;
  if ( N > 0 ) {
    res += hanoi(N - 1, A, C, B) + 1;
    res += hanoi(N - 1, C, B, A) + 1;
  }
  return res;
}

int main() {
  std::cout << hanoi(40, 40, 0, 0) << std::endl;
  return 0;
}
