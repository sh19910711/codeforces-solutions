
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
  typedef std::set<int> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 2 * 100000 + 11;
  const LL NONE = std::numeric_limits<LL>::min() / 10LL;
  const LL MEMO_NONE = std::numeric_limits<LL>::min() / 5LL;
  // storages
  int n;
  int A[SIZE];

  bool visited[SIZE][3];
  LL memo[SIZE][3];

  LL results[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( int i = 1; i <= n - 1; i ++ ) {
        A[1] = i;
        visited[1][1+1] = false;
        memo[1][1+1] = MEMO_NONE;
        results[i - 1] = run(1, 1);
      }
    }

    LL run( int x, int k ) {
      if ( x <= 0 || x > n )
        return 0;
      LL& res = memo[x][k+1];
      if ( res != MEMO_NONE )
        return res;
      if ( visited[x][k+1] )
        return res = NONE;
      visited[x][k+1] = true;
      LL ret = run(x + k * A[x], -k);
      if ( ret == NONE )
        return NONE;
      return res = ret + A[x];
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
      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j < 3; ++ j ) {
          memo[i][j] = MEMO_NONE;
          visited[i][j] = false;
        }
      }
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
        if ( results[i] == NONE ) {
          cout << -1 << endl;
        } else {
          cout << results[i] << endl;
        }
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

