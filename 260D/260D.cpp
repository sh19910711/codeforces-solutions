
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

// @snippet<sh19910711/contest:io/pair.cpp>
namespace io {
  template <class A, class B> std::ostream& operator<<( std::ostream& os, const std::pair<A,B>& p ) {
    return os << "(" << p.first << "," << p.second << ")";
  }
  template <class A, class B> std::istream& operator>>( std::istream& is, std::pair<A,B>& p ) {
    return is >> p.first >> p.second;
  }
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
  using namespace io;
  
  class Edge {
  public:
    int from;
    int to;
    int weight;
    
    Edge() {}
    Edge( int from, int to, int weight ): from(from), to(to), weight(weight) {}
    
    friend ostream& operator << ( ostream& os, const Edge& edge ) {
      return os << edge.from << " " << edge.to << " " << edge.weight;
    }
  };
  
  typedef set <II> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int TYPES = 2;
  const int COLOR_WHITE = 0;
  const int COLOR_BLACK = 1;
  // storages
  int n;
  int C[SIZE];
  int S[SIZE];
  
  Set visited;
  II vertices[TYPES][SIZE]; // (weight, pos)
  int vertices_num[TYPES];
  Edge edges[SIZE];
  int edges_num;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      for ( int i = 0; i < TYPES; ++ i )
        sort(vertices[i], vertices[i] + vertices_num[i], greater<II>());
      
      rec(0, 0);
    }
    
    void rec( int x, int y ) {
      if ( visited.count(II(x, y)) ) {
        if ( x + 1 < vertices_num[COLOR_WHITE] && y + 1 < vertices_num[COLOR_BLACK] ) {
          return rec(x + 1, y + 1);
        } else if ( x + 1 < vertices_num[COLOR_WHITE] || y + 1 < vertices_num[COLOR_BLACK] ) {
          return rec(min(x + 1, vertices_num[COLOR_WHITE] - 1), min(y + 1, vertices_num[COLOR_BLACK] - 1));
        }
        return;
      }
      visited.insert(II(x, y));

      if ( x >= vertices_num[COLOR_WHITE] && y >= vertices_num[COLOR_BLACK] )
        return;

      int& white_weight = vertices[COLOR_WHITE][x].first;
      const int white_index = vertices[COLOR_WHITE][x].second;
      int& black_weight = vertices[COLOR_BLACK][y].first;
      const int black_index = vertices[COLOR_BLACK][y].second;
      
      int min_subtract = min(white_weight, black_weight);
      white_weight -= min_subtract;
      black_weight -= min_subtract;
      edges[edges_num ++] = Edge(white_index, black_index, min_subtract);
 
      if ( white_weight <= 0 ) {
        return rec(min(vertices_num[COLOR_WHITE] - 1, x + 1), y);
      }
      if ( black_weight <= 0 ) {
        return rec(x, min(vertices_num[COLOR_BLACK] - 1, y + 1));
      }
    }
    
    void normalize() {
      for ( int i = 0; i < n; ++ i ) {
        vertices[C[i]][vertices_num[C[i]] ++] = II(S[i], i + 1);
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
      visited.clear();
      for ( int i = 0; i < TYPES; ++ i )
        vertices_num[i] = 0;
      edges_num = 0;
    }
    
    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> C[i] >> S[i];
      return true;
    }
    
    void output() {
      for ( int i = 0; i < edges_num; ++ i )
        cout << edges[i] << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}


