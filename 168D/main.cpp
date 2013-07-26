
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

  typedef std::pair <int, int> PII;
  typedef std::pair <int, PII> MapKey;
  typedef std::map <MapKey, Double> Map;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 200 + 11;
  const int A_NONE = -1;
  const int VOLUME_LIMIT = SIZE;

  // storages
  int n, l, k;
  Double prob[SIZE];
  int A[SIZE];

  Double dp[SIZE][SIZE][2 * VOLUME_LIMIT + 11]; // (tour id, wins, volume)

  Double result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_ok_prob();
    }

    MapKey get( int i, int j, int k ) {
      return MapKey(i, PII(j, k));
    }

    Double get_ok_prob() {
      dp[0][0][VOLUME_LIMIT + k] = 1.0;
      
      for ( int tour = 0; tour < n; ++ tour ) {
        for ( int wins = 0; wins < n; ++ wins ) {
          for ( int volume = 0; volume < 2 * VOLUME_LIMIT + 11; ++ volume ) {
            dp[tour + 1][wins + 1][std::min(2 * VOLUME_LIMIT, volume + A[tour])] += dp[tour][wins][volume] * prob[tour];
            dp[tour + 1][wins][volume] += dp[tour][wins][volume] * ( 1.0 - prob[tour] );
          }
        }
      }

      Double res = 0.0;
      for ( int wins = l; wins <= n; ++ wins ) {
        for ( int volume = VOLUME_LIMIT; volume <= 2 * VOLUME_LIMIT; ++ volume ) {
          res += dp[n][wins][volume];
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
      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j < SIZE; ++ j ) {
          for ( int k = 0; k < VOLUME_LIMIT * 2 + 11; ++ k ) {
            dp[i][j][k] = 0.0;
          }
        }
      }
      result = 0.0;
    }

    bool input() {
      if ( ! ( cin >> n >> l >> k ) )
        return false;
      for ( int i = 0; i < n; ++ i ) {
        int p;
        cin >> p;
        prob[i] = (Double)p / 100.0;
      }
      for ( int i = 0; i < n; ++ i ) {
        cin >> A[i];
      }
      return true;
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

