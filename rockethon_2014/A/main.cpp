
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
  typedef std::vector <String> Tokens;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
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
    
    void solve() {
      Tokens tokens = get_tokens(in->S);
      out->result = count_even(tokens);
    }

    Int count_even( const Tokens& tokens ) {
      Int res = 0;
      for ( auto token : tokens ) {
        if ( token.size() % 2 == 0 )
          res ++;
      }
      return res;
    }

    Tokens get_tokens( const String& s ) {
      Tokens res;
      char prev = ' ';
      String tmp;
      for ( auto c : s ) {
        if ( prev != ' ' && prev != c ) {
          res.push_back(tmp);
          prev = c;
          tmp = "";
          tmp += c;
        } else {
          prev = c;
          tmp += c;
        }
      }
      if ( tmp != "" )
        res.push_back(tmp);
      return res;
    }
    
    bool input() {
      return std::cin >> in->S;
    }
    
    void output() {
      std::cout << out->result << std::endl;
    }
    
    //
    //
    //
    Solution( Input* in, Output* out ): in(in), out(out) {
      // pre calc
    }
    
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

