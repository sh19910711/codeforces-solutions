
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
  const Int SIZE = 52 * 2;
  const String YES = "YES";
  const String NO = "NO";
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    String S[SIZE];
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
 
    struct Node {
      Int steps;
      Int a;
      Int b;
      Int c;
    };
    typedef std::queue <Node> Queue;
    Int C[SIZE];
    Queue Q;
    bool used[SIZE][SIZE][SIZE][SIZE];

    void init() {
    }
    
    void solve() {
      for ( auto i = 0; i < in->N; ++ i ) {
        C[i] = get_index(in->S[in->N - i - 1]);
      }
      out->result = check();
    }

    bool check() {
      if ( in->N == 1 )
        return true;
      if ( in->N == 2 )
        return can_put(C[0], C[1]);

      for ( auto i = 0; i < SIZE; ++ i ) {
        for ( auto j = 0; j < SIZE; ++ j ) {
          for ( auto k = 0; k < SIZE; ++ k ) {
            for ( auto l = 0; l < SIZE; ++ l ) {
              used[i][j][k][l] = false;
            }
          }
        }
      }
      Q = Queue();
      Q.push(Node {0, C[0], C[1], C[2]});

      while ( ! Q.empty() ) {
        auto cur = Q.front();
        Q.pop();

        // std::cout << cur.steps << ", " << get_card(cur.a) << ", " << get_card(cur.b) << ", " << get_card(cur.c) << std::endl;

        if ( cur.steps + 3 >= in->N )
          if ( can_put(cur.a, cur.b) && can_put(cur.a, cur.c) )
            return true;

        {
          Node next {cur.steps + 1, cur.a, cur.c, C[cur.steps + 3]};
          if ( cur.steps + 1 < in->N && can_put(cur.a, cur.b) ) {
            if ( ! used[cur.steps + 1][cur.a][cur.c][C[cur.steps + 3]] ) {
              used[cur.steps + 1][cur.a][cur.c][C[cur.steps + 3]] = true;
              Q.push(next);
            }
          }
        }
        {
          Node next {cur.steps + 1, cur.b, cur.c, cur.a};
          if ( cur.steps + 1 < in->N && can_put(cur.a, C[cur.steps + 3]) ) {
            if ( ! used[cur.steps + 1][cur.b][cur.c][cur.a] ) {
              used[cur.steps + 1][cur.b][cur.c][cur.a] = true;
              Q.push(next);
            }
          }
        }
      }
      return false;
    }

    int get_index( const String& s ) {
      const String& suit = "SDHC";
      const String& value = "A23456789TJQK";
      for ( auto i = 0; i < suit.size(); ++ i ) {
        for ( auto j = 0; j < value.size(); ++ j ) {
          String t = "";
          t += value[j];
          t += suit[i];
          if ( t == s )
            return i * value.size() + j;
        }
      }
      return -1;
    }

    String get_card( const Int& id ) {
      const String& suit = "SDHC";
      const String& value = "A23456789TJQK";
      String res;
      res += value[id % value.size()];
      res += suit[id / value.size()];
      return res;
    }

    bool can_put( const Int& a, const Int& b ) {
      return a % 13 == b % 13 || a / 13 == b / 13;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N && in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->S[i] ) )
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

