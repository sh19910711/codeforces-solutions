
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

// @snippet<sh19910711/contest:search/search_interface.cpp>
namespace search {
  template <class Node> class SearchInterface {
  public:
    virtual Node search() = 0;
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search_base.cpp>
namespace search {
  template <class Node> class BreadthFirstSearchBase: public SearchInterface<Node> {
  public:
    virtual Node search() {
      Node res = get_none_node();
      init();
      while ( has_next_node() ) {
        Node node = get_next_node();
        if ( is_goal_node(node) )
          res = node;
        visit_next_node(node);
      }
      return res;
    }
    
  protected:
    virtual void init()                              = 0; 
    virtual bool has_next_node()                     = 0;
    virtual void visit_next_node( const Node& node ) = 0;
    virtual void push_next_node( const Node& node )  = 0;
    virtual Node get_next_node()                     = 0;
    virtual Node get_none_node()                     = 0;
    virtual bool is_visited_node( const Node& node ) = 0;
    virtual void set_visited( const Node& node )     = 0;
    virtual bool is_goal_node( const Node& node )    = 0;
    
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search.cpp>
namespace search {
  template <class Node> class BreadthFirstSearch: public BreadthFirstSearchBase<Node> {
  protected:
    virtual void init() {}
    
    bool has_next_node() {
      return ! Q.empty();
    }
    
    Node get_next_node() {
      Node res = Q.front();
      Q.pop();
      return res;
    }
    
    void push_next_node( const Node& node ) {
      Q.push(node);
    }
    
  protected:
    std::queue <Node> Q;
  };
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 1000 + 11;
  const int dr[4] = {1, -1, 0, 0};
  const int dc[4] = {0, 0, 1, -1};
  const char START_CELL = 'S';
  const char GOAL_CELL = 'E';
  const char WALL_CELL = 'T';
  const char EMPTY_CELL = '0';
  const int INF = std::numeric_limits<int>::max();
  // storages
  int H, W;
  string S[SIZE];
  
  int start_r, start_c;
  int goal_r, goal_c;
  int min_dist[SIZE][SIZE];
  int result;
  
  class Node {
  public:
    Node(): r(0), c(0), steps(0) {}
    Node( int r, int c, int steps ): r(r), c(c), steps(steps) {}
    
    friend ostream& operator <<( ostream& os, const Node& node ) {
      return os << "{" << node.r << ", " << node.c << ": steps = " << node.steps << "}";
    }
    
    int steps;
    int r;
    int c;
  };
  const Node NONE_NODE(INF, INF, INF);
  
  class MyBFS: public search::BreadthFirstSearch<Node> {
  protected:
    virtual void init() {
      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j < SIZE; ++ j ) {
          min_dist[i][j] = INF;
        }
      }
      Node start_node(goal_r, goal_c, 0);
      set_visited(start_node);
      push_next_node(start_node);
    }
    
    virtual void visit_next_node( const Node& node ) {
      int nsteps = node.steps + 1;
      for ( int k = 0; k < 4; ++ k ) {
        int nr = node.r + dr[k];
        int nc = node.c + dc[k];
        if ( nr < 0 || nr >= H || nc < 0 || nc >= W )
          continue;
        if ( S[nr][nc] == WALL_CELL )
          continue;
        Node next_node(nr, nc, nsteps);
        if ( is_visited_node(next_node) )
          continue;
        set_visited(next_node);
        push_next_node(next_node);
      }
    }
    
    virtual Node get_none_node() {
      return NONE_NODE;
    }
    
    virtual bool is_goal_node( const Node& node ) {
      return node.r == start_r && node.c == start_c;
    }
    
    virtual bool is_visited_node( const Node& node ) {
      return node.steps >= min_dist[node.r][node.c];
    }
    
    virtual void set_visited( const Node& node ) {
      min_dist[node.r][node.c] = node.steps;
    }
  };
  
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( S[i][j] == START_CELL ) {
            start_r = i;
            start_c = j;
            S[i][j] = EMPTY_CELL;
          }
          if ( S[i][j] == GOAL_CELL ) {
            goal_r = i;
            goal_c = j;
            S[i][j] = EMPTY_CELL;
          }
        }
      }
      bfs.search();
      result = get_minimum_battles();
    }
    
    int get_minimum_battles() {
      int res = 0;
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( min_dist[i][j] <= min_dist[start_r][start_c] ) {
            res += to_int(S[i][j]);
          }
        }
      }
      return res;
    }
    
    int to_int( char c ) {
      return c - '0';
    }
    
  private:
    MyBFS bfs;
    
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
      result = 0;
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


