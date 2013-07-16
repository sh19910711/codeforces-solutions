
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
  const int SIZE = 24;
  const int BIT_SIZE = 1 << SIZE;
  const int NONE = std::numeric_limits<int>::max();
  const int MEMO_NONE = std::numeric_limits<int>::min();
  
  // storages
  int n;
  int A[SIZE];
  
  int all;
  
  int result;
  int memo[BIT_SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      all = ( 1 << n ) - 1;
      result = rec(1 << ( n - 1 ));
    }
    
    int rec( int state ) {
      int& res = memo[state];
      if ( res != MEMO_NONE )
        return res;

      if ( state == 1 )
        return res = 1;
      
      res = NONE;
      for ( int target = n - 1; target >= 1; -- target ) {
        int bt = 1 << target;
        if ( ! ( state & bt ) )
          continue;

        int ret = distribute(state, target);
        res = min(res, ret);
        break;
      }
      return res;
    }

    int distribute( int state, int target ) {
      int res = NONE;
      int state_num = __builtin_popcount(state);
      int value = A[target];
      int bt = 1 << target;
      if ( state & bt ) {
        for ( int i = 0; i < target; ++ i ) {
          for ( int j = i; j < target; ++ j ) {
            int a = A[i];
            int b = A[j];
            int bi = 1 << i;
            int bj = 1 << j;
            if ( a + b == value ) {
              int next_target = target - 1;
              int bnt = 1 << next_target;

              int next_state = state;
              next_state ^= bt;
              next_state |= bnt;
              next_state |= bi;
              next_state |= bj;

              int ret = rec(next_state);
              res = min(res, max(ret, state_num));
            }
          }
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
      for ( int i = 0; i < BIT_SIZE; ++ i )
        memo[i] = MEMO_NONE;
    }
    
    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> A[i];
      return true;
    }
    
    void output() {
      if ( result == NONE ) {
        cout << -1 << endl;
      } else {
        cout << result << endl; 
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


