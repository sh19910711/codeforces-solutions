
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
  const int SIZE = 60 + 1;
  const int QUERIES = 100000 + 11;
  const int K_MAX = 60 + 11;
  const int DP_NONE = std::numeric_limits<int>::max();
  // storages
  int n, m, r;
  int T[SIZE][SIZE][SIZE]; // T[car][from][to]
  int QS[QUERIES];
  int QT[QUERIES];
  int QK[QUERIES];

  int dp[K_MAX][SIZE][SIZE];

  int query_result[QUERIES];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      find_minimum_time_each_car();
      find_minimum_time();
      for ( int i = 0; i < r; ++ i ) {
        query_result[i] = query(QS[i], QT[i], QK[i]);
      }
    }

    void normalize() {
      for ( int i = 0; i < r; ++ i ) {
        QS[i] --;
        QT[i] --;
      }
    }

    void find_minimum_time() {
      for ( int i = 0; i < m; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          for ( int k = 0; k < n; ++ k ) {
            if ( j == k ) {
              continue;
            }
            dp[0][j][k] = std::min(dp[0][j][k], T[i][j][k]);
          }
        }
      }

      for ( int k = 1; k < K_MAX; ++ k ) {
        for ( int i = 0; i < n; ++ i ) {
          for ( int j = 0; j < n; ++ j ) {
            dp[k][i][j] = std::min(dp[k][i][j], dp[k - 1][i][j]);
            for ( int mid = 0; mid < n; ++ mid ) {
              if ( j == mid || mid == i ) {
                continue;
              }
              dp[k][i][j] = std::min(dp[k][i][j], dp[k - 1][i][mid] + dp[0][mid][j]);
            }
          }
        }
      }
    }

    void find_minimum_time_each_car() {
      for ( int i = 0; i < m; ++ i ) {
        find_minimum_time_each_car(i);
      }
    }

    void find_minimum_time_each_car( int car ) {
      for ( int k = 0; k < n; ++ k ) {
        for ( int i = 0; i < n; ++ i ) {
          for ( int j = 0; j < n; ++ j ) {
            if ( i == j || j == k || k == i ) {
              continue;
            }
            T[car][i][j] = std::min(T[car][i][j], T[car][i][k] + T[car][k][j]);
          }
        }
      }
    }

    int query( int s, int t, int k ) {
      k = std::min(K_MAX - 1, k);
      return dp[k][s][t];
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

    virtual void init() {
      for ( int i = 0; i < K_MAX; ++ i ) {
        for ( int j = 0; j < SIZE; ++ j ) {
          for ( int k = 0; k < SIZE; ++ k ) {
            dp[i][j][k] = DP_NONE;
          }
        }
      }
    }

    virtual bool input() {
      if ( ! ( cin >> n >> m >> r ) )
        return false;
      for ( int i = 0; i < m; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          for ( int k = 0; k < n; ++ k ) {
            cin >> T[i][j][k];
          }
        }
      }
      for ( int i = 0; i < r; ++ i ) {
        cin >> QS[i] >> QT[i] >> QK[i];
      }
      return true;
    }

    virtual void output() {
      for ( int i = 0; i < r; ++ i ) {
        cout << query_result[i] << endl;
      }
      cout << endl;
    }
    
  protected:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

