
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
  const int SIZE = 100;
  const LL INF = 1000000000000000000LL + 11LL;

  // storages
  LL n;

  int AC;
  LL A[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      AC = 0;

      LL ret1 = search_even();
      if ( ret1 != INF )
        A[AC ++] = ret1;

      LL ret2 = search_odd();
      if ( ret2 != INF )
        A[AC ++] = ret2;

      sort(A, A + AC);
    }

    LL f( int x ) {
      if ( x < 1 )
        return 1;
      if ( x == 1 )
        return 1;
      LL p = 1;
      for ( int i = 0; i < x; ++ i ) {
        if ( p * 2 >= INF )
          return INF;
        p *= 2;
      }
      LL res = ( p - 1 ) / ( x - 1 );
      if ( res >= INF )
        return INF;
      return res;
    }

    LL get_sum_even( LL s ) {
      LL m = s;
      LL x = 0;
      while ( m % 2 == 0 ) {
        m /= 2;
        x ++;
      }
      if ( f(x) > INF / m )
        return INF;
      if ( m > INF )
        return INF;
      if ( m - 1 > 2 * INF / m )
        return INF;
      return m * f(x) + m * ( m - 1 ) / 2;
    }

    bool equal_even( LL s ) {
      return get_sum_even(s) == n;
    }

    bool less_even( LL s ) {
      return get_sum_even(s) < n;
    }

    LL search_even() {
      LL lb = 0;
      LL ub = INF;
      while ( ub - lb > 1 ) {
        LL mid = ( lb + ub ) / 2;
        for ( int i = 0; i < 50; ++ i ) {
          if ( equal_even(2 * mid + i * 2) )
            return 2 * mid + i * 2;
        }
        if ( less_even(2 * mid) ) {
          lb = mid;
        } else {
          ub = mid;
        }
      }
      return INF;
    }

    LL get_sum_odd( LL s ) {
      if ( s <= 1 )
        return 0;
      if ( s > 2 * INF / ( s - 1 ) )
        return INF;
      return s * ( s - 1 ) / 2;
    }

    bool equal_odd( LL s ) {
      return get_sum_odd(s) == n;
    }

    bool less_odd( LL s ) {
      return get_sum_odd(s) < n;
    }

    LL search_odd() {
      LL lb = 0;
      LL ub = INF;
      while ( ub - lb > 1 ) {
        LL mid = ( lb + ub ) / 2;
        if ( equal_odd(2 * mid + 1) ) {
          return 2 * mid + 1;
        } else if ( less_odd(2 * mid + 1) ) {
          lb = mid;
        } else {
          ub = mid;
        }
      }
      return INF;
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
      if ( ! ( cin >> n ) )
        return false;
      return true;
    }

    void output() {
      if ( AC == 0 ) {
        cout << -1 << endl;
      } else {
        for ( int i = 0; i < AC; ++ i )
          cout << A[i] << endl;
        cout << endl;
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

