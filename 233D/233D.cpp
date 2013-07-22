
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

// @snippet<sh19910711/contest:math/comb/comb.cpp>
namespace math {
  namespace comb {
    const long long MOD = 1000000007LL;
    const int SIZE = 1001;
    long long C[SIZE][SIZE];
    void init() {
      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j <= i; ++ j ) {
          if ( j == 0 || j == i )
            C[i][j] = 1;
          else
            C[i][j] = ( C[i-1][j-1] + C[i-1][j] ) % MOD;
        }
      }
    }
    long long calc( int n, int r ) {
      return C[n][r];
    }
  }
}

// @snippet<sh19910711/contest:math/mod_pow.cpp>
namespace math {
  template<class T> T mod_pow( T x, T n, T mod ) {
    if ( n == 0 ) return 1;
    T res = mod_pow( x * x % mod, n / 2, mod );
    if ( n & 1 ) res = res * x % mod;
    return res;
  }
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const LL MOD = 1000000007LL;
  const int SIZE = 100 + 11;
  
  // storages
  int n;
  LL m;
  int k;
  
  LL result;
  LL dp[SIZE][SIZE * SIZE];
  LL cnt[SIZE];
  LL comb_pow[SIZE][SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = calc_ways();
    }

    LL calc_ways() {
      for ( int i = 0; i < n; ++ i ) {
        cnt[i] = m / n + ( i < m % n ? 1 : 0 );
      }

      for ( int i = 0; i <= n; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          comb_pow[i][j] = math::mod_pow(math::comb::calc(n, i), cnt[j], MOD);
        }
      }

      dp[0][0] = 1;
      for ( int i = 0; i < n; ++ i ) {
        for ( int j = 0; j <= k; ++ j ) {
          LL& current_state = dp[i][j];
          for ( int p = 0; p <= n; ++ p ) {
            LL& next_state = dp[i + 1][j + p];
            next_state = ( next_state + ( current_state * comb_pow[p][i] ) % MOD ) % MOD;
          }
        }
      }

      return dp[n][k];
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
      math::comb::init();
      
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE * SIZE; ++ j )
          dp[i][j] = 0;
    }
    
    bool input() {
      return cin >> n >> m >> k;
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



