
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

// @snippet<sh19910711/contest:math/comb/comb.cpp>
namespace math {
  namespace comb {
    const int MOD = 1000000000 + 7;
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
  const int DIGIT_NUM = 10;
  const int SIZE = 100 + 11;
  const LL MOD = 1000000007LL;
  const LL MEMO_NONE = -100;
  // storages
  int n;
  int A[DIGIT_NUM];
  
  LL memo[SIZE][SIZE];
  
  LL result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = calc_numbers();
    }
    
    LL calc_numbers() {
      LL res = 0;
      for ( int i = 1; i <= n; ++ i ) {
        res = ( res + f(i, 0) ) % MOD;
      }
      return res;
    }
    
    LL f( int len, int x ) {
      LL& res = memo[len][x];
      if ( res != MEMO_NONE ) {
        return res;
      }

      
      if ( x == 9 ) {
        res = len >= A[9] ? 1 : 0;
      } else if ( x == 0 ) {
        LL sum = 0;
        for ( int i = A[0]; i <= len; ++ i ) {
          sum += ( f(len - i, 1) * math::comb::calc(len - 1, i) ) % MOD;
        }
        res = sum % MOD;
      } else {
        LL sum = 0;
        for ( int i = A[x]; i <= len; ++ i ) {
          sum += ( f(len - i, x + 1) * math::comb::calc(len, i) ) % MOD;
        }
        res = sum % MOD;
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

    void pre_calc() {
      math::comb::init();
    }
    
    void init() {
      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j < SIZE; ++ j ) {
          memo[i][j] = MEMO_NONE;
        }
      }
    }
    
    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < DIGIT_NUM; ++ i ) {
        cin >> A[i];
      }
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
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif


