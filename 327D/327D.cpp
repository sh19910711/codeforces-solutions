
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
  typedef stack<II> Stack;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE          = 500 + 11;
  const int MAX_TIMES     = 1000000 + 11;
  const int TYPE_PUT_BLUE = 0;
  const int TYPE_PUT_RED  = 1;
  const int TYPE_DEL      = 2;
  const char CHAR_BLUE    = 'B';
  const char CHAR_RED     = 'R';
  const char CHAR_DEL     = 'D';
  const char WALL         = '#';
  const char EMPTY        = '.';

  // storages
  int H, W;
  string grid[SIZE];

  int times, cur;
  int T[MAX_TIMES];
  int R[MAX_TIMES];
  int C[MAX_TIMES];

  Stack st;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {

      // 横
      for ( int i = 0; i < H; ++ i ) {
        st = Stack();
        for ( int j = 0; j < W; ++ j ) {
          if ( grid[i][j] == WALL ) {
            if ( st.empty() )
              continue;

            II put_g = st.top();
            st.pop();
            cur --;
            T[cur] = TYPE_PUT_RED;
            R[cur] = put_g.first;
            C[cur] = put_g.second;
            cur ++;

            while ( st.size() >= 2 ) {
              II rep_to_g = st.top();
              st.pop();
              T[cur] = TYPE_DEL;
              R[cur] = rep_to_g.first;
              C[cur] = rep_to_g.second;
              cur ++;
              T[cur] = TYPE_PUT_RED;
              R[cur] = rep_to_g.first;
              C[cur] = rep_to_g.second;
              cur ++;
            }

          } else {
            T[cur] = TYPE_PUT_BLUE;
            R[cur] = i;
            C[cur] = j;
            cur ++;
            st.push(II(i, j));
          }
        }
      }

      // 縦
      int pre_cur = cur;
      st = Stack();
      for ( int i = 0; i + 1 < pre_cur; ++ i ) {
        if ( T[i] == TYPE_PUT_BLUE && C[i] == 1 + C[i + 1] ) {
          st.push(II(R[i], C[i]));
        } else {
          while ( st.size() >= 2 ) {
            II rep_to_g = st.top();
            st.pop();
              T[cur] = TYPE_DEL;
              R[cur] = rep_to_g.first;
              C[cur] = rep_to_g.second;
              cur ++;
              T[cur] = TYPE_PUT_RED;
              R[cur] = rep_to_g.first;
              C[cur] = rep_to_g.second;
              cur ++;
          }
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
      cur = 0;
    }

    bool input() {
      if ( ! ( cin >> H >> W ) )
        return false;
      for ( int i = 0; i < H; ++ i )
        cin >> grid[i];
      return true;
    }

    void output() {
      cout << cur << endl;
      for ( int i = 0; i < cur; ++ i ) {
        if ( T[i] == TYPE_DEL ) {
          cout << CHAR_DEL;
        } else if ( T[i] == TYPE_PUT_BLUE ) {
          cout << CHAR_BLUE;
        } else if ( T[i] == TYPE_PUT_RED ) {
          cout << CHAR_RED;
        }
        cout << " " << C[i] + 1 << " " << R[i] + 1 << endl;
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

