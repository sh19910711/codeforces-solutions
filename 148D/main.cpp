
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
  typedef double Double;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 1000 + 11;
  // storages
  int W, B;
  Double memo[2][SIZE][SIZE];

  Double result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_winning_prob();
    }

    Double get_winning_prob() {
      return rec(0, W, B);
    }

    Double rec( int steps, int whites, int blacks ) {
      Double& res = memo[steps % 2][whites][blacks];
      if ( res >= 0.0 ) {
        return res;
      }

      if ( whites == 0 && blacks <= 1 ) {
        return res = ( steps % 2 == 0 ? 0.0 : 1.0 );
      }

      res = 0.0;
      if ( steps % 2 == 0 ) {
        if ( whites > 0 ) {
          res += (Double)( whites ) / ( whites + blacks );
        }
        if ( blacks > 0 ) {
          res += (Double)( blacks ) / ( whites + blacks ) * ( 1.0 - rec(steps + 1, whites, blacks - 1) );
        }
      } else {
        if ( whites > 0 ) {
          res += (Double)( whites ) / ( whites + blacks );
        }
        if ( blacks > 0 ) {
          if ( whites > 0 ) {
            res += (Double)( blacks ) / ( whites + blacks ) * (Double)( whites ) / ( whites + blacks - 1 ) * ( 1.0 - rec(steps + 1, whites - 1, blacks - 1) );
          }
          if ( blacks - 1 > 0 ) {
            res += (Double)( blacks ) / ( whites + blacks ) * (Double)( blacks - 1 ) / ( whites + blacks - 1 ) * ( 1.0 - rec(steps + 1, whites, blacks - 2) );
          }
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
      for ( int i = 0; i < 2; ++ i ) {
        for ( int j = 0; j < SIZE; ++ j ) {
          for ( int k = 0; k < SIZE; ++ k ) {
            memo[i][j][k] = -1.0;
          }
        }
      }
    }

    bool input() {
      return cin >> W >> B;
    }

    void output() {
      printf("%.12f\n", result);
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

