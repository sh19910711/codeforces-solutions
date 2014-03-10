
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
  const Int SIZE = 1000000 * 2 + 11;
  const string NONE = "-1";
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
  };
  
  struct Output {
    string res;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      return s >> in.N >> in.M;
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
    
    typedef vector<string> StringVector;

    Solution() {}

    char buf[SIZE];
    int cnt;
    
    bool solve() {
      cnt = 0;
      out.res = find();
      return true;
    }

    string get_repeat( const Int& x, const string& s ) {
      StringVector v(x, s);
      return accumulate(begin(v), end(v), string());
    }

    string find() {
      Int n = in.N;
      Int m = in.M;
      if ( n == m ) {
        for ( int i = 0; i < n; ++ i ) {
          buf[cnt ++] = '1';
          buf[cnt ++] = '0';
        }
        return buf;
      } else if ( n > m ) {
        if ( n - m == 1 ) {
          buf[cnt ++] = '0';
          for ( int i = 0; i < m; ++ i ) {
            buf[cnt ++] = '1';
            buf[cnt ++] = '0';
          }
          return buf;
        }
        return NONE;
      } else if ( n < m ) {
        while ( n >= 1 && m >= 2 && n < m ) {
          buf[cnt ++] = '1';
          buf[cnt ++] = '1';
          buf[cnt ++] = '0';
          n -= 1;
          m -= 2;
        }
        while ( n >= 1 && m >= 1 ) {
          buf[cnt ++] = '1';
          buf[cnt ++] = '0';
          n --;
          m --;
        }
        if ( n > 0 ) return NONE;
        if ( m >= 3 ) return NONE;
        while ( m > 0 ) {
          buf[cnt ++] = '1';
          m --;
        }
        return buf;
      }
      return NONE;
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

