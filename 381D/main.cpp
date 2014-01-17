#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
using namespace std;

int main() {
  const int NONE = -1;
  const int SIZE = 100 * 7000 + 111;
  int pl[SIZE];
  int pr[SIZE];
  int cnt = 1;
  for ( int i = 1; i < SIZE; ++ i ) {
    if ( ( i & ( i - 1 ) ) == 0 ) {
      pl[i] = cnt ++;
      pr[i] = cnt ++;
    } else {
      pl[i] = NONE;
      pr[i] = cnt ++;
    }
  }
  typedef std::pair <int, int> II;
  typedef std::pair <II, int> III; // l, r, x
  typedef std::vector<III> VIII;
  VIII xs[SIZE];
  int n, m;
  std::cin >> n >> m;
  for ( int i = 0; i < m; ++ i ) {
    int t;
    std::cin >> t;
    if ( t == 1 ) {
      int t, l, r, x;
      std::cin >> t >> l >> r >> x;
      xs[t].push_back(III(II(l, r), x));
    } else {
      int t, v;
      std::cin >> t >> v;
      std::set <int> vt;
      int lm[SIZE];
      int rm[SIZE];
      lm[t] = v;
      rm[t] = v;
      for ( int i = t + 1; i <= n; ++ i ) {
        lm[i] = pl[lm[i - 1]] == NONE ? pr[lm[i - 1]] : pl[lm[i - 1]];
        rm[i] = pr[rm[i - 1]];

      }
      for ( int i = t; i <= n; ++ i ) {
        int len = xs[i].size();
        for ( int j = 0; j < len; ++ j ) {
          const III& e = xs[i][j];
          int ll = e.first.first;
          int rr = e.first.second;
          int xx = e.second;
          if ( lm[i] <= rr && ll <= rm[i] ) {
            vt.insert(xx);
          }
        }
      }
      std::cout << vt.size() << std::endl;
    }
  }
  return 0;
}
