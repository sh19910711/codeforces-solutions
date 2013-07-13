
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
  
  class Node {
  public:
    int pos;
    Node* prev_node;
    Node* next_node;
    bool alive_flag;
    Node( int pos, Node* prev_node, Node* next_node ):
      pos(pos),
      prev_node(prev_node),
      next_node(next_node),
      alive_flag(true) {
      }
    friend ostream& operator << ( ostream& os, const Node& node ) {
      return os << "(pos = " << node.pos << ", links = " << node.prev_node << ", " << node.next_node << ", alive? = " << node.alive_flag << ")";
    }
  };
  typedef vector<Node> Nodes;

}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int NONE = -1;
  // storages
  int n;
  int A[SIZE];
  Nodes nodes;

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_steps();
    }

    int get_steps() {
      for ( int i = 0; i < n; ++ i ) {
        nodes.push_back(Node(i, NULL, NULL));
      }
      for ( int i = 0; i < n; ++ i )
        if ( i - 1 >= 0 )
          nodes[i - 1].next_node = &nodes[i];
      for ( int i = 0; i < n; ++ i )
        if ( i + 1 < n )
          nodes[i + 1].prev_node = &nodes[i];

      std::vector<Node*> current;
      for ( int i = 0; i < n; ++ i )
        current.push_back(&nodes[i]);

      for ( int t = 0; t < SIZE; ++ t ) {

        if ( current.empty() )
          return t;

        std::vector<Node*> dead;
        Node *cur = current[0];
        while ( cur && cur->next_node ) {
          if ( A[cur->pos] > A[cur->next_node->pos] ) {
            dead.push_back(cur->next_node);
            cur->next_node->alive_flag = false;
          }
          cur = cur->next_node;
        }

        if ( dead.empty() )
          return t;

        std::vector<Node*> next;
        for ( vector<Node*>::iterator it_i = dead.begin(); it_i != dead.end(); ++ it_i ) {
          Node* p = *it_i;
          if ( p->prev_node )
            p->prev_node->next_node = p->next_node;
          if ( p->next_node ) {
            p->next_node->prev_node = p->prev_node;
            if ( p->next_node->alive_flag )
              next.push_back(p->next_node);
          }
        }
        current = next;
      }

      return -2;
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
      nodes.clear();
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> A[i];
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

