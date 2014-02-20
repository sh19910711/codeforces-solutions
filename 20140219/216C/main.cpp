
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
  const Int SIZE = 1000000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int K;
  };
  struct Output {
    Int num;
    Int A[SIZE];
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
      Int k = in->K;
      Int n = in->N;
      Int m = in->M;

      out->num = 0;
      if ( k == 1 ) {
        if ( n == 2 && m == 2 ) {
          out->A[out->num ++] = 1;
          out->A[out->num ++] = 2;
          out->A[out->num ++] = 3;
          out->A[out->num ++] = 4;
        } else if ( n <= m + 1 ) {
          out->A[out->num ++] = 1;
          out->A[out->num ++] = n * 1;
          out->A[out->num ++] = n * 2 - 1;
        } else {
          out->A[out->num ++] = 1;
          out->A[out->num ++] = n;
        }
      } else {
        if ( n == m ) {
          for ( int i = 0; i < n + m; i += n ) {
            if ( i == 0 ) {
              out->A[out->num ++] = i + 1;
            } else {
              out->A[out->num ++] = i;
            }
            for ( int j = 0; j + 1 < k; ++ j ) {
              out->A[out->num ++] = i + 1;
            }
          }
          out->A[out->num ++] = n + m;
        } else {
          for ( int i = 0; i < n + m; i += n ) {
            if ( i == 0 ) {
              out->A[out->num ++] = i + 1;
            } else {
              out->A[out->num ++] = i;
            }
            for ( int j = 0; j + 1 < k; ++ j ) {
              out->A[out->num ++] = i + 1;
            }
          }
        }
      }
    }
    
    bool input() {
      return std::cin >> in->N >> in->M >> in->K;
    }
    
    void output() {
      std::cout << out->num << std::endl;
      for ( auto i = 0; i < out->num; ++ i ) {
        std::cout << out->A[i] << " ";
      }
      std::cout << std::endl;
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

