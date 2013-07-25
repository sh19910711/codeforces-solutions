
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
  typedef std::set<II> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 30;
  const LL NONE = std::numeric_limits<LL>::min();
  // storages
  int n, u, r;
  LL A[SIZE];
  int B[SIZE];
  int K[SIZE];
  int P[SIZE];
  
  LL result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      result = NONE;
      rec(0, true, A);
    }
    
    void normalize() {
      for ( int i = 0; i < n; ++ i ) {
        P[i] --;
      }
    }

    void update_max_score( LL* cur ) {
      LL score = 0;
      for ( int i = 0; i < n; ++ i ) {
        score += cur[i] * K[i];
      }
      result = std::max(result, score);
    }
    
    void rec( int x, bool prev, LL* cur ) {
      if ( ! ( ( u - x ) & 1 ) ) {
        update_max_score(cur);
      }

      if ( x == u ) {
        return;
      }

      LL next[SIZE];
      if ( prev ) {
        for ( int i = 0; i < n; ++ i ) {
          next[i] = cur[i] ^ B[i];
        }
        rec(x + 1, false, next);
      }

      for ( int i = 0; i < n; ++ i ) {
        next[i] = cur[P[i]] + r;
      }
      rec(x + 1, true, next);
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
    
    bool input() {
      if ( ! ( cin >> n >> u >> r ) )
        return false;
      for ( int i = 0; i < n; ++ i ) {
        cin >> A[i];
      }
      for ( int i = 0; i < n; ++ i ) {
        cin >> B[i];
      }
      for ( int i = 0; i < n; ++ i ) {
        cin >> K[i];
      }
      for ( int i = 0; i < n; ++ i ) {
        cin >> P[i];
      }
      return true;
    }
    
    void output() {
      cout << result << endl;
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


