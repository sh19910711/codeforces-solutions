
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
  const LL INF = std::numeric_limits<int>::max();

  // storages
  int n;
  LL h;
  LL A[SIZE];
  int R[SIZE];

  II A_sorted[SIZE];

  LL minimum_goodness;
  int B[SIZE];

}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      get_ranked();
      sort(A, A + n);
      minimum_goodness = split_sequence();
    }

    void get_ranked() {
      for ( int i = 0; i < n; ++ i )
        A_sorted[i] = II(A[i], i);
      sort(A_sorted, A_sorted + n);
      for ( int i = 0; i < n; ++ i )
        R[i] = A_sorted[i].second;
    }

    LL split_sequence() {
      LL goodness_a = f_a(n - 1, n - 2) - f_a(0, 1);
      LL goodness_b = max(f_b(n - 1, n - 2), f_b(0, n - 1)) - min(f_b(0, 1), f_b(1, 2));

      if ( goodness_a <= goodness_b ) {
        for ( int i = 0; i < n; ++ i )
          B[i] = 1;
        return goodness_a;
      }

      for ( int i = 0; i < n; ++ i )
        B[i] = 2;
      B[R[0]] = 1;
      return goodness_b;
    }

    LL f_a( int a, int b ) {
      if ( a >= n || b >= n )
        return INF;
      return A[a] + A[b];
    }

    LL f_b( int a, int b ) {
      if ( a >= n || b >= n )
        return INF;
      if ( a == 0 || b == 0 ) {
        return A[a] + A[b] + h;
      }
      return A[a] + A[b];
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
      minimum_goodness = std::numeric_limits<LL>::max();
      for ( int i = 0; i < SIZE; ++ i )
        B[i] = -1;
    }

    bool input() {
      if ( ! ( cin >> n >> h ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> A[i];
      return true;
    }

    void output() {
      cout << minimum_goodness << endl;
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

