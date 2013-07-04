
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
  const LL MOD = 1000000000 + 7;
  const int SIZE = 100000 + 11;
  
  // storages
  string s;
  LL k;
  LL result;
  LL TP[SIZE];
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

// @snippet<sh19910711/contest:math/extgcd.cpp>
namespace math {
  template <class T> T extgcd( T a, T b, T& x, T& y ) {
    for ( T u = y = 1, v = x = 0; a; ) {
      T q = b / a;
      std::swap( x -= q * u, u );
      std::swap( y -= q * v, v );
      std::swap( b -= q * a, a );
    }
    return b;
  }
}

// @snippet<sh19910711/contest:math/mod_inverse.cpp>
namespace math {
  // @desc mod mでaの逆元を求める
  template <class T> T mod_inverse( T a, T m ) {
    T x, y;
    extgcd( a, m, x, y );
    x %= m;
    while ( x < 0 )
      x += m;
    return x;
  }
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = calc();
    }
    
    bool check_good( char c ) {
      return c == '0' || c == '5';
    }
    
    LL calc() {
      int n = s.size();
      LL possum = 0;
      for ( int i = 0; i < n; ++ i )
        if ( check_good(s[i]) )
          possum = ( possum + TP[i] ) % MOD;
      
      LL offset = TP[n];
      LL p = math::mod_pow(offset, k, MOD);
      LL offset_sum = ( ( p - 1 ) * math::mod_inverse( offset - 1, MOD ) ) % MOD;
      
      return ( possum * offset_sum ) % MOD;
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {
      TP[0] = 1;
      for ( int i = 1; i < SIZE; ++ i )
        TP[i] = ( TP[i - 1] * 2 ) % MOD;
    }
    
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
      return cin >> s >> k;
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



