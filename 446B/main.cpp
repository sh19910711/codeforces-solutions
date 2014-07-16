
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
/* default headers {{{ */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cmath>

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif
/* }}} */


// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  using namespace std;
  /* primitives {{{ */
  typedef long long Int;
  typedef long double Double;
  /* }}} */
  
  typedef priority_queue <Int> IntPriorityQueue;
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int SIZE = 1000 + 11;
  const Int K_MAX = 1000000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int K;
    Int P;
    Int A[SIZE][SIZE];
  };
  
  struct Output {
    Int res;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      if ( s >> in.N >> in.M >> in.K >> in.P ) {
        for ( int i = 0; i < in.N; ++ i ) {
          for ( int j = 0; j < in.M; ++ j ) {
            s >> in.A[i][j];
          }
        }
        return true;
      }
      return false;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.res << endl;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionIO {
    //
    // Implement here
    //
    
    Solution() {}
    
    bool solve() {
      out.res = find_max();
      return true;
    }
      
    Int A[K_MAX];
    Int NA;
    Int B[K_MAX];
    Int NB;
    IntPriorityQueue R;
    IntPriorityQueue C;
    
    Int find_max() {
      R = IntPriorityQueue();
      C = IntPriorityQueue();
      NA = 0;
      NB = 0;
      
      for ( Int i = 0; i < in.N; ++ i ) {
        Int sum = 0;
        for ( Int j = 0; j < in.M; ++ j ) {
          sum += in.A[i][j];
        }
        R.push(sum);
      }
      for ( Int i = 0; i < in.M; ++ i ) {
        Int sum = 0;
        for ( Int j = 0; j < in.N; ++ j ) {
          sum += in.A[j][i];
        }
        C.push(sum);
      };
      
      Int NA = 0;
      Int SA = 0;
      A[NA ++] = 0;
      for ( Int i = 0; i < in.K; ++ i ) {
        Int tmp = R.top();
        R.pop();
        SA += tmp;
        A[NA ++] = SA;
        R.push(tmp - in.M * in.P);
      }
      Int NB = 0;
      Int SB = 0;
      B[NB ++] = 0;
      for ( Int i = 0; i < in.K; ++ i ) {
        Int tmp = C.top();
        C.pop();
        SB += tmp;
        B[NB ++] = SB;
        C.push(tmp - in.N * in.P);
      }
      
      Int res = numeric_limits<Int>::min();
      for ( Int i = 0; i <= in.K; ++ i ) {
        Int na = i;
        Int nb = in.K - i;
        // cout << A[na] << " + " << B[nb] << " - " << na << " * " << nb << ", " << in.P << endl;
        res = max(res, A[na] + B[nb] - na * nb * in.P);
      }
      
      return res;
    }
    
    /* action methods {{{ */
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    bool action( const int& t_id = -1 ) {
      before_action(t_id);
      bool res = input(std::cin) && solve() && output(std::cout);
      after_action(t_id);
      return res;
    }
    /* }}} */
  };
}

// @snippet<sh19910711/contest-base-simple:solution/runner-normal.cpp>
namespace solution {
  /* Runner Class {{{ */
  struct Runner {
    static int run() {
      bool f = false;
      while ( ! f ) {
        Solution* sol = new Solution;
        f = ! sol->action();
        delete sol;
      };
      return 0;
    }
  };
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  return solution::Runner::run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

