
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
  const Int SIZE = 2 * 100000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int K;
    Int C[SIZE];
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
    
    typedef std::vector<Int> IntVector;

    Int n;
    Int m;
    Int k;
    IntVector p[SIZE];
    IntVector d[SIZE];

    void init() {
    }
    
    void solve() {
      n = in->N;
      m = in->M;
      k = in->K;
      std::fill(p, p + SIZE, IntVector());
      std::fill(d, d + SIZE, IntVector());
      out->result = count();
    }

    Int count() {
      Int res = n ? 1 : 0;
      for ( auto i = 0; i < n; ++ i ) {
        Int color = in->C[i] - 1;
        p[color].push_back(i);
      }
      for ( Int i = 0; i < m; ++ i ) {
        Int l = 0, r = 0;
        while ( r < p[i].size() ) {
          Int num = p[i][r] - p[i][l] - ( r - l );
          if ( num <= k ) {
            res = std::max(res, r - l + 1);
            r ++;
          } else {
            l ++;
          }
        }
      }
      return res;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N >> in->M >> in->K ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->C[i] ) )
          return false;
      return true;
    }
    
    void output() {
      std::cout << out->result << std::endl;
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

