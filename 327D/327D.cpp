
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
  const int GRID_SIZE = 500 + 11;
  const int SIZE = 1000000 + 11;

  const char CHAR_EMPTY = '.';
  const char CHAR_BLUE = 'B';
  const char CHAR_RED = 'R';

  const string TYPE_BLUE = "B";
  const string TYPE_RED = "R";
  const string TYPE_DELETE = "D";

  const int dr[4] = {1, -1, 0, 0};
  const int dc[4] = {0, 0, 1, -1};

  // storages
  int H, W;
  string grid[GRID_SIZE];

  int operations;
  string T[SIZE];
  int R[SIZE];
  int C[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( int i = 0; i < H; ++ i )
        for ( int j = 0; j < W; ++ j )
          rec(i, j, i, j);
    }

    void rec( int r, int c, int sr, int sc ) {
      if ( grid[r][c] != CHAR_EMPTY )
        return;

      put_blue(r, c);

      for ( int k = 0; k < 4; ++ k ) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if ( nr < 0 || nr >= H || nc < 0 || nc >= W )
          continue;
        rec(nr, nc, sr, sc);
      }

      if ( r != sr || c != sc ) {
        put_red(r, c);
      }

    }

    void put_red( int r, int c ) {
      grid[r][c] = CHAR_RED;

      T[operations] = TYPE_DELETE;
      R[operations] = r;
      C[operations] = c;
      operations ++;

      T[operations] = TYPE_RED;
      R[operations] = r;
      C[operations] = c;
      operations ++;
    }

    void put_blue( int r, int c ) {
      grid[r][c] = CHAR_BLUE;
      T[operations] = TYPE_BLUE;
      R[operations] = r;
      C[operations] = c;
      operations ++;
    }

    void print_grid() {
      cout << "grid:" << endl;
      for ( int i = 0; i < H; ++ i )
        cout << grid[i] << endl;
      cout << endl;
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
      operations = 0;
    }

    bool input() {
      if ( ! ( cin >> H >> W ) )
        return false;
      for ( int i = 0; i < H; ++ i )
        cin >> grid[i];
      return true;
    }

    void output() {
      cout << operations << endl;
      for ( int i = 0; i < operations; ++ i )
        cout << T[i] << " " << R[i] + 1 << " " << C[i] + 1 << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

