
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
  const LL INF = 100000;
  // storages
  LL n, x, y, c;

  LL result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_minimum_steps();
    }

    LL get_minimum_steps() {
      LL lb = 0;
      LL ub = INF;

      while ( ub - lb > 1 ) {
        LL mid = ( lb + ub ) / 2LL;
        if ( check(mid) ) {
          ub = mid;
        } else {
          lb = mid;
        }
      }

      return ub - 1;
    }

    bool check( LL steps ) {
      printf("@check: steps = %lld, total = %lld\n", steps, f_total(steps));
      return f_total(steps) >= c;
    }

    LL f_total( LL steps ) {
      if ( steps <= 0 )
        return 0;
      if ( steps == 1 )
        return 1;

      LL f1_value = f1(steps);
      LL f3_t = f3_top(steps);
      LL f3_r = f3_right(steps);
      LL f3_b = f3_bottom(steps);
      LL f3_l = f3_left(steps);
      LL f2_x = f2(max(0LL, steps - max(x, n - x + 1)));
      LL f2_y = f2(max(0LL, steps - max(y, n - y + 1)));

      printf("@f_total\n");
      printf("@f_total: steps = %lld\n", steps);
      printf("@f_total: f1: %lld\n", f1_value);
      printf("@f_total: f2: %lld, %lld\n", f2_x, f2_y);
      printf("@f_total: f3: %lld, %lld, %lld, %lld\n", f3_t, f3_r, f3_b, f3_l);
      printf("\n");

      LL res = f1(steps)
        - f3_t - f3_l - f3_r - f3_b
        + f2(max(0LL, steps - x)) + f2(max(0LL, steps - ( n - x + 1 )))
        + f2(max(0LL, steps - y)) + f2(max(0LL, steps - ( n - y + 1 ))) ;
      return res;
    }

    LL sum_g( LL steps ) {
      LL res = ( steps - 1 ) * ( 4 + 4 * ( steps - 1 ) ) / 2;
      return res;
    }

    LL f1( LL steps ) {
      if ( steps <= 0 )
        return 0;
      LL res = 1 + sum_g(steps);
      return res;
    }

    LL h( LL steps ) {
      if ( steps <= 0 )
        return 0;
      LL res = 3 + 2 * ( steps - 1 );
      return res;
    }

    LL sum_h( LL steps ) {
      if ( steps <= 1LL )
        return 0;
      LL res = ( steps - 1 ) * ( h( steps - 1 ) + 3 ) / 2;
      return res;
    }

    LL f3_top( LL steps ) {
      LL real_steps = max(0LL, steps - x);
      if ( real_steps <= 1 )
        return 0;
      LL left = max(0LL, real_steps - y);
      LL right = max(0LL, real_steps - ( n - y + 1 ));
      LL res = 1 + sum_h(real_steps) - f2(left) - f2(right);
      return res;
    }

    LL f3_bottom( LL steps ) {
      LL real_steps = max(0LL, steps - ( n - x + 1 ));
      if ( real_steps <= 1 )
        return 0;
      LL left = max(0LL, real_steps - y);
      LL right = max(0LL, real_steps - ( n - y + 1 ));
      LL res = 1 + sum_h(real_steps) - f2(left) - f2(right);
      return res;
    }

    LL f3_left( LL steps ) {
      LL real_steps = max(0LL, steps - y);
      if ( real_steps <= 1 )
        return 0;
      LL top = max(0LL, real_steps - x);
      LL bottom = max(0LL, real_steps - ( n - x + 1 ));
      LL res = 1 + sum_h(real_steps) - f2(top) - f2(bottom);
      return res;
    }

    LL f3_right( LL steps ) {
      LL real_steps = max(0LL, steps - ( n - y + 1 ));
      if ( real_steps <= 1 )
        return 0;
      LL top = max(0LL, real_steps - x);
      LL bottom = max(0LL, real_steps - ( n - x + 1 ));
      LL res = 1 + sum_h(real_steps) - f2(top) - f2(bottom);
      return res;
    }

    LL f2( LL x ) {
      LL res = x * ( x + 1 ) / 2;
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

    bool input() {
      return cin >> n >> x >> y >> c;
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

