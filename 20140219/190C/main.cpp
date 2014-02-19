
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
  const Int SIZE = 3 * 1000000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int tokens;
    bool token[SIZE]; // true = pair, false = int
  };
  struct Output {
    bool ok;
    String result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    Int n;
    Int k;
    Int buf_cur;
    char buf[SIZE];

    void init() {
    }
    
    void solve() {
      n = in->tokens;
      k = 0;
      buf_cur = 0;
      std::fill(buf, buf + SIZE, '\0');
      out->ok = rec() && k == in->tokens;
      out->result = buf;
    }

    bool rec( const bool& prev = false ) {
      if ( k >= n )
        return false;
      bool t = in->token[k ++];
      if ( t ) {
        buf[buf_cur ++] = 'p';
        buf[buf_cur ++] = 'a';
        buf[buf_cur ++] = 'i';
        buf[buf_cur ++] = 'r';
        buf[buf_cur ++] = '<';
        bool ret1 = rec(true);
        if ( ! ret1 )
          return false;
        buf[buf_cur ++] = ',';
        bool ret2 = rec(true);
        buf[buf_cur ++] = '>';
        return ret1 & ret2;
      } else {
        buf[buf_cur ++] = 'i';
        buf[buf_cur ++] = 'n';
        buf[buf_cur ++] = 't';
        if ( ! prev && in->tokens == 1 )
          return true;
        return prev;
      }
      return false;
    }
    
    bool input() {
      return input_number() && input_tokens();
    }

    bool input_number() {
      String line;
      if ( ! std::getline(std::cin, line) )
        return false;
      std::istringstream iss(line);
      iss >> in->N;
      return true;
    }

    bool input_tokens() {
      String line;
      if ( ! std::getline(std::cin, line) )
        return false;
      std::istringstream iss(line);
      String token;
      in->tokens = 0;
      while ( iss >> token ) {
        in->token[in->tokens ++] = ( token == "pair" );
      }
      return true;
    }
    
    void output() {
      if ( out->ok ) {
        std::cout << out->result << std::endl;
      } else {
        std::cout << "Error occurred" << std::endl;
      }
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

