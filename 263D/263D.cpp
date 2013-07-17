
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
  const int SIZE = 100000 + 11;
  // storages
  int n, m, k;
  int A[SIZE];
  int B[SIZE];

  VI G[SIZE];

  int PC;
  int P[SIZE];
  bool visited[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      if ( rec(0, 0, 0) )
        return;
      for ( int i = 0; i < n; ++ i ) {
        fill(visited, visited + SIZE, false);
        int start = rand() % n;
        for ( int j = 0; j < 10; ++ j )
          start = ( start + rand() % n ) % n;
        if ( rec(start, start, 0) )
          return;
      }
    }

    void normalize() {
      for ( int i = 0; i < m; ++ i ) {
        A[i] --;
        B[i] --;
      }
      normalize_graph();
    }

    void normalize_graph() {
      for ( int i = 0; i < m; ++ i ) {
        int a = A[i];
        int b = B[i];
        G[a].push_back(b);
        G[b].push_back(a);
      }
    }

    bool rec( int from, int start, int depth ) {
      if ( depth >= k + 1 && start == from )
        return true;
      if ( visited[from] )
        return false;
      visited[from] = true;

      int num_vertices = G[from].size();
      for ( int i = 0; i < num_vertices; ++ i ) {
        int to = G[from][i];
        if ( rec(to, start, depth + 1) ) {
          P[PC ++] = from + 1;
          return true;
        }
      }

      return false;
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
      PC = 0;
      fill(visited, visited + SIZE, false);
      fill(G, G + SIZE, VI());
    }

    bool input() {
      if ( ! ( cin >> n >> m >> k ) )
        return false;
      for ( int i = 0; i < m; ++ i )
        cin >> A[i] >> B[i];
      return true;
    }

    void output() {
      cout << PC << endl;
      for ( int i = 0; i < PC; ++ i )
        cout << P[i] << " ";
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

