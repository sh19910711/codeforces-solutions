
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual int run() = 0;
    
  protected:
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      pre_calc();
      while ( action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef std::vector<std::string> VS;
  typedef long long LL;
  typedef int INT;
  typedef std::vector<INT> VI;
  typedef std::vector<VI> VVI;
  typedef std::pair<INT,INT> II;
  typedef std::vector<II> VII;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE       = 50000 + 11;
  const int CNT_SIZE   = 5000;
  const int CNT_OFFSET = CNT_SIZE / 2;

  const int dx[4] = {1, -1, 0, 0};
  const int dy[4] = {0, 0, 1, -1};

  // storages
  int n, m;
  int X[SIZE], Y[SIZE];

  int cnt[CNT_SIZE][CNT_SIZE];

  int query_result[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( ; n > 4; n -= 4 ) {
        cnt[0 + CNT_OFFSET][0 + CNT_OFFSET] += 4;
        rec(0, 0);
      }
      for ( ; n > 0; -- n ) {
        cnt[0 + CNT_OFFSET][0 + CNT_OFFSET] += 1;
        rec(0, 0);
      }
      for ( int i = 0; i < m; ++ i ) {
        query_result[i] = query(X[i], Y[i]);
      }
    }

    int query( int x, int y ) {
      if ( abs(x) >= CNT_OFFSET || abs(y) >= CNT_OFFSET )
        return 0;
      return mapping(x, y);
    }

    int& mapping( int x, int y ) {
      return cnt[x + CNT_OFFSET][y + CNT_OFFSET];
    }

    void rec( int x, int y ) {
      if ( cnt[x + CNT_OFFSET][y + CNT_OFFSET] >= 4 ) {
        cnt[x + CNT_OFFSET][y + CNT_OFFSET] -= 4;
        for ( int k = 0; k < 4; ++ k ) {
          int nx = x + dx[k];
          int ny = y + dy[k];
          cnt[nx + CNT_OFFSET][ny + CNT_OFFSET] ++;
        }
        for ( int k = 0; k < 4; ++ k ) {
          int nx = x + dx[k];
          int ny = y + dy[k];
          if ( cnt[nx + CNT_OFFSET][ny + CNT_OFFSET] >= 4 )
            rec(nx, ny);
        }
      }
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }

    void init() {
      for ( int i = 0; i < CNT_SIZE; ++ i )
        for ( int j = 0; j < CNT_SIZE; ++ j )
          cnt[i][j] = 0;
    }

    bool input() {
      if ( ! ( cin >> n >> m ) )
        return false;
      for ( int i = 0; i < m; ++ i ) {
        cin >> X[i] >> Y[i];
      }
      return true;
    }

    void output() {
      for ( int i = 0; i < m; ++ i ) {
        cout << query_result[i] << endl;
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

