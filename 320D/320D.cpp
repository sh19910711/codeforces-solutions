
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
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  // storages
  int n;
  int A[SIZE];
  int B[2][SIZE];
  int BC;
  int bcur;
  int C[2][SIZE];
  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_times();
    }

    void print_bc( int cur ) {
      cout << "B: " << endl;
      for ( int i = 0; i < BC; ++ i ) {
        cout << i << ": " << B[cur][i] << endl;
      }
      cout << "C: " << endl;
      for ( int i = 0; i < BC; ++ i ) {
        cout << i << ": " << C[cur][i] << endl;
      }
    }

    int get_times() {
      if ( n == 1 )
        return 0;

      int tmp = 0;
      int prev = 0;
      BC = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( i + 1 < n && A[i] < A[i + 1] ) {
          C[0][BC] = tmp + 1;
          B[0][BC] = A[prev];
          prev = i + 1;
          tmp = 0;
          BC ++;
        } else {
          tmp ++;
        }
      }
      if ( tmp > 0 ) {
        C[0][BC] = tmp;
        B[0][BC] = A[prev];
        BC ++;
      }

      if ( BC == 0 )
        return 0;

      if ( BC == 1 )
        return 0;

      for ( int t = 0; t < n; ++ t ) {
        int cur = ( t & 1 );
        int next = ( cur ^ 1 ) & 1;
        
        if ( BC == 1 )
          return t * ( C[cur][0] - 1);

        int m = BC;
        BC = 0;

        int tmp = 0;
        int prev = 0;
        BC = 0;
        for ( int i = 0; i < m; ++ i ) {
          if ( i + 1 < m && A[i] < A[i + 1] ) {
            C[next][BC] = tmp + 1;
            B[next][BC] = B[cur][prev];
            prev = i + 1;
            tmp = 0;
            BC ++;
          } else {
            tmp ++;
          }
        }
        if ( tmp > 0 ) {
          C[next][BC] = tmp;
          B[next][BC] = B[cur][prev];
          BC ++;
        }

      }

      return -1;
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

