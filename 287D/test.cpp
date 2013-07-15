#include <iostream>
#include <cstdio>
using namespace std;

const int SIZE = 1000;
int n;
int P[SIZE];

void print_p() {
  for ( int i = 0; i < n; ++ i )
    printf("%2d,", P[i]);
  cout << endl;
}

void f( int k ) {
  for ( int i = 0; i < n; i += k ) {
    int len = k;
    if ( i + k - 1 >= n )
      len = n % k;
    int tmp = P[i];
    for ( int j = 0; j < len - 1; ++ j )
      P[i + j] = P[i + j + 1];
    P[i + len - 1] = tmp;
  }
}

void find() {
  for ( int i = 0; i < n; ++ i )
    P[i] = i + 1;
  printf("@f: (%2d,%2d):", n, 1);
  print_p();
  for ( int i = 2; i <= n; ++ i )
    f(i);
  printf("@f: (%2d,%2d):", n, 1);
  print_p();
  cout << endl;
}

int main() {
  for ( n = 1; n < 20; ++ n ) {
    find();
  }
  return 0;
}

