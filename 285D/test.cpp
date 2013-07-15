#include <iostream>
using namespace std;

const int SIZE = 100;
int n;
int cnt;
int A[SIZE];
int B[SIZE];
int C[SIZE];

bool is_permutation_sum( int sum ) {
  return sum == ( 1 << n ) - 1;
}

void find( int k, int asum, int bsum ) {
  if ( k >= n ) {
    if ( is_permutation_sum(asum) && is_permutation_sum(bsum) ) {
      int csum = 0;
      for ( int i = 0; i < n; ++ i ) {
        C[i] = ( A[i] + B[i] - 2 ) % n + 1;
        csum |= 1 << ( C[i] - 1 );
      }
      if ( is_permutation_sum(csum) ) {
        cnt ++;
      }
    }

    return;
  }

  for ( int a = 1; a <= n; ++ a ) {
    for ( int b = 1; b <= n; ++ b ) {
      A[k] = a;
      B[k] = b;
      int ba = 1 << ( a - 1 );
      int bb = 1 << ( b - 1 );
      find(k + 1, asum | ba, bsum | bb );
    }
  }
}

int main() {
  for ( n = 3; n <= 7; n += 2 ) {
    cnt = 0;
    find(0, 0, 0);
    cout << n << ": " << cnt << endl;
  }
  return 0;
}

