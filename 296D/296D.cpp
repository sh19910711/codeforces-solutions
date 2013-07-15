
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
  const LL INF = std::numeric_limits<LL>::max();
  // storages
  int n;
  LL A[SIZE][SIZE];
  int X[SIZE];

  LL C[SIZE][SIZE];
  LL min_dist[SIZE][SIZE];

  LL B[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      calc_sum();
    }

    void calc_sum() {
      for ( int i = 0; i < n; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          min_dist[i][j] = A[i][j];
        }
      }

      for ( int xi = 0; xi < n; ++ xi ) {
        int num_vertices = xi + 1;
        for ( int i = 0; i < n; ++ i ) {
          for ( int j = 0; j < n; ++ j ) {
            min_dist[i][j] = min(min_dist[i][j], min_dist[i][X[xi]] + min_dist[X[xi]][j]);
          }
        }
        LL sum = 0;
        for ( int i = 0; i < num_vertices; ++ i )
          for ( int j = 0; j < num_vertices; ++ j )
            sum += min_dist[X[i]][X[j]];
        B[xi] = sum;
      }

      reverse(B, B + n);
    }

    void normalize() {
      for ( int i = 0; i < n; ++ i )
        X[i] --;
      reverse(X, X + n);
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
      fill(B, B + n, 0);
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        for ( int j = 0; j < n; ++ j )
          cin >> A[i][j];
      for ( int i = 0; i < n; ++ i )
        cin >> X[i];
      return true;
    }

    void output() {
      for ( int i = 0; i < n; ++ i )
        cout << B[i] << " ";
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

