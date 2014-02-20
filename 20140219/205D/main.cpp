
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
    Int X[SIZE];
    Int Y[SIZE];
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
    
    typedef std::map<Int, Int> IntMap;
    
    IntMap cnt;

    void init() {
    }
    
    void solve() {
      cnt.clear();
      for ( auto i = 0; i < in->N; ++ i ) {
        cnt[in->X[i]] ++;
        cnt[in->Y[i]] ++;
      }
      out->result = count();
    }

    Int count() {
      const Int INF = std::numeric_limits<Int>::max();
      Int res = INF;
      for ( auto p : cnt ) {
        Int lim = ( 2 * ( in->N + 1 ) / 2 / 2 );
        if ( p.second >= lim ) {
          Int tmp = 0;
          Int all = 0;
          for ( auto i = 0; i < in->N; ++ i ) {
            if ( in->X[i] == p.first ) all ++;
          }
          for ( auto i = 0; i < in->N; ++ i ) {
            if ( in->X[i] != p.first && all < lim && in->Y[i] == p.first ) {
              tmp ++;
              all ++;
            }
          }
          if ( all >= lim ) {
            res = std::min(res, tmp);
          }
        }
      }
      return res == INF ? -1 : res;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->X[i] >> in->Y[i] ) )
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

