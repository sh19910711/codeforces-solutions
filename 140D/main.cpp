
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
  const int SIZE = 100 + 11;
  // storages
  int n;
  int A[SIZE];

  int problems;
  int penalty;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      std::sort(A, A + n);
      problems = calc_problems();
      penalty = calc_penalty();
    }

    int calc_penalty() {
      int res = 0;
      int sum = 0;
      int id = 0;
      while ( id < n && sum + A[id] <= 360 - 10 ) {
        sum += A[id ++];
      }
      while ( id < n && sum + A[id] <= 720 - 10 ) {
        sum += A[id ++];
        res += ( sum - ( 360 - 10 ) );
      }
      return res;
    }

    int calc_problems() {
      int sum = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( A[i] + sum > 720 - 10 )
          return i;
        sum += A[i];
      }
      return n;
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
      for ( int i = 0; i < n; ++ i ) {
        cin >> A[i];
      }
      return true;
    }

    void output() {
      cout << problems << " " << penalty << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

