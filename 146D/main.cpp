
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
  
  // storages
  int a, b, c, d;

  string result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_lucky_number();
    }

    string get_lucky_number() {
      if ( a == 1 && b == 1 && c == 1 && d == 0 ) {
        return "47";
      }

      if ( a == 1 && b == 1 && c == 0 && d == 1 ) {
        return "74";
      }

      if ( c > 0 && c == d ) {
        if ( a >= c + 1 && b >= c ) {
          // 4...4
          string res = string(a - c, '4');
          for ( int i = 0; i < c - 1; ++ i ) {
            res += "74";
          }
          res += string(max(0, b - c + 1), '7');
          res += "4";
          return res;
        } else if ( a >= c && b >= c + 1 ) {
          string res = "7";
          res += string(max(0, a - c + 1), '4');
          for ( int i = 0; i < c - 1; ++ i ) {
            res += "74";
          }
          res += string(max(0, b - c), '7');
          return res;
        }
      }

      if ( abs( c - d ) == 1 ) {
        if ( a >= c && b >= c && c > d ) {
          string res = "";
          // 4...4
          res += string(max(0, a - c), '4');
          // 4...4...47
          for ( int i = 0; i < c; ++ i ) {
            res += "47";
          }
          // 4...4...47...7
          res += string(max(0, b - c), '7');
          return res;
        } else if ( a >= d && b >= d && d > c ) {
          d --;
          string res = "74";
          res += string(max(0, a - d - 1), '4');
          for ( int i = 0; i < d - 1; ++ i ) {
            res += "74";
          }
          res += string(max(0, b - d - 1), '7');
          res += "74";
          return res;
        }
      }

      return "-1";
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
      return cin >> a >> b >> c >> d;
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

