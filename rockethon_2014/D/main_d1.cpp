
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
  const Int SIZE = 1000 + 11;
  typedef std::array<Int, SIZE> IntArray;
  typedef std::array<IntArray, 2> IntMatrix;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    IntMatrix X;
    IntMatrix Y;
    IntMatrix L;
  };
  struct Output {
    Int result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    void solve() {
      out->result = find_max();
    }

    bool check_cross( const Int& l, const Int& r, const Int& x ) {
      return l <= x && x <= r;
    }

    Int find_max() {
      Int res = 0;
      for ( auto i = 0; i < in->N; ++ i ) {
        for ( auto j = 0; j < in->M; ++ j ) {
          if ( check_cross(in->X[1][j], in->X[1][j] + in->L[1][j], in->X[0][i] ) ) {
            if ( check_cross(in->Y[0][i], in->Y[0][i] + in->L[0][i], in->Y[1][j]) ) {
              Int min_x = std::min(std::abs(in->X[1][j] - in->X[0][i]), std::abs(in->X[1][j] + in->L[1][j] - in->X[0][i]));
              Int min_y = std::min(std::abs(in->Y[0][i] - in->Y[1][j]), std::abs(in->Y[0][i] + in->L[0][i] - in->Y[1][j]));
              Int len = std::min(min_x, min_y);
              res = std::max(res, len);
            }
          }
        }
      }
      return res;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N >> in->M ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->X[0][i] >> in->Y[0][i] >> in->L[0][i] ) )
          return false;
      for ( auto i = 0; i < in->M; ++ i ) {
        if ( ! ( std::cin >> in->X[1][i] >> in->Y[1][i] >> in->L[1][i] ) )
          return false;
      }
      return true;
    }
    
    void output() {
      std::cout << out->result << std::endl;
    }
    
    //
    //
    //
    Solution( Input* in, Output* out ): in(in), out(out) {
      // pre calc
    }
    
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

