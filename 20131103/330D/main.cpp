
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

// @snippet<sh19910711/contest:solution/define_classes.cpp>
namespace solution {
  class Solution;
  class Solver;
  struct InputStorage;
  struct OutputStorage;
  struct DataStorage;
  class Storages;
}

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    
  protected:
    SolutionInterface() {}
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
    virtual void before_action( const int& test_no ) const {}
    virtual void after_action( const int& test_no ) const {}
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}
    virtual int run() {
      this->pre_calc();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:search/search_interface.cpp>
namespace search {
  template <class Node> class SearchInterface {
  public:
    virtual Node search() = 0;
  };
}

namespace search {
  template <class Node> class BreadthFirstSearchInterface: public SearchInterface<Node> {
  // TODO
  // public:
  //   virtual Node search()                            = 0;
  protected:
    virtual void init()                              = 0;
    virtual bool has_next_node()                     = 0;
    virtual void visit_next_node( const Node& node ) = 0;
    virtual void push_next_node( const Node& node )  = 0;
    virtual Node get_next_node()                     = 0;
    virtual Node get_none_node()                     = 0;
    virtual bool is_not_min_dist_node( const Node& node ) = 0;
    virtual void set_min_dist( const Node& node )     = 0;
    virtual bool is_goal_node( const Node& node )    = 0;
  };
}

namespace search {
  template <class Node> class BreadthFirstSearchBase: public BreadthFirstSearchInterface<Node> {
  public:
    Node search() {
      Node res = this->get_none_node();
      this->init();
      while ( this->has_next_node() ) {
        Node node = this->get_next_node();
        if ( this->is_goal_node(node) ) {
          res = node;
        }
        this->visit_next_node(node);
      }
      return res;
    }
  };
}

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
      if ( this->is_not_min_dist_node(node) )
        return;
      Q.push(node);
      this->set_min_dist(node);
    }
    
    // TODO
  private:
    std::queue <Node> Q;
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

namespace solution {
  // constant vars
  const int SIZE        = 1000 + 11;
  const int INF         = std::numeric_limits<int>::max();
  const char CELL_START = 'S';
  const char CELL_GOAL  = 'E';
  const char CELL_TREE  = 'T';
  const char CELL_EMPTY = '0';
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types

  struct Node {
    int r;
    int c;
    int steps;
  };

  const int dr[4] = {0, 0, 1, -1};
  const int dc[4] = {1, -1, 0, 0};
  const Node NODE_NONE = {INF, INF, INF};

  class BFS: public search::BreadthFirstSearch<Node> {
  public:
    void init() {
      for ( int i = 0; i < h; ++ i )
        for ( int j = 0; j < w; ++ j )
          min_dist[i][j] = INF;
    }

    void visit_next_node( const Node& node ) {
      for ( int k = 0; k < 4; ++ k ) {
        int nr = node.r + dr[k];
        int nc = node.c + dc[k];
        int nsteps = node.steps + 1;
        if ( nr < 0 || nr >= h || nc < 0 || nc >= w )
          continue;
        if ( nr == sr && nc == sc )
          continue;
        if ( t[nr][nc] == CELL_TREE )
          continue;
        Node next = { nr, nc, nsteps };
        push_next_node(next);
      }
    }

    Node get_none_node() {
      return NODE_NONE;
    }

    bool is_not_min_dist_node( const Node& node ) {
      return node.steps >= min_dist[node.r][node.c];
    }

    void set_min_dist( const Node& node ) {
      min_dist[node.r][node.c] = node.steps;
    }

    bool is_goal_node( const Node& node ) {
      return node.r == gr && node.c == gc;
    }

    void set_start_node( const Node& node ) {
      sr = node.r;
      sc = node.c;
      push_next_node(node);
    }

    void set_goal_node( const Node& node ) {
      gr = node.r;
      gc = node.c;
    }

    void set_grid( const int w, const int h, const string* t ) {
      this->w = w;
      this->h = h;
      this->t = t;
    }

    int get_lower_visits() {
      int cnt = 0;
      for ( int i = 0; i < h; ++ i ) {
        for ( int j = 0; j < w; ++ j ) {
          if ( min_dist[gr][gc] >= min_dist[i][j] && std::isdigit(t[i][j]) ) {
            cnt += t[i][j] - '0';
          }
        }
      }
      return cnt;
    }

  private:
    int min_dist[SIZE][SIZE];
    int w;
    int h;
    int sr;
    int sc;
    int gr;
    int gc;
    const string* t;
  };

}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    int H;
    int W;
    string T[SIZE];
  };
  
  struct OutputStorage {
    int result;
  };
  
  struct DataStorage {
  };
  
  struct Storages {
    InputStorage  in;
    OutputStorage out;
    DataStorage   data;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  BFS bfs;

  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      out.result = find_minimum_battles(in.W, in.H, in.T);
      return out;
    }
    
  protected:
    static int find_minimum_battles( const int w, const int h, const string* t ) {
      Node start_node = {0, 0, 0};
      for ( int i = 0; i < h; ++ i ) {
        for ( int j = 0; j < w; ++ j ) {
          if ( t[i][j] == CELL_START ) {
            start_node.r = i;
            start_node.c = j;
          }
        }
      }
      Node goal_node = {0, 0, 0};
      for ( int i = 0; i < h; ++ i ) {
        for ( int j = 0; j < w; ++ j ) {
          if ( t[i][j] == CELL_GOAL ) {
            goal_node.r = i;
            goal_node.c = j;
          }
        }
      }

      bfs.set_grid(w, h, t);
      bfs.set_start_node(goal_node);
      bfs.set_goal_node(start_node);
      bfs.search();
      return bfs.get_lower_visits();
    }

    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {}
    Solution(Storages* p): storages(p) {}
    
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }
    
    bool input( InputStorage& in ) {
      if ( ! ( std::cin >> in.H >> in.W ) )
        return false;
      for ( int i = 0; i < in.H; ++ i )
        std::cin >> in.T[i];
      return true;
    }
    
    void output( const OutputStorage& out ) {
      std::cout << out.result << endl;
    }
    
  private:
    Solver solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif


