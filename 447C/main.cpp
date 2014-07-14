
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
  const Int N_MAX = 100000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int A[N_MAX];
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
      if ( s >> in.N ) {
        for ( int i = 0; i < in.N; ++ i ) {
          s >> in.A[i];
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

    Int L[N_MAX];
    Int LS[N_MAX];
    Int R[N_MAX];
    Int RS[N_MAX];

    Int find_max() {
      Int N = in.N;
      for ( Int i = 0; i < N; ++ i ) {
        L[i] = 0;
        LS[i] = 0;
        R[i] = 0;
        RS[i] = 0;
      }
      L[0] = 1;
      for ( Int i = 1; i < N; ++ i ) {
        if ( in.A[i - 1] < in.A[i] ) {
          L[i] = L[i - 1] + 1;
        } else {
          L[i] = 1;
        }
      }
      R[N - 1] = 1;
      for ( Int i = N - 1 - 1; i >= 0; -- i ) {
        if ( in.A[i] < in.A[i + 1] ) {
          R[i] = R[i + 1] + 1;
        } else {
          R[i] = 1;
        }
      }
      Int res = 0;
      res = min(Int(2), N);
      for ( Int i = 0; i + 1 < N; ++ i ) {
        if ( in.A[i] < in.A[i + 1] ) {
          res = max(res, L[i] + R[i + 1] + 1);
        }
      }
      for ( Int i = 0; i < N; ++ i ) {
        if ( i - 1 >= 0 && i + 1 < N && in.A[i - 1] + 1 < in.A[i + 1] ) {
          res = max(res, L[i - 1] + R[i + 1] + 1);
        }
      }
      res = min(res, N);
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

