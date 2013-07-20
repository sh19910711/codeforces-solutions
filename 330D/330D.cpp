
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
  typedef std::pair <int, II> Node;
  typedef std::priority_queue<Node, std::vector<Node>, std::greater<Node> > Queue;
  typedef std::set <int> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE        = 1000 + 11;
  const int INF         = std::numeric_limits<int>::max();
  const char CHAR_START = 'S';
  const char CHAR_EXIT  = 'E';
  const char CHAR_ZERO  = '0';
  const char CHAR_TREE  = 'T';

  const int dr[4] = {1, -1, 0, 0};
  const int dc[4] = {0, 0, 1, -1};

  // storages
  int H;
  int W;
  string S[SIZE];

  int MC[SIZE][SIZE];

  int min_dist[SIZE][SIZE];
  int exit_r;
  int exit_c;
  int start_r;
  int start_c;

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( S[i][j] == CHAR_START ) {
            start_r = i;
            start_c = j;
            S[i][j] = CHAR_ZERO;
          } else if ( S[i][j] == CHAR_EXIT ) {
            exit_r = i;
            exit_c = j;
            S[i][j] = CHAR_ZERO;
          }
        }
      }

      fill_min_dist();

      int min_steps = get_minimum_steps();

      result = 0;
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( S[i][j] != CHAR_TREE && min_dist[i][j] <= min_steps ) {
            result += S[i][j] - '0';
          }
        }
      }
    }

    int get_minimum_steps() {
      Queue Q;
      Q.push(Node(0, II(start_r, start_c)));
      MC[start_r][start_c] = 0;

      while ( ! Q.empty() ) {
        Node node = Q.top();
        Q.pop();

        int steps = node.first;
        int next_steps = steps + 1;
        int r = node.second.first;
        int c = node.second.second;

        if ( r == exit_r && c == exit_c )
          return steps;

        for ( int k = 0; k < 4; ++ k ) {
          int nr = r + dr[k];
          int nc = c + dc[k];
          if ( nr < 0 || nr >= H || nc < 0 || nc >= W )
            continue;
          if ( S[nr][nc] == CHAR_TREE )
            continue;
          if ( next_steps >= MC[nr][nc] )
            continue;
          MC[nr][nc] = next_steps;
          Q.push(Node(next_steps, II(nr, nc)));
        }
      }

      return -1;
    }

    void fill_min_dist() {
      std::queue <II> Q;
      Q.push(II(exit_r, exit_c));
      min_dist[exit_r][exit_c] = 0;

      while ( ! Q.empty() ) {
        II node = Q.front();
        Q.pop();

        int r = node.first;
        int c = node.second;
        int next_steps = min_dist[r][c] + 1;

        for ( int k = 0; k < 4; ++ k ) {
          int nr = r + dr[k];
          int nc = c + dc[k];
          if ( nr < 0 || nr >= H || nc < 0 || nc >= W )
            continue;
          if ( S[nr][nc] == CHAR_TREE )
            continue;
          if ( next_steps >= min_dist[nr][nc] )
            continue;
          min_dist[nr][nc] = next_steps;
          Q.push(II(nr, nc));
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
          min_dist[i][j] = INF;
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE; ++ j )
          MC[i][j] = INF;
    }

    bool input() {
      if ( ! ( cin >> H >> W ) )
        return false;
      for ( int i = 0; i < H; ++ i )
        cin >> S[i];
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

