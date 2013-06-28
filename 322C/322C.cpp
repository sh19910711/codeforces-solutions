
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
  const string YES = "Yes";
  const string NO = "No";
  const LL INF = 1000000000LL + 11LL;
  const LL LIMIT = 5000;

  // storages
  LL tx, ty;
  string s;
  bool result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = check();
    }

    bool check() {
      int n = s.size();
      LL dx = 0;
      LL dy = 0;
      for ( int j = 0; j < LIMIT; ++ j ) {
        for ( int i = 0; i < n; ++ i ) {
          if ( dx == tx && dy == ty )
            return true;
          if ( s[i] == 'L' ) {
            dx --;
          } else if ( s[i] == 'R' ) {
            dx ++;
          } else if ( s[i] == 'U' ) {
            dy ++;
          } else if ( s[i] == 'D' ) {
            dy --;
          }
        }
      }

      LL lb = 1, ub = INF;
      while ( ub - lb > 1 ) {
        LL mid = ( lb + ub ) / 2;
        LL nx = dx * mid;
        LL ny = dy * mid;
        LL atx = abs(tx);
        LL aty = abs(ty);
        LL anx = abs(nx);
        LL any = abs(ny);
        if ( anx <= atx && any <= aty ) {
          lb = mid;
        } else {
          ub = mid;
        }
      }

      LL x = dx * lb;
      LL y = dy * lb;

      for ( int j = 0; j < LIMIT; ++ j ) {
        for ( int i = 0; i < n; ++ i ) {
          if ( x == tx && y == ty )
            return true;
          if ( s[i] == 'L' ) {
            x --;
          } else if ( s[i] == 'R' ) {
            x ++;
          } else if ( s[i] == 'U' ) {
            y ++;
          } else if ( s[i] == 'D' ) {
            y --;
          }
          if ( x == tx && y == ty )
            return true;
        }
      }

      return false;
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
      return cin >> tx >> ty >> s;
    }

    void output() {
      cout << ( result ? YES : NO ) << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

