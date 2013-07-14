
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
  typedef set<II> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 1000000 + 11;
  const LL MOD = 1000000007LL;

  // storages
  int n, m, k;
  int from[SIZE];
  int to[SIZE];
  int F[SIZE];
  int FC;
  Set E;

  LL P[SIZE];

  LL result;

}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      for ( int i = 0; i < m; ++ i )
        E.insert(II(from[i], to[i]));
      result = calc_ways();
    }

    void normalize() {
      for ( int i = 0; i < m; ++ i ) {
        from[i] --;
        to[i] --;
      }
    }

    bool has_skipped( int x ) {
      return E.count(II(x, x + k + 1));
    }

    LL calc_ways() {
      if ( is_invalid_case() )
        return 0;

      LL total = get_total();
      return total;
    }

    LL get_total() {

      FC = 0;
      for ( int i = 0; i < m; ++ i ) {
        if ( to[i] - from[i] == k + 1 ) {
          F[FC ++] = from[i];
        }
      }
      sort(F, F + FC);

      LL res = 0;
      for ( int i = 0; i + k + 1 < n; ++ i ) {
        if ( has_skipped(i) || has_skipped(i + k + 1) )
          continue;
        int left = i;
        int right = min(n - k - 1 - 1, i + k);
        int len = max(0, right - left);
        int lb = std::lower_bound(F, F + FC, left + 1) - F;
        int ub = std::upper_bound(F, F + FC, right) - F;
        len -= ub - lb;
        if ( len < 0 )
          continue;
        if ( len == 0 && has_skipped(i) )
          continue;
        res = ( res + P[len] ) % MOD;
      }

      bool ok = true;
      LL con = 0;
      for ( int i = 0; i + 1 < n; ++ i ) {
        if ( ! E.count(II(i, i + 1)) ) {
          ok = false;
          con = 1;
        }
      }
      if ( ok )
        con ++;

      return ( res + con ) % MOD;
    }

    bool is_invalid_case() {

      for ( int i = 0; i < m; ++ i ) {
        int dist = to[i] - from[i];
        if ( dist != 1 && dist != k + 1 )
          return true;
      }

      for ( int i = 0; i < m; ++ i ) {
        if ( has_skipped(i) && has_skipped(i + k + 1) )
          return true;
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

    void pre_calc() {
      P[0] = 1;
      for ( int i = 1; i < SIZE; ++ i )
        P[i] = ( P[i - 1] * 2LL ) % MOD;
    }

    void init() {
      E.clear();
    }

    bool input() {
      if ( ! ( cin >> n >> m >> k ) )
        return false;
      for ( int i = 0; i < m; ++ i )
        cin >> from[i] >> to[i];
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
int main() {
  return solution::Solution().run();
}

