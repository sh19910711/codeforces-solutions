
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
  const Int SIZE = 100000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int A;
    Int D;
    Int T[SIZE];
    Int V[SIZE];
  };
  struct Output {
    Int N;
    Double result[SIZE];
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    Double sqv[SIZE];
    Double sqt;

    void init() {
    }
    
    void solve() {
      sqt = std::sqrt( 2.0 * in->D / in->A );
      Double t0 = -1.0;
      out->N = in->N;
      for ( auto i = 0; i < in->N; ++ i ) {
        Double t = in->T[i] + get_time(in->A, in->D, in->V[i]);
        t0 = std::max(t0, t);
        out->result[i] = t0;
      }
    }

    Double sq( Double x ) {
      return x * x;
    }

    Double get_time( const Double& A, const Double& D, const Double& V ) {
      Double d1 = 0.5 * sq(V) / A;
      if ( D > d1 )
        return V / A + ( D - d1 ) / V;
      return sqt;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N >> in->A >> in->D ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->T[i] >> in->V[i] ) )
          return false;
      return true;
    }
    
    void output() {
      for ( auto i = 0; i < out->N; ++ i )
        std::cout << std::setprecision(12) << out->result[i] << std::endl;
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

