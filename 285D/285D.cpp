
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
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 20;
  // storages
  int n;
  LL result;
  
  II C[SIZE][SIZE];
  int CC[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( int a = 1; a <= n; ++ a ) {
        for ( int b = 1; b <= n; ++ b ) {
          int value = (a + b - 2) % n + 1;
          C[value][CC[value] ++] = II(a, b);
        }
      }
      result = rec(0, 0, 0, 0) / fact(n);
    }

    int fact( int k ) {
      int res = 1;
      for ( int i = 1; i <= k; ++ i )
        res *= i;
      return res;
    }

    int rec( int k, int asum, int bsum, int csum ) {
      if ( k >= n ) {
        return 1;
      }
      int res = 0;
      for ( int c = 0; c < n; ++ c ) {
        int bc = 1 << c;
        if ( csum & bc )
          continue;
        for ( int cc = 0; cc < CC[c + 1]; ++ cc ) {
          int a = C[c + 1][cc].first - 1;
          int ba = 1 << a;
          int b = C[c + 1][cc].second - 1;
          int bb = 1 << b;
          if ( asum & ba )
            continue;
          if ( bsum & bb )
            continue;
          res += rec(k + 1, asum | ba, bsum | bb, csum | bc);
        }
      }
      return res;
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
        CC[i] = 0;
    }
    
    bool input() {
      return cin >> n;
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


