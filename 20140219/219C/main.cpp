
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
  const Int SIZE = 5 * 100000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int K;
    String S;
  };
  struct Output {
    Int N;
    String S;
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
    String S;

    void init() {
    }
    
    void solve() {
      N = in->N;
      S = in->S;
      K = in->K;
      if ( K == 2 ) {
        String T(SIZE, 'A');
        for ( auto i = 1; i < SIZE; i += 2 ) T[i] = 'B';
        Int n1 = count(S, T.substr(0, N));
        Int n2 = count(S, T.substr(1, N));
        if ( n1 < n2 ) {
          out->N = n1;
          out->S = T.substr(0, N);
        } else {
          out->N = n2;
          out->S = T.substr(1, N);
        }
      } else {
        out->N = 0;
        for ( auto i = 1; i < N; ++ i ) {
          if ( S[i] == S[i - 1] ) {
            change(i);
            out->N ++;
          }
        }
        out->S = S;
      }
    }

    void change( const Int& k ) {
      for ( auto i = 0; i < K; ++ i ) {
        char c = 'A' + i;
        if ( k > 0 && S[k - 1] == c )
          continue;
        if ( k + 1 < N && S[k + 1] == c )
          continue;
        S[k] = c;
        return;
      }
    }
    
    Int count( const String& a, const String& b ) {
      Int res = 0;
      for ( auto i = 0; i < N; ++ i ) {
        if ( a[i] != b[i] ) res ++;
      }
      return res;
    }
    
    bool input() {
      return std::cin >> in->N >> in->K >> in->S;
    }
    
    void output() {
      std::cout << out->N << std::endl;
      std::cout << out->S << std::endl;
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

