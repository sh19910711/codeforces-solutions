
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
  const int NONE = -1;
  // storages
  int n, m;
  int U[SIZE];
  int V[SIZE];
  int A[SIZE];
  
  int B[SIZE];
  bool ok[SIZE];
  VI G[SIZE];

  int operations;
  int push_index[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      fill(B, B + n, 0);
      for ( int i = 0; i < n; ++ i )
        ok[i] = A[i] != B[i];
      operations = get_operations();
    }

    void normalize() {
      for ( int i = 0; i < m; ++ i ) {
        U[i] --;
        V[i] --;
      }
      for ( int i = 0; i < m; ++ i ) {
        int u = U[i];
        int v = V[i];
        G[u].push_back(v);
        G[v].push_back(u);
      }
      for ( int i = 0; i < n; ++ i )
        sort(G[i].begin(), G[i].end());
    }

    int get_operations() {
      int res = 0;

      for ( int t = 0; t < 3 && res < n; ++ t ) {
        int left_most = 0;

        while ( left_most < n && ok[left_most] )
          left_most ++;

        while ( res < n && left_most < n ) {
          while ( left_most < n && ok[left_most] ) {
            left_most ++;
          }
          if ( left_most < n ) {
            int next_left_most = left_most + 1;
            push_index[res ++] = left_most;
            B[left_most] ++;
            ok[left_most] = B[left_most] != A[left_most];
            for ( int j = 0; j < (int)G[left_most].size(); ++ j ) {
              int v = G[left_most][j];
              B[v] ++;
              ok[v] = B[v] != A[v];
              if ( ! ok[v] )
                next_left_most = min(next_left_most, v);
            }
            left_most = next_left_most;
          }
        }
      }

      return std::count(ok, ok + n, false) > 0 ? NONE : res;
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
        G[i].clear();
    }

    bool input() {
      if ( ! ( cin >> n >> m ) )
        return false;
      for ( int i = 0; i < m; ++ i )
        cin >> U[i] >> V[i];
      for ( int i = 0; i < n; ++ i )
        cin >> A[i];
      return true;
    }

    void output() {
      if ( operations == NONE ) {
        cout << -1 << endl;
      } else {
        cout << operations << endl;
        for ( int i = 0; i < operations; ++ i )
          cout << push_index[i] + 1 << " ";
        cout << endl;
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

