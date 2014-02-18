#include <iostream>
#include <cmath>
using namespace std;

double sq( double x ) {
  return x * x;
}

double get_dist( double x1, double y1, double x2, double y2 ) {
  double x = x2 - x1;
  double y = y2 - y1;
  return sqrt(sq(x) + sq(y));
}

// x <= y
bool check( double x, double y ) {
  if ( abs( x - y ) < 1e-9 )
    return true;
  return x < y;
}

int main() {
  const int size = 100;
  for ( int N = 0; N <= size / 2; ++ N ) {
    double n = N;
    bool T[size][size];
    int sx = size / 2;
    int sy = size / 2;
    for ( int i = 0; i < size; ++ i ) {
      for ( int j = 0; j < size; ++ j ) {
        if ( check(get_dist(sx, sy, j, i), n) ) {
          T[i][j] = true;
        } else {
          T[i][j] = false;
        }
      }
    }
    cout << "N = " << N << endl;
    for ( int i = 0; i < size; ++ i ) {
      for ( int j = 0; j < size; ++ j ) {
        cout << T[i][j];
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
