#include <iostream>
#include <cmath>
#include <set>
using namespace std;

int main() {
  const int SIZE = 10;
  for ( int N = 1; N < SIZE; ++ N ) {
    set<pair<int, int>> s;
    double n = N;
    cout << "n = " << n << endl;
    for ( int i = 0; i < 360; ++ i ) {
      for ( int j = 0; j <= 1000; ++ j ) {
        double k = i;
        k += 1.0 / (double)j;
        double ang = k * M_PI / 180.0;
        double x = n * sin(ang);
        double y = n * cos(ang);
        // cout << i << ": " << x << ", " << y << endl;
        s.insert(make_pair(x + 1000.0, y + 1000.0));
      }
    }
    cout << "size = " << s.size() << endl;
  }
  return 0;
}
