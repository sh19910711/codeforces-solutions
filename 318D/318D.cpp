
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
  class ISolution {
  public:
    virtual int run() = 0;
    
  protected:
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public ISolution {
  public:
    virtual int run() {
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
  typedef map <II, int> Map;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 50000 + 11;
  const int dx[4] = {1, -1, 0 ,0};
  const int dy[4] = {0, 0, 1, -1};
  const int GRID_SIZE = 400;
  const int GRID_OFFSET = GRID_SIZE / 2;

  // storages
  int n, t;
  int X[SIZE];
  int Y[SIZE];
  int CNT[GRID_SIZE * GRID_SIZE];

  int results;
  int A[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( int i = 0; i < n; ++ i )
        rec(0, 0);

      results = 0;
      for ( int i = 0; i < t; ++ i ) {
        A[results ++] = query(X[i], Y[i]);
      }
    }

    int& mapping( int x, int y ) {
      x += GRID_OFFSET;
      y += GRID_OFFSET;
      return CNT[y * GRID_OFFSET + x];
    }

    void rec( int x, int y ) {
      int& cnt = mapping(x, y);
      cnt ++;
      if ( cnt >= 4 ) {
        cnt -= 4;
        for ( int k = 0; k < 4; ++ k ) {
          int nx = x + dx[k];
          int ny = y + dy[k];
          rec(nx, ny);
        }
      }
    }

    int query( int x, int y ) {
      if ( abs(x) >= GRID_OFFSET || abs(y) >= GRID_OFFSET )
        return 0;
      return mapping(x, y);
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
      fill(CNT, CNT + GRID_SIZE * GRID_SIZE, 0);
    }

    bool input() {
      if ( ! ( cin >> n >> t ) )
        return false;
      for ( int i = 0; i < t; ++ i )
        cin >> X[i] >> Y[i];
      return true;
    }

    void output() {
      for ( int i = 0; i < results; ++ i )
        cout << A[i] << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

