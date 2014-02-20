
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
  const Int SIZE = 100000 + 11;
  const String YES = "YES";
  const String NO = "NO";
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int A[SIZE];
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
    
    void init() {
    }
    
    void solve() {
      out->result = check();
    }

    bool check() {
      Int sorted[SIZE];
      Int sorted_sum = 0;
      std::copy(in->A, in->A + in->N, sorted);
      std::sort(sorted, sorted + in->N);
      for ( auto i = 0; i < in->N; ++ i ) {
        sorted_sum += ( i + 1 ) * sorted[i];
      }
      Int sum = 0;
      for ( auto i = 0; i < in->N; ++ i ) {
        sum += ( i + 1 ) * in->A[i];
      }
      if ( sum == sorted_sum )
        return true;
      std::stack <Int> s;
      for ( auto i = 0; i < in->N; ++ i ) {
        if ( sorted[i] != in->A[i] ) {
          s.push(i);
        }
      }
      if ( s.size() != 2 )
        return false;
      Int l = s.top(); s.pop();
      Int r = s.top(); s.pop();
      sum -= ( l + 1 ) * in->A[l];
      sum -= ( r + 1 ) * in->A[r];
      sum += ( r + 1 ) * in->A[l];
      sum += ( l + 1 ) * in->A[r];
      return sum == sorted_sum;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->A[i] ) )
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

