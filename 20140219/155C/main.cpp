
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
    String S;
    Int K;
    String F[13];
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
    
    const Int MEMO_NONE = -1;
    Int N;
    Int memo[256][SIZE];

    void init() {
    }
    
    void solve() {
      for ( auto i = 0; i < 256; ++ i ) {
        for ( auto j = 0; j < SIZE; ++ j ) {
          memo[i][j] = MEMO_NONE;
        }
      }
      N = in->S.size();
      out->result = count();
    }

    bool is_forbidden( const char& a, const char& b ) {
      for ( auto i = 0; i < in->K; ++ i ) {
        const char e = std::min(in->F[i][0], in->F[i][1]);
        const char f = std::max(in->F[i][0], in->F[i][1]);
        const char c = std::min(a, b);
        const char d = std::max(a, b);
        if ( e == c && f == d )
          return true;
      }
      return false;
    }

    Int count() {
      return N - rec('#', 0);
    }

    Int rec( const char& prev, const Int& pos ) {
      if ( pos >= N )
        return 0;
      Int& res = memo[prev][pos];
      if ( res != MEMO_NONE )
        return res;
      res = 0;
      if ( ! is_forbidden(prev, in->S[pos]) )
        res = std::max(res, rec(in->S[pos], pos + 1) + 1);
      return res = std::max(res, rec(prev, pos + 1));
    }

    Int count2() {
      const Int SIZE = 100000 + 11;
      const Int INF = std::numeric_limits<Int>::max();
      Int dp[SIZE][2];
      for ( auto i = 0; i < SIZE; ++ i ) {
        for ( auto j = 0; j < 2; ++ j ) {
          dp[i][j] = INF;
        }
      }
      dp[0][0] = 0;
      for ( auto i = 1; i < in->S.size(); ++ i ) {
        for ( auto j = 0; j < 2; ++ j ) {
          const Int cur = dp[i - 1][j];
          if ( cur == INF )
            continue;
          if ( j == 0 ) {
            dp[i][1] = std::min(dp[i][1], cur + 1);
            if ( ! is_forbidden(in->S[i - 1], in->S[i]) ) {
              dp[i][0] = std::min(dp[i][0], cur);
            }
          } else if ( j == 1 ) {
            dp[i][0] = std::min(dp[i][0], cur);
            dp[i][1] = std::min(dp[i][1], cur + 1);
          }
        }
      }
      return dp[in->S.size() - 1][0];
    }
    
    bool input() {
      if ( ! ( std::cin >> in->S ) )
        return false;
      if ( ! ( std::cin >> in->K ) )
        return false;
      for ( auto i = 0; i < in->K; ++ i )
        if ( ! ( std::cin >> in->F[i] ) )
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

