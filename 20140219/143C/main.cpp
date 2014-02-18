
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
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
  };
  struct Output {
    Int min_s;
    Int max_s;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    void init() {
    }
    
    void solve() {
      out->min_s = std::numeric_limits<Int>::max();
      out->max_s = std::numeric_limits<Int>::min();
      for ( Int i = 1; i * i * i <= in->N; ++ i ) {
        if ( in->N % i ) continue;
        for ( Int j = i; j * j <= in->N / i; ++ j ) {
          if ( ( in->N / i ) % j ) continue;
          Int k = in->N / i / j;
          {
            Int NS = ( k + 1 ) * ( i + 2 ) * ( j + 2 );
            out->min_s = std::min(out->min_s, NS - in->N);
            out->max_s = std::max(out->max_s, NS - in->N);
          }
          {
            Int NS = ( j + 1 ) * ( i + 2 ) * ( k + 2 );
            out->min_s = std::min(out->min_s, NS - in->N);
            out->max_s = std::max(out->max_s, NS - in->N);
          }
          {
            Int NS = ( i + 1 ) * ( j + 2 ) * ( k + 2 );
            out->min_s = std::min(out->min_s, NS - in->N);
            out->max_s = std::max(out->max_s, NS - in->N);
          }
        }
      }
    }
    
    bool input() {
      return std::cin >> in->N;
    }
    
    void output() {
      std::cout << out->min_s << " " << out->max_s << std::endl;
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

