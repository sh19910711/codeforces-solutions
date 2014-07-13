
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
  
  typedef set<Int> IntSet;
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
    
    Int N;
    Int A[N_MAX];
    Int C1[N_MAX];
    Int S1[N_MAX];
    Int C2[N_MAX];
    Int S2[N_MAX];
    Int C3[N_MAX];
    Int S3[N_MAX];
    IntSet used;
    
    Int find_max() {
      N = in.N;
      copy(in.A, in.A + N, A);
      
      for ( Int i = 0; i < N; ++ i ) {
        C1[i] = 0;
        S1[i] = 0;
        C2[i] = 0;
        S2[i] = 0;
        C3[i] = 0;
        S3[i] = 0;
      }
      
      for ( Int i = 0; i + 1 < N; ++ i ) {
        if ( A[i] > A[i + 1] ) {
          C1[i] = 1;
        }
      }
      
      used.clear();
      for ( Int i = 0; i < N; ++ i ) {
        if ( used.count(A[i]) ) {
          C2[i] = 1;
        }
        used.insert(A[i]);
      }
      
      for ( Int i = 1; i + 1 < N; ++ i ) {
        if ( A[i + 1] - A[i - 1] <= 1 ) C3[i] = 1;
      }
  
      S1[0] = 0;
      for ( Int i = 1; i < N; ++ i ) {
        S1[i] = S1[i - 1] + C1[i - 1];
      }
  
      S2[0] = C2[0];
      for ( Int i = 1; i < N; ++ i ) {
        S2[i] = S2[i - 1] + C2[i];
      }
  
      S3[0] = C3[0];
      for ( Int i = 1; i < N; ++ i ) {
        S3[i] = S3[i - 1] + C3[i];
      }
      
      for ( Int i = 0; i < N; ++ i ) {
        for ( Int j = i; j < N; ++ j ) {
          // cout << i << ", " << j << " = " << s2(j) - s2(i) << endl;
        }
      }
      
      Int lb = -1;
      Int ub = 1000000000;
      while ( ub - lb > 1 ) {
        Int mid = ( lb + ub ) / 2;
        if ( check_cand(mid) ) {
          lb = mid;
        } else {
          ub = mid;
        }
      }
      return lb;
    }
    
    bool check_cand( const Int& len ) {
      if ( len > N ) return false;
      for ( Int i = 0; i + len - 1 < N; ++ i ) {
        if ( ok(i, i + len - 1) ) return true;
      }
      return false;
    }
    
    Int s2( const Int& x ) {
      if ( x < 0 ) return 0;
      return S2[x];
    }
    
    Int s3( const Int& x ) {
      if ( x < 0 || x >= N ) return 0;
      return S3[x];
    }
    
    bool ok( const Int& l, const Int& r ) {
      Int num1 = S1[r] - S1[l];
      Int num2 = s2(r) - s2(l);
      Int num3 = s3(r - 1) - s3(l + 1);
      if ( l + 1 > r - 1 ) num3 = 0;
      // cout << l << " - " << r << ": " << num1 << ", " << num2 << ", " << num3 << endl;
      if ( num1 == 0 ) {
        if ( num2 <= 1 && num3 == 0 ) return true;
      } else if ( num1 == 1 ) {
        if ( num2 == 0 ) return true;
      }
      return false;
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

