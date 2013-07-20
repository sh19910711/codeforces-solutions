
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
  const int SIZE   = 100 + 11;
  const char EVIL  = 'E';
  const char EMPTY = '.';
  const char FILLED = '#';
  const int NONE = -1;
  // storages
  int n;
  string S[SIZE];

  bool row_filled[SIZE];
  bool col_filled[SIZE];
  int row_evils[SIZE];
  int col_evils[SIZE];

  int results;
  int R[SIZE];
  int C[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      results = get_minimum_ways();
    }

    int get_minimum_ways() {
      for ( int i = 0; i < n; ++ i ) {
        row_evils[i] = count_evils_row(i);
        col_evils[i] = count_evils_col(i);
      }

      if ( is_invalid_case() )
        return NONE;

      int res = 0;

      for ( int i = 0; i < n; ++ i ) {
        if ( S[i][i] == EMPTY ) {
          R[res] = i + 1;
          C[res] = i + 1;
          res ++;
          row_filled[i] = true;
          col_filled[i] = true;
        }
      }

      for ( int i = 0; i < n; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          if ( S[i][j] == EVIL )
            continue;
          if ( ! row_filled[i] && ! col_filled[j] ) {
            R[res] = i + 1;
            C[res] = j + 1;
            res ++;
            row_filled[i] = true;
            col_filled[i] = true;
          }
        }
      }

      for ( int i = 0; i < n; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          if ( S[i][j] == EVIL )
            continue;
          if ( ! row_filled[i] ) {
            R[res] = i + 1;
            C[res] = j + 1;
            res ++;
            row_filled[i] = true;
            col_filled[i] = true;
          }
        }
      }

      for ( int i = 0; i < n; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          if ( S[i][j] == EVIL )
            continue;
          if ( ! col_filled[j] ) {
            R[res] = i + 1;
            C[res] = j + 1;
            res ++;
            row_filled[i] = true;
            col_filled[i] = true;
          }
        }
      }

      return res;
    }

    bool is_invalid_case() {
      for ( int i = 0; i < n; ++ i )
        for ( int j = 0; j < n; ++ j )
          if ( row_evils[i] == n && col_evils[j] == n )
            return true;
      return false;
    }

    int count_evils_row( int row ) {
      int res = 0;
      for ( int i = 0; i < n; ++ i )
        if ( S[row][i] == EVIL )
          res ++;
      return res;
    }

    int count_evils_col( int col ) {
      int res = 0;
      for ( int i = 0; i < n; ++ i )
        if ( S[i][col] == EVIL )
          res ++;
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
      results = 0;
      fill(row_filled, row_filled + SIZE, false);
      fill(col_filled, col_filled + SIZE, false);
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> S[i];
      return true;
    }

    void output() {
      if ( results == NONE ) {
        cout << -1 << endl;
      } else {
        for ( int i = 0; i < results; ++ i ) {
          cout << R[i] << " " << C[i] << endl;
        }
      }
      cout << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

