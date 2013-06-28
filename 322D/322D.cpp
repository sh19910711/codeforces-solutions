
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
  const int SIZE = 100 + 11;
  const string ATK = "ATK";
  const string DEF = "DEF";
  const int NONE = -1;
  const int ON = 1;
  const int OFF = 0;

  // storages
  int n, m;
  string JT[SIZE];
  LL JS[SIZE];

  LL JAT[SIZE];
  LL JDF[SIZE];
  int attackers;
  int defenses;
  LL JAT_bk[SIZE];
  LL JDF_bk[SIZE];
  int attackers_bk;
  int defenses_bk;

  LL CS[SIZE];
  int remains;
  LL CS_bk[SIZE];
  int remains_bk;

  LL dp[SIZE][SIZE][2];

  LL result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      prepare();
      result = calc_max();
    }

    void prepare() {
      attackers = 0;
      defenses = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( JT[i] == ATK ) {
          JAT[attackers] = JS[i];
          attackers ++;
        } else if ( JT[i] == DEF ) {
          JDF[defenses] = JS[i];
          defenses ++;
        }
      }
      sort(JAT, JAT + attackers, greater<LL>());
      sort(JDF, JDF + defenses, greater<LL>());

      sort(CS, CS + m);
      remains = m;
    }

    LL calc_max() {
      backup();

      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE; ++ j )
          for ( int k = 0; k < 2; ++ k )
            dp[i][j][k] = NONE;

      dp[0][0][0] = dp[0][0][1] = 0;
      for ( int i = 0; i < m; ++ i ) {
        for ( int j = 0; j <= n; ++ j ) {
          for ( int k = 0; k < 2; ++ k ) {
            if ( dp[i][j][k] == NONE )
              continue;

            int st = JS[i];
            int ni = i + 1;
            int nj = j + 1;

            dp[ni][j][OFF] = max(dp[ni][j][OFF], dp[i][j][k]);
            dp[ni][nj][OFF] = max(dp[ni][nj][OFF], dp[i][j][k]);
            dp[i][j][OFF] = max(dp[i][j][OFF], dp[i][j][k]);
            dp[i][nj][OFF] = max(dp[i][nj][OFF], dp[i][j][k]);

            if ( j == 0 )
              continue;

            int ind = j - 1;
            string type = JT[ind];
            if ( type == ATK && CS[i] >= st ) {
              int nk = min(ON, k);
              dp[ni][nj][nk] = max(dp[ni][nj][nk], dp[i][j][k] + CS[i] - st);
            } else if ( type == DEF && CS[i] > st ) {
              int nk = min(ON, k);
              dp[ni][nj][nk] = max(dp[ni][nj][nk], dp[i][j][k]);
            }
          }
        }
      }

      LL res = 0;

      for ( int i = 0; i <= m; ++ i ) {
        for ( int j = 0; j <= n; ++ j ) {
          for ( int k = 0; k < 2; ++ k ) {
            res = max(res, dp[i][j][k]);
            if ( j == n && k == ON && dp[i][j][k] != NONE ) {
              res = max(res, dp[i][j][k] + accumulate(CS + i, CS + m, 0LL));
            }
          }
        }
      }

      return res;
    }

    void backup() {
      for ( int i = 0; i < attackers; ++ i )
        JAT_bk[i] = JAT[i];
      for ( int i = 0; i < defenses; ++ i )
        JDF_bk[i] = JDF[i];
      attackers_bk = attackers;
      defenses_bk = defenses;

      remains_bk = remains;
      for ( int i = 0; i < remains; ++ i )
        CS_bk[i] = CS[i];
    }

    void reset_backup() {
      for ( int i = 0; i < attackers_bk; ++ i )
        JAT[i] = JAT_bk[i];
      for ( int i = 0; i < defenses_bk; ++ i )
        JDF[i] = JDF_bk[i];
      attackers = attackers_bk;
      defenses = defenses_bk;

      remains = remains_bk;
      for ( int i = 0; i < remains; ++ i )
        CS[i] = CS_bk[i];
    }

    void print_cs() {
      for ( int i = 0; i < remains; ++ i ) {
        cout << i << ": " << CS[i] << endl;
      }
    }

    void remove_value( int pos ) {
      for ( int i = pos; i + 1 < remains; ++ i ) {
        CS[i] = CS[i + 1];
      }
      remains --;
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
      if ( ! ( cin >> n >> m ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> JT[i] >> JS[i];
      for ( int i = 0; i < m; ++ i )
        cin >> CS[i];
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

