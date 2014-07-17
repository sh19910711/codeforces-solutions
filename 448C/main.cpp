
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
  const Int N_MAX = 5000 + 11;
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
    
    Int L[N_MAX][N_MAX];
    Int LC[N_MAX];
    Int R[N_MAX][N_MAX];
    Int RC[N_MAX];
    Int groups_limit;
    
    bool solve() {
      out.res = find_min();
      return true;
    }
    
    Int find_min() {
      fill(LC, LC + N_MAX, Int(0));
      fill(RC, RC + N_MAX, Int(0));
      // groups_limit = min(in.N, *max_element(in.A, in.A + in.N));
      groups_limit = in.N + 1;
      
      const Int NONE = -1;
      for ( Int i = 1; i <= groups_limit; ++ i ) {
        Int l = NONE;
        Int r = NONE;
        for ( Int j = 0; j < in.N; ++ j ) {
          if (i <= in.A[j]) {
            if ( l == NONE ) {
              l = r = j;
            } else {
              r = j;
            }
          } else {
            if ( r != NONE ) {
              L[i][LC[i] ++] = l;
              R[i][RC[i] ++] = r;
              l = NONE;
              r = NONE;
            }
          }
        }
        if (r != NONE) {
          L[i][LC[i] ++] = l;
          R[i][RC[i] ++] = r;
        }
        // cout << "groups: " << i << ": " << groups[i] << endl;
      }
      
      Int res = numeric_limits<Int>::max();
      for ( Int i = 0; i < groups_limit; ++ i ) {
        // cout << "res: " << i << ": " << get_count(i) << endl;
        res = min(res, get_count(i));
      }
      return res;
    }
    
    Int get_count(const Int& x) {
      if (x == 0) return in.N;
      Int res = 0;
      for ( Int i = 0; i <= x; ++ i ) { res += LC[i]; }
      bool used[N_MAX];
      fill(used, used + N_MAX, false);
      for ( Int i = 0; i < LC[x + 1]; ++ i ) {
        int l = L[x+1][i];
        int r = R[x+1][i];
        int d = *max_element(in.A + l, in.A + r) - x;
        if (r - l > d) {
          res += d;
          for ( int j = l; j <= r; ++ j ) {
            if (x + 1 >= in.A[j]) used[j] = true;
          }
        }
      }
      for ( Int i = 0; i < in.N; ++ i ) {
        if ( used[i] ) continue;
        if ( x < in.A[i] ) res ++;
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

