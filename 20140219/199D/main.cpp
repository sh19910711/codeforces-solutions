
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
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

// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  typedef int Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int SIZE = 10 * 100000 + 11;
  const String YES = "YES";
  const String NO = "NO";
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int K;
    String S[2];
  };
  struct Output {
    bool result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    Int N;
    Int K;
    String S[2];
    Int used[2][SIZE];

    void init() {
    }
    
    void solve() {
      N = in->N;
      K = in->K;
      for ( auto i = 0; i < 2; ++ i ) {
        S[i] = in->S[i];
        std::fill(used[i], used[i] + SIZE, std::numeric_limits<Int>::max());
      }
      out->result = rec(0, 0, 0);
    }

    bool rec( const Int& x, const Int& y, const Int& t ) {
      if ( x >= N )
        return true;
      
      if ( t >= used[y][x] )
        return false;
      used[y][x] = t;

      if ( x + K >= N ) {
        if ( rec( x + K, y ^ 1, t + 1 ) )
          return true;
      } else {
        if ( S[y ^ 1][x + K] == '-' && rec( x + K, y ^ 1, t + 1 ) )
          return true;
      }
      if ( x + 1 >= N ) {
        if ( rec( x + 1, y, t + 1 ) )
          return true;
      } else {
        if ( S[y][x + 1] == '-' && rec( x + 1, y, t + 1 ) )
          return true;
      }
      if ( x - 1 > t && x - 1 >= 0 ) {
        if ( S[y][x - 1] == '-' && rec( x - 1, y, t + 1 ) )
          return true;
      }
      return false;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N >> in->K ) )
        return false;
      for ( auto i = 0; i < 2; ++ i )
        if ( ! ( std::cin >> in->S[i] ) )
          return false;
      return true;
    }
    
    void output() {
      std::cout << ( out->result ? YES : NO ) << std::endl;
    }
    
    //
    //
    //
    Solution( Input* in, Output* out ): in(in), out(out) { this->init(); }
    
    int run() {
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
    
    bool action() {
      if ( ! this->input() ) return false;
      this->solve();
      this->output();
      return true;
    }
    
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using namespace solution;
  static Input in;
  static Output out;
  static Solution sol(&in, &out);
  return sol.run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

