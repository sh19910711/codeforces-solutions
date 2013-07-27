
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
  typedef std::stack <int> Stack;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 700 + 11;
  const LL MOD = 1000000007LL;
  const int BLACK = 0;
  const int COLORS = 3;
  const LL MEMO_NONE = std::numeric_limits<LL>::min();

  // storages
  string s;

  int n;
  int cor[SIZE];
  LL memo[SIZE][SIZE][COLORS][COLORS];

  LL result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      n = s.size();
      find_corresponds();
      result = calc_numbers();
    }

    LL calc_numbers() {
      return rec(0, n - 1, BLACK, BLACK);
    }

    LL rec( int l, int r, int cl, int cr ) {
      LL& res = memo[l][r][cl][cr];
      if ( res != MEMO_NONE ) {
        return res;
      }

      if ( l > r ) {
        return res = 1 % MOD;
      }

      int correspond = cor[l];
      res = 0;

      if ( correspond == r ) {
        for ( int new_color = 1; new_color < COLORS; ++ new_color ) {
          if ( new_color != cl ) {
            res = ( res + rec(l + 1, r - 1, new_color, BLACK) ) % MOD;
          }
          if ( new_color != cr ) {
            res = ( res + rec(l + 1, r - 1, BLACK, new_color) ) % MOD;
          }
        }
      } else {
        for ( int new_color = 1; new_color < COLORS; ++ new_color ) {
          if ( new_color != cl ) {
            LL ret = rec(l + 1, correspond - 1, new_color, BLACK) * rec(correspond + 1, r, BLACK, cr);
            ret %= MOD;
            res = ( res + ret ) % MOD;
          }
          LL ret = rec(l + 1, correspond - 1, BLACK, new_color) * rec(correspond + 1, r, new_color, cr);
          ret %= MOD;
          res = ( res + ret ) % MOD;
        }
      }

      return res %= MOD;
    }

    void find_corresponds() {
      Stack st;
      for ( int i = 0; i < n; ++ i ) {
        if ( s[i] == '(' ) {
          st.push(i);
        } else if ( s[i] == ')' ) {
          int l = st.top();
          st.pop();
          cor[l] = i;
          cor[i] = l;
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
      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j < SIZE; ++ j ) {
          for ( int k = 0; k < COLORS; ++ k ) {
            for ( int l = 0; l < COLORS; ++ l ) {
              memo[i][j][k][l] = MEMO_NONE;
            }
          }
        }
      }
    }

    bool input() {
      return cin >> s;
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

