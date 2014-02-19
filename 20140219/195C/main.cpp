
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
  const Int MAX_N = 100000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    String S[MAX_N];
  };
  struct Output {
    String result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //

    typedef std::map<String, Int> StringMap;
    
    Int N;
    String S[MAX_N];
    enum LineType {LINE_TRY, LINE_THROW, LINE_CATCH, LINE_EMPTY};
    Int types[MAX_N];
    Int symbol_id[MAX_N];
    StringMap symbol;
    String message[MAX_N];
    Int catch_id[MAX_N];

    void init() {
    }
    
    void solve() {
      symbol.clear();
      N = in->N;
      init_lines();
      out->result = exec();
    }

    String exec() {
      std::stack<Int> sym[MAX_N];
      for ( auto i = 0; i < N; ++ i ) {
        if ( types[i] == LINE_TRY ) {
          Int cid = catch_id[i];
          sym[symbol_id[cid]].push(cid);
        } else if ( types[i] == LINE_THROW ) {
          if ( sym[symbol_id[i]].size() )
            return message[sym[symbol_id[i]].top()];
        } else if ( types[i] == LINE_CATCH ) {
          if ( ! sym[symbol_id[i]].empty() )
            sym[symbol_id[i]].pop();
        }
      }
      return "Unhandled Exception";
    }

    void init_lines() {
      std::copy(in->S, in->S + MAX_N, S);
      for ( auto i = 0; i < N; ++ i ) {
        while ( S[i].size() > 1 && S[i][0] == ' ' )
          S[i] = S[i].substr(1);
      }
      for ( auto i = 0; i < N; ++ i ) {
        if ( S[i].substr(0, 3) == "try" ) {
          types[i] = LINE_TRY;
        } else if ( S[i].substr(0, 5) == "throw" ) {
          types[i] = LINE_THROW;
        } else if ( S[i].substr(0, 5) == "catch" ) {
          types[i] = LINE_CATCH;
        } else {
          types[i] = LINE_EMPTY;
        }
      }
      for ( auto i = 0; i < N; ++ i ) {
        if ( types[i] == LINE_THROW ) {
          symbol_id[i] = get_symbol_id_from_throw(S[i]);
        } else if ( types[i] == LINE_CATCH ) {
          symbol_id[i] = get_symbol_id_from_catch(S[i]);
        }
      }
      for ( auto i = 0; i < N; ++ i ) {
        if ( types[i] == LINE_CATCH ) {
          message[i] = get_message(S[i]);
        }
      }
      std::stack<Int> s;
      for ( auto i = N - 1; i >= 0; -- i ) {
        if ( types[i] == LINE_TRY ) {
          catch_id[i] = s.top();
          s.pop();
        } else if ( types[i] == LINE_CATCH ) {
          s.push(i);
        }
      }
    }

    String get_message( const String& s ) {
      bool flag = false;
      String res = "";
      for ( auto c : s ) {
        if ( c == '"' ) {
          if ( flag ) {
            break;
          } else {
            flag = true;
          }
        } else if ( flag ) {
          res += c;
        }
      }
      return res;
    }

    String trim( const String& s ) {
      String res = s;
      while ( res[0] == ' ' ) res = res.substr(1);
      std::reverse(std::begin(res), std::end(res));
      while ( res[0] == ' ' ) res = res.substr(1);
      std::reverse(std::begin(res), std::end(res));
      return res;
    }

    String get_symbol_str( const String& s ) {
      bool flag_l = false;
      String res = "";
      for ( char c : s ) {
        if ( c == ',' || c == ')' )
          break;
        if ( flag_l )
          res += c;
        if ( c == '(' )
          flag_l = true;
      }
      return trim(res);
    }

    Int get_symbol_id_from_throw( const String& s ) {
      String symbol_str = get_symbol_str(s);
      if ( symbol.count(symbol_str) )
        return symbol[symbol_str];
      return symbol[symbol_str] = symbol.size();
    }

    Int get_symbol_id_from_catch( const String& s ) {
      String symbol_str = get_symbol_str(s);
      if ( symbol.count(symbol_str) )
        return symbol[symbol_str];
      return symbol[symbol_str] = symbol.size();
    }
    
    bool input() {
      return input_n() && input_s();
    }

    bool input_n() {
      String line;
      if ( ! std::getline(std::cin, line) )
        return false;
      std::istringstream iss(line);
      iss >> in->N;
      return true;
    }

    bool input_s() {
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! std::getline(std::cin, in->S[i]) )
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

