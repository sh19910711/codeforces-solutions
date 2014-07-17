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
  const Int SIZE = 100 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    string A[SIZE];
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
    
    typedef set<int> IntSet;
    
    Int C[SIZE];
    Int NC;
    Int M[SIZE];
    
    Solution() {}
    
    Int get_card(string s) {
      return get_bit(s[0]) | get_bit(s[1]);
    }
    
    Int get_bit(const char& c) {
      Int res = 0;
      string a = "RGBYW";
      string b = "12345";
      for ( Int i = 0; i < 5; ++ i ) {
        if ( a[i] == c) {
          return Int(1) << i;
        }
      }
      for ( Int i = 0; i < 5; ++ i ) {
        if (b[i] == c){
          return (Int(1) << i) << 5;
        }
      }
      return -1;
    }
    
    bool solve() {
      out.res = find_min();
      return true;
    }
    
    void set_match( const Int& b ) {
      for ( Int i = 0; i < NC; ++ i ) {
        if (C[i] & b) M[i] |= b;
      }
    }
    
    bool check( Int s1, Int s2 ) {
      for ( Int i = 0; i < 5; ++ i ) {
        Int bi = Int(1) << i;
        if ( s1 & bi ) set_match(bi);
      }
      for ( Int i = 0; i < 5; ++ i ) {
        Int bi = Int(1) << i;
        bi <<= Int(5);
        if ( s2 & bi ) set_match(bi);
      }
      return is_ok();
    }
    
    bool is_ok() {
      IntSet matches;
      for ( Int i = 0; i < NC; ++ i ) {
        matches.insert(M[i]);
      }
      return matches.size() == NC;
    }
    
    Int find_min() {
      NC = 0;
      
      IntSet S;
      for ( int i = 0; i < in.N; ++ i ) {
        S.insert(get_card(in.A[i]));
      }
      
      
      for ( auto& c : S ) {
        C[NC ++] = c;
      }
  
      Int res = numeric_limits<Int>::max();
      for ( Int i = 0; i < Int(1) << Int(5); ++ i ) {
        for ( Int j = 0; j < Int(1) << Int(5); ++ j ) {
          for ( Int k = 0; k < SIZE; ++ k ) M[k] = 0;
          if ( check(i, j << Int(5)) ) {
            res = min(res, (Int)__builtin_popcountll(i) + __builtin_popcountll(j));
          }
        }
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

