
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
    Int K[SIZE];
    Int C[SIZE];
    Int T;
    Int P[SIZE];
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
    typedef std::pair <Int, Int> IntPair;
 
    // cost, num
    
    void init() {
    }
    
    void solve() {
      out->result = find_max();
    }

    Int find_max() {
      Int n = in->N;
      Int t = in->T;
      IntPair f[SIZE];
      for ( auto i = 0; i < n; ++ i ) {
        f[i] = std::make_pair(in->C[i], in->K[i]);
      }
      std::sort(f, f + n);

      Int p[SIZE];
      std::copy(in->P, in->P + SIZE, p);
      for ( auto i = t - 1; i >= 1; -- i ) {
        p[i] -= p[i - 1];
      }

      Int res = 0;
      Int fac = 1;
      for ( auto i = 0, j = 0; i < n; ) {
        if ( j >= t ) {
          res += fac * f[i].first * f[i].second;
          i ++;
          continue;
        }
        if ( f[i].second > p[j] ) {
          res += fac * f[i].first * p[j];
          f[i].second -= p[j];
          fac ++;
          j ++;
        } else {
          res += fac * f[i].first * f[i].second;
          p[j] -= f[i].second;
          i ++;
        }
      }
      return res;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->K[i] >> in->C[i] ) )
          return false;
      if ( ! ( std::cin >> in->T ) )
        return false;
      for ( auto i = 0; i < in->T; ++ i )
        if ( ! ( std::cin >> in->P[i] ) )
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

