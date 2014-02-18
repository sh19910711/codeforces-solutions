
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
    String S;
    String P;
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
      out->result = count_good(in->S, in->P);
    }

    Int count_good( const String& s, const String& p ) {
      Int need[256] = {0};
      Int cnt[256] = {0};
      for ( auto c : p ) {
        need[c] ++;
      }
      if ( p.size() > s.size() )
        return 0;
      Int res = 0;
      Int len = p.size();
      for ( auto i = 0; i < s.size(); ++ i ) {
        const char& c = s[i];
        cnt[c] += 1;
        if ( i >= p.size() )
          cnt[s[i - p.size()]] --;
        if ( i + 1 >= p.size() ) {
          Int rem = 0;
          for ( auto i = 'a'; i <= 'z'; ++ i ) {
            rem += need[i] - std::min(need[i], cnt[i]);
          }
          if ( cnt['?'] >= rem ) {
            res ++;
          }
        }
      }
      return res;
    }
    
    bool input() {
      return std::cin >> in->S >> in->P;
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

