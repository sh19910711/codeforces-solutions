
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
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int HOLES = 300 + 11;
  const int SIZE = 100000 + 11;
  const LL NONE = std::numeric_limits<LL>::max() / 2;
  // storages
  int n, m, k;
  int L[SIZE];
  int R[SIZE];
  LL C[SIZE];
  LL result;
  LL table[HOLES][HOLES];
  LL min_cost[HOLES][HOLES * 2];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_min_cost();
    }

    LL get_min_cost() {
      for ( int i = 0; i < m; ++ i ) {
        int l = L[i] - 1;
        int r = R[i] - 1;
        int len = r - l + 1;
        for ( int j = 0; j < len; ++ j )
          table[l][l + j + 1] = min(table[l][l + j + 1], C[i]);
        for ( int j = 0; j < len; ++ j )
          table[r - j][r + 1] = min(table[r - j][r + 1], C[i]);
      }

      for ( int i = 0; i < n; ++ i )
        min_cost[i][0] = 0;

      // [from, to)
      for ( int from = 0; from < n; ++ from ) {
        for ( int to = from + 1; to <= n; ++ to ) {
          if ( table[from][to] == NONE )
            continue;
          for ( int num = 0; num <= n; ++ num ) {
            LL cur = min_cost[from][num];
            if ( cur == NONE )
              continue;
            int len = to - from;
            int next_num = num + len;
            min_cost[to][next_num] = min(min_cost[to][next_num], cur + table[from][to]); 
          }
        }
        for ( int num = 0; num <= n; ++ num )
          min_cost[from + 1][num] = min(min_cost[from + 1][num], min_cost[from][num]);
      }

      LL res = NONE;
      for ( int i = 0; i <= n; ++ i ) {
        for ( int x = k; x <= 2 * n; ++ x ) {
          res = min(res, min_cost[i][x]);
        }
      }
      return res;
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
      result = NONE;
      for ( int i = 0; i < HOLES; ++ i )
        for ( int j = 0; j < HOLES; ++ j )
          table[i][j] = NONE;
      for ( int i = 0; i < HOLES; ++ i )
        for ( int j = 0; j < 2 * HOLES; ++ j )
          min_cost[i][j] = NONE;
    }

    bool input() {
      if ( ! ( cin >> n >> m >> k ) )
        return false;
      for ( int i = 0; i < m; ++ i )
        cin >> L[i] >> R[i] >> C[i];
      return true;
    }

    void output() {
      if ( result == NONE ) {
        cout << -1 << endl;
      } else {
        cout << result << endl;
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

