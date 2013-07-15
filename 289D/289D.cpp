
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
  const int MOD = 1000000007;
  const int SIZE = 1000 + 11;
  // storages
  int n, k;
  int result;

  int P[SIZE];
  bool used[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = 0;

      rec(0);
    }

    void rec( int x ) {
      if ( x >= n ) {
        if ( check_valid() )
          print_p();
        return;
      }

      for ( int i = 0; i < n; ++ i ) {
        P[x] = i;
        rec(x + 1);
      }
    }

    bool check_valid() {
      for ( int i = 0; i < n; ++ i ) {
        fill(used, used + n, false);
        if ( i < k ) {
          if ( ! can_reach_0(P[i]) ) {
            return false;
          }
        } else {
          if ( can_reach_0(P[i]) ) {
            return false;
          }
        }
      }
      return true;
    }

    bool can_reach_0( int x ) {
      if ( x == 0 )
        return true;
      if ( used[x] )
        return false;
      used[x] = true;
      return can_reach_0(P[x]);
    }

    void print_p() {
      for ( int i = 0; i < n; ++ i )
        cout << P[i] << ", ";
      cout << endl;
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
      return cin >> n >> k;
    }

    void output() {
      cout << result << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

