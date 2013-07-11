
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
  const int NONE = std::numeric_limits<int>::min() / 2;
  const int ON  = 1;
  const int OFF = 0;

  const string ATK = "ATK";
  const string DEF = "DEF";

  // storages
  int n, m;
  string JT[SIZE];
  int JS[SIZE];
  int atk_num;
  int atk[SIZE];
  int def_num;
  int def[SIZE];
  int CS[SIZE];

  int max_damages[SIZE][SIZE][SIZE][2];
  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      pre_john();

      sort(CS, CS + m);
      sort(atk, atk + atk_num);
      sort(def, def + def_num);

      result = get_max();
    }

    void pre_john() {
      atk_num = 0;
      def_num = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( JT[i] == ATK ) {
          atk[atk_num ++] = JS[i];
        } else if ( JT[i] == DEF ) {
          def[def_num ++] = JS[i];
        }
      }
    }

    int get_max() {
      int res1 = rec(0, 0, 0, OFF);
      int res2 = rec(0, 0, 0, ON);
      return max(res1, res2);
    }

    int rec( int i, int j, int k, int flag ) {
      if ( max_damages[i][j][k][flag] != NONE )
        return max_damages[i][j][k][flag];

      if ( k >= m ) {
        if ( flag == ON ) {
          if ( i < atk_num || j < def_num )
            return NONE;
          return 0;
        }
        return 0;
      }

      int res = NONE;

      if ( k < m )
        res = max(res, rec(i, j, k + 1, flag));

      if ( k < m )
        res = max(res, rec(i, j, k + 1, ON) + CS[k]);

      if ( i < atk_num && k < m && CS[k] >= atk[i] )
        res = max(res, rec(i + 1, j, k + 1, flag) + CS[k] - atk[i]);

      if ( j < def_num && k < m && CS[k] > def[j] )
        res = max(res, rec(i, j + 1, k + 1, flag));

      return max_damages[i][j][k][flag] = res;
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
              max_damages[i][j][k][l] = NONE;
      result = NONE;
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

