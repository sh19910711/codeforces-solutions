
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
  const Int SIZE = 1000 + 11;
  typedef std::array<Int, SIZE> IntArray;
  typedef std::array<char, SIZE> CharArray;
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
    
    Int ID;
    CharArray T;
    IntArray L;
    IntArray LB;
    
    void solve() {
      generate_tl(in->S);
      out->result = find_max_char();
    }

    Int find_max_char() {
      Int res = std::numeric_limits<Int>::min();
      for ( auto c = 'A'; c <= 'Z'; ++ c ) {
        res = std::max(res, find_max(c));
      }
      return res;
    }

    Int find_max_len( const char& c ) {
      Int res = std::numeric_limits<Int>::min();
      for ( auto i = 0; i < ID; ++ i ) {
        if ( T[i] != c )
          continue;
        res = std::max(res, L[i]);
      }
      return res;
    }

    Int find_max( const char& c ) {
      Int res = find_max_len(c);
      Int n = ID;
      LB = L;
      for ( auto i = 0; i < n; ++ i ) {
        if ( T[i] != c )
          continue;
        L = LB;
        Int sum = L[i];
        for ( auto j = i + 1; j < n; ) {
          if ( T[j] != c ) {
            Int len = 0;
            while ( j < n && T[j] != c ) {
              len += L[j];
              j += 1;
            }
            if ( ( len % 2 ) && j < n && T[j] == c ) {
              L[j] --;
              len ++;
            }
            if ( len % 2 )
              break;
          } else {
            sum += L[j];
            j += 1;
          }
        }
        res = std::max(res, sum);
      }
      return res;
    }

    void generate_tl( const String& s ) {
      Int n = s.size();
      char prev = ' ';
      ID = 0;
      Int cnt = 0;
      for ( Int i = 0; i < n; ++ i ) {
        if ( prev != s[i] ) {
          if ( prev != ' ' ) {
            T[ID] = prev;
            L[ID] = cnt;
            ID += 1;
          }
          cnt = 1;
        } else {
          cnt ++;
        }
        prev = s[i];
      }
      if ( cnt > 0 ) {
        T[ID] = prev;
        L[ID] = cnt;
        ID += 1;
      }
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

