
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
  const int SIZE = 100 + 11;
  const int OFF = 0;
  const int ON = 1;
  const LL DP_NONE = -1;

  // storages
  int n, m;
  string jiro_p[SIZE];
  int jiro_s[SIZE];
  int ciel_s[SIZE];

  int jiro_def_s[SIZE];
  int jiro_def_s_num;
  int jiro_atk_s[SIZE];
  int jiro_atk_s_num;

  LL dp[SIZE][SIZE][SIZE][2];
  LL result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      split_jiro();
      sort_cards();
      result = calc_maximum_damages();
    }

    void sort_cards() {
      std::sort(jiro_def_s, jiro_def_s + jiro_def_s_num, std::less<int>());
      std::sort(jiro_atk_s, jiro_atk_s + jiro_atk_s_num, std::less<int>());
      std::sort(ciel_s, ciel_s + m, std::greater<int>());
    }

    LL calc_maximum_damages() {
      dp[0][0][0][OFF] = 0;
      for ( int jiro_atk = jiro_atk_s_num; jiro_atk >= 0; -- jiro_atk ) {
        for ( int jiro_def = jiro_def_s_num; jiro_def >= 0; -- jiro_def ) {
          for ( int ciel = m; ciel >= 0; -- ciel ) {
            for ( int flag = 0; flag < 2; ++ flag ) {
              if ( dp[jiro_atk][jiro_def][ciel][flag] == DP_NONE )
                continue;
              if ( jiro_atk < jiro_atk_s_num && ciel_s[ciel] >= jiro_atk_s[jiro_atk] ) {
                dp[jiro_atk + 1][jiro_def][ciel + 1][flag] = std::max(
                    dp[jiro_atk + 1][jiro_def][ciel + 1][flag],
                    dp[jiro_atk][jiro_def][ciel][flag] + ciel_s[ciel] - jiro_atk_s[jiro_atk]
                    );
              }
              if ( jiro_def < jiro_def_s_num && ciel_s[ciel] > jiro_def_s[jiro_def] ) {
                dp[jiro_atk][jiro_def + 1][ciel + 1][flag] = std::max(
                    dp[jiro_atk][jiro_def + 1][ciel + 1][flag],
                    dp[jiro_atk][jiro_def][ciel][flag]
                    );
              }
              dp[jiro_atk][jiro_def][ciel + 1][ON] = std::max(
                  dp[jiro_atk][jiro_def][ciel + 1][ON],
                  dp[jiro_atk][jiro_def][ciel][flag] + ciel_s[ciel]
                  );
            }
          }
        }
      }

      LL res = 0;
      for ( int i = 0; i <= jiro_atk_s_num; ++ i ) {
        for ( int j = 0; j <= jiro_def_s_num; ++ j ) {
          for ( int k = 0; k <= m; ++ k ) {
            if ( i == jiro_atk_s_num && j == jiro_def_s_num ) {
              res = std::max(res, dp[i][j][k][ON]);
            }
            res = std::max(res, dp[i][j][k][OFF]);
          }
        }
      }
      return res;
    }

    void split_jiro() {
      for ( int i = 0; i < n; ++ i ) {
        if ( jiro_p[i] == "ATK" ) {
          jiro_atk_s[jiro_atk_s_num ++] = jiro_s[i];
        } else {
          jiro_def_s[jiro_def_s_num ++] = jiro_s[i];
        }
      }
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
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE; ++ j )
          for ( int k = 0; k < SIZE; ++ k )
            for ( int l = 0; l < 2; ++ l )
              dp[i][j][k][l] = DP_NONE;
      jiro_atk_s_num = 0;
      jiro_def_s_num = 0;
    }

    bool input() {
      if ( ! ( cin >> n >> m ) )
        return false;
      for ( int i = 0; i < n; ++ i ) {
        cin >> jiro_p[i] >> jiro_s[i];
      }
      for ( int i = 0; i < m; ++ i ) {
        cin >> ciel_s[i];
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

