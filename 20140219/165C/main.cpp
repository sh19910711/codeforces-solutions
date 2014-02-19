
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
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int K;
    String S;
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
    
    void init() {
    }
    
    void solve() {
      out->result = count(in->S);
    }

    Int count( const String& s ) {
      Int dp[s.size() + 11];
      std::fill(dp, dp + s.size() + 11, 0);
      dp[0] = 1;
      Int res = 0;
      Int sum = 0;
      for ( auto i = 0; i < s.size(); ++ i ) {
        if ( s[i] == '1' )
          sum ++;
        if ( sum >= in->K )
          res += dp[sum - in->K];
        dp[sum] += 1;
      }
      return res;
    }

    Int count2( const String& s ) {
      Int res = 0;
      Int n = s.size();
      Int l, r;
      Int cnt = 0;
      for ( l = 0, r = 0; l < n; ++ l ) {
        r = std::max(l + 1, r);
        if ( s[l] == '1' )
          cnt ++;
        for ( ; r < n && cnt != in->K; ++ r ) {
          if ( s[r] == '1')
            cnt ++;
        }
        if ( cnt != in->K ) break;
        res ++;
        Int tr = r;
        while ( s[tr] == '0' && tr < n ) {
          res ++;
          tr ++;
        }
        if ( s[l] == '1' )
          cnt --;
      }
      return res;
    }
    
    bool input() {
      return std::cin >> in->K >> in->S;
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

