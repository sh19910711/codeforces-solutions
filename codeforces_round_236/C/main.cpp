
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
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int SIZE = 24 * 24;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int P;
  };
  
  struct Output {
    Int N;
    Int A[SIZE];
    Int B[SIZE];
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      return s >> in.N >> in.P;
    }
    
    template <class Stream> bool output( Stream& s ) {
      for ( int i = 0; i < out.N; ++ i ) s << out.A[i] + 1 << " " << out.B[i] + 1 << endl;
      return s;
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

    Int n;
    Int A[SIZE];
    Int B[SIZE];

    bool solve() {
      find();
      out.N = n;
      copy(A, A + n, out.A);
      copy(B, B + n, out.B);
      return true;
    }

    void find() {
      n = 0;
      for ( int i = 0; i < in.N; ++ i ) {
        for ( int j = i + 1; j < in.N; ++ j ) {
          A[n] = i;
          B[n] = j;
          n ++;
          if ( n >= 2 * in.N + in.P ) return;
        }
      }
      return;
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

// @snippet<sh19910711/contest-base-simple:solution/runner-multi-test.cpp>
namespace solution {
  /* Runner Class {{{ */
  struct Runner {
    static int run() {
      int tests;
      std::cin >> tests;
      for ( int i = 0; i < tests; ++ i ) {
        Solution* sol = new Solution;
        sol->action(i);
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


