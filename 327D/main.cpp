
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
  const int SIZE = 500 + 11;
  const int MAX_COMMANDS = 1000000 + 11;
  const string BLUE_TYPE = "B";
  const string RED_TYPE = "R";
  const string DELETE_TYPE = "D";
  const char EMPTY_CELL = '.';
  const char WALL_CELL = '#';
  const char BLUE_CELL = 'B';
  const char RED_CELL = 'R';

  const int dr[4] = {1, -1, 0, 0};
  const int dc[4] = {0, 0, 1, -1};

  // storages
  int H, W;
  string S[SIZE];

  int command_num;
  string command_type[MAX_COMMANDS];
  int command_r[MAX_COMMANDS];
  int command_c[MAX_COMMANDS];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      command_num = 0;
      find_base_point();
    }

    void find_base_point() {
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( S[i][j] == EMPTY_CELL ) {
            rec(i, j, true);
          }
        }
      }
    }

    void add_command( string type, int r, int c ) {
      command_type[command_num] = type;
      command_r[command_num] = r;
      command_c[command_num] = c;
      command_num ++;
    }

    void rec( int r, int c, bool first ) {
      if ( S[r][c] != EMPTY_CELL )
        return;

      if ( first ) {
        S[r][c] = BLUE_CELL;
        add_command(BLUE_TYPE, r, c);
      } else {
        S[r][c] = RED_CELL;
        add_command(BLUE_TYPE, r, c);
      }

      for ( int k = 0; k < 4; ++ k ) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if ( nr < 0 || nr >= H || nc < 0 || nc >= W )
          continue;

        rec(nr, nc, false);
      }

      if ( ! first ) {
        add_command(DELETE_TYPE, r, c);
        add_command(RED_TYPE, r, c);
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

    bool input() {
      if ( ! ( cin >> H >> W ) )
        return false;
      for ( int i = 0; i < H; ++ i ) {
        cin >> S[i];
      }
      return true;
    }

    void output() {
      cout << command_num << endl;
      for ( int i = 0; i < command_num; ++ i ) {
        cout << command_type[i] << " " << command_r[i] + 1 << " " << command_c[i] + 1 << endl;
      }
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

