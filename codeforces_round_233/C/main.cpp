
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
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int A;
    Int B;
  };
  
  struct Output {
    Int N;
    string S;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      return s >> in.A >> in.B;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.N << endl << out.S << endl;
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
      out.S = get_str();
      out.N = get_score(out.S);
      return true;
    }

    Int get_score( const string& s ) {
      return get_score(s, 'o') - get_score(s, 'x');
    }

    Int get_score( const string& s, const char& c ) {
      Int res = 0;
      Int cnt = 0;
      Int n = s.size();
      for ( auto i = 0; i < n; ++ i ) {
        if ( s[i] == c ) {
          cnt ++;
        } else if ( cnt > 0 ) {
          res += pow(cnt, Int(2));
          cnt = 0;
        }
      }
      if ( cnt > 0 ) {
        res += pow(cnt, Int(2));
      }
      return res;
    }

    string get_str() {
      string res;
      if ( in.A <= in.B ) {
        Int na = in.A;
        Int nb = in.B;
        while ( na > 0 ) {
          res += "xo";
          na --;
          nb --;
        }
        while ( nb > 0 ) {
          res += "x";
          nb --;
        }
      } else {
        Int na = in.A;
        Int nb = in.B;
        res = string(na, 'o') + string(nb, 'x');
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

