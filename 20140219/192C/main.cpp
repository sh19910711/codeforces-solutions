
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
  const Int MAX_N = 5 * 100000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    String S[MAX_N];
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
    
    typedef std::array<Int, 26> IntArray;
    typedef std::array<IntArray, 26> IntMatrix;

    const Int DP_NONE = -1;
    IntMatrix dp[2];

    void init() {
    }
    
    void solve() {
      for ( auto i = 0; i < 26; ++ i ) {
        for ( auto j = 0; j < 26; ++ j ) {
          dp[0][i][j] = DP_NONE;
          dp[1][i][j] = DP_NONE;
        }
      }
      out->result = count();
    }

    Int count() {
      for ( auto i = 0; i < in->N; ++ i ) {
        Int cur = i & 1;
        Int next = cur ^ 1;
        const String& s = in->S[i];
        Int len = s.size();
        dp[next] = dp[cur];
        dp[next][s.front() - 'a'][s.back() - 'a'] = std::max(dp[next][s.front() - 'a'][s.back() - 'a'], len);
        for ( auto l = 0; l < 26; ++ l ) {
          if ( dp[cur][l][s.front() - 'a'] == DP_NONE )
            continue;
          dp[next][l][s.back() - 'a'] = std::max(dp[next][l][s.back() - 'a'], dp[cur][l][s.front() - 'a'] + len);
        }
      }
      Int res = 0;
      for ( auto i = 0; i < 26; ++ i ) {
        res = std::max(res, dp[in->N & 1][i][i]);
      }
      return res;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->S[i] ) )
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

