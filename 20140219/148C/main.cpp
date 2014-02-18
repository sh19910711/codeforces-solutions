
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
  const Int SIZE = 100 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int A;
    Int B;
  };
  struct Output {
    Int N;
    bool ok;
    Int result[SIZE];
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
      out->N = in->N;
      // out->ok = make();
      out->ok = make2();
    }

    bool make2() {
      Int sum = 0;
      Int cur = 0;
      out->result[cur ++] = 1;
      sum += 1;
      if ( in->B ) {
        for ( auto i = 0; i < in->B; ++ i ) {
          out->result[cur ++] = sum + 1;
          if ( cur > in->N )
            return false;
          if ( sum + 1 > 50000 )
            return false;
          if ( i + 1 < in->B )
            sum += sum + 1;
        }
        sum += 1;
      } else {
        out->result[cur ++] = 1;
      }
      for ( auto i = 0; i < in->A; ++ i ) {
        out->result[cur ++] = sum + 1;
        if ( cur > in->N )
          return false;
        if ( sum + 1 > 50000 )
          return false;
        sum += 1;
      }
      while ( cur < in->N )
        out->result[cur ++] = 1;
      return true;
    }

    bool make() {
      Int sum = 0;
      Int cur = 0;
      out->result[cur ++] = 1;
      sum += 1;
      if ( in->A > 0 ) {
        out->result[cur ++] = 1;
        sum += 1;
        Int tmp = 2;
        for ( auto i = 0; i < in->A; ++ i ) {
          out->result[cur ++] = tmp;
          sum += tmp;
          tmp += 1;
        }
      }
      if ( in->B > 0 ) {
        Int tmp = sum + 1;
        for ( auto i = 0; i < in->B; ++ i ) {
          out->result[cur ++] = tmp;
          if ( tmp > 50000 )
            return false;
          sum += tmp;
          tmp = sum + 1;
        }
      }
      while ( cur < in->N )
        out->result[cur ++] = 1;
      return true;
    }
    
    bool input() {
      return std::cin >> in->N >> in->A >> in->B;
    }
    
    void output() {
      if ( out->ok ) {
        for ( auto i = 0; i < out->N; ++ i ) {
          std::cout << out->result[i] << " ";
        }
        std::cout << std::endl;
      } else {
        std::cout << -1 << std::endl;
      }
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

