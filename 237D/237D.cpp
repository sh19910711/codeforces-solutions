
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
  typedef set <II> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int NONE = -1;
  const int INF = std::numeric_limits<int>::max();

  // storages
  int n;
  int A[SIZE];
  int B[SIZE];

  VI G[SIZE];

  int U[SIZE];
  int V[SIZE];
  int edges_num;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      generate_graph();
    }

    void normalize() {
      for ( int i = 0; i < n - 1; ++ i ) {
        A[i] --;
        B[i] --;
      }
      for ( int i = 0; i < n - 1; ++ i ) {
        int a = A[i];
        int b = B[i];
        G[a].push_back(i);
        G[b].push_back(i);
      }
    }

    void generate_graph() {
      for ( int i = 0; i < n; ++ i ) {
        int num = G[i].size();
        for ( int j = 0; j + 1 < num; ++ j ) {
          U[edges_num] = G[i][j];
          V[edges_num] = G[i][j + 1];
          edges_num ++;
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
      edges_num = 0;
      for ( int i = 0; i < SIZE; ++ i ) {
        U[i] = NONE;
        V[i] = NONE;
      }
      for ( int i = 0; i < SIZE; ++ i ) {
        G[i].clear();
      }
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n - 1; ++ i )
        cin >> A[i] >> B[i];
      return true;
    }

    void output() {
      cout << n - 1 << endl;
      for ( int i = 0; i < n - 1; ++ i ) {
        cout << 2 << " " << A[i] + 1 << " " << B[i] + 1 << endl;
      }
      for ( int i = 0; i < n - 2; ++ i ) {
        cout << U[i] + 1 << " " << V[i] + 1 << endl;
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

