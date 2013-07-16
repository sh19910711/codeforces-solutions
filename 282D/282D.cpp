
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
  const int NUM       = 4;
  const int SIZE      = 300 + 11;
  const string YES    = "BitLGM";
  const string NO     = "BitAryo";
  const int MEMO_NONE = -1;
  const int TYPE_WIN  = 0;
  const int TYPE_LOSE = 1;
  // storages
  int n;
  int A[NUM];
  bool result;
  int memo[SIZE][SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = false;
      if ( n == 1 || n == 3 ) {
        int xorsum = 0;
        for ( int i = 0; i < n; ++ i )
          xorsum ^= A[i];
        if ( xorsum )
          result = true;
      } else {
        result = check2();
      }
    }

    bool check2() {
      return rec(A[0], A[1]);
    }

    bool rec( int a, int b ) {
      if ( a == 0 && b == 0 )
        return false;
      if ( a == b )
        return true;

      if ( memo[a][b] != MEMO_NONE ) {
        return ( memo[a][b] == TYPE_WIN ? true : false );
      }

      bool res = false;

      for ( int i = 1; i <= a; ++ i ) {
        res |= true ^ rec(a - i, b);
      }
      for ( int i = 1; i <= b; ++ i ) {
        res |= true ^ rec(a, b - i);
      }
      for ( int i = 1; i <= min(a, b); ++ i ) {
        res |= true ^ rec(a - i, b - i);
      }

      memo[a][b] = ( res ? TYPE_WIN : TYPE_LOSE );
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
        for ( int j = 0; j < SIZE; ++ j )
          memo[i][j] = MEMO_NONE;
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> A[i];
      return true;
    }

    void output() {
      cout << ( result ? YES : NO ) << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

