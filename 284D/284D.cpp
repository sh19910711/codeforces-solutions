
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
  const int SIZE = 2 * 100000 + 11;
  const int NONE = -1;
  const LL MEMO_NONE = std::numeric_limits<LL>::min();
  // storages
  int n;
  int A[SIZE];
  
  LL B[SIZE];
  bool visited[SIZE][2];
  LL memo[SIZE][2];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( int i = 1; i <= n - 1; ++ i ) {
        memo[1][0] = MEMO_NONE;
        visited[1][0] = false;
        A[1] = i;
        LL ret = rec(1, 0);
        if ( ret == NONE ) {
          B[i - 1] = NONE;
        } else {
          B[i - 1] = ret;
        }
      }
    }

    LL rec( int x, int first ) {
      if ( x <= 0 || x > n )
        return 0;

      if ( memo[x][first] != MEMO_NONE )
        return memo[x][first];

      if ( visited[x][first] )
        return memo[x][first] = NONE;
      visited[x][first] = true;

      if ( first ) {
        LL ret = rec(x - A[x], 0);
        return memo[x][first] = ( ret == NONE ? NONE : ret + A[x] );
      } else {
        LL ret = rec(x + A[x], 1);
        return memo[x][first] = ( ret == NONE ? NONE : ret + A[x] );
      }

      return NONE;
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
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < 2; ++ j )
          visited[i][j] = false;
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < 2; ++ j )
          memo[i][j] = MEMO_NONE;
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 2; i <= n; ++ i )
        cin >> A[i];
      return true;
    }

    void output() {
      for ( int i = 0; i < n - 1; ++ i ) {
        if ( B[i] == NONE ) {
          cout << -1 << endl;
        } else {
          cout << B[i] << endl;
        }
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

