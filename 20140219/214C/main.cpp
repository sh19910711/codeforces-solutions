
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
  const Int MAX_N = 200 + 11;
  typedef std::vector <Int> IntVector;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int C[MAX_N];
    Int K[MAX_N];
    IntVector A[MAX_N];
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
    
    const Int INF = std::numeric_limits<Int>::max();

    Int N;
    Int need[MAX_N];
    IntVector unlock_to[MAX_N];
    Int remains;
    bool used[MAX_N];

    void init() {
    }
    
    void solve() {
      N = in->N;
      init_graph();
      out->result = find();
    }

    Int rec( const Int& cur, const Int& c_id ) {
      if ( used[cur] )
        return 0;
      used[cur] = true;
      remains --;
      Int res = 1;
      for ( auto to : unlock_to[cur] ) {
        need[to] --;
        if ( need[to] == 0 && ! used[to] && in->C[to] - 1 == c_id ) {
          res += rec(to, c_id);
        }
      }
      return res;
    }

    Int update( const Int& s_id ) {
      Int c_id = s_id;
      Int res = 0;
      while ( remains > 0 ) {
        for ( auto i = 0; i < N; ++ i ) {
          if ( c_id == in->C[i] - 1 && need[i] == 0 && ! used[i] ) {
            res += rec(i, c_id);
          }
        }
        c_id = ( c_id + 1 ) % 3;
        if ( remains > 0 )
          res ++;
      }
      return res;
    }

    Int find() {
      Int res = INF;
      for ( auto i = 0; i < 3; ++ i ) {
        init_need();
        remains = N;
        std::fill(used, used + MAX_N, false);
        res = std::min(res, update(i));
      }
      return res;
    }

    void init_graph() {
      std::fill(unlock_to, unlock_to + MAX_N, IntVector());
      for ( auto i = 0; i < N; ++ i ) {
        for ( auto j = 0; j < in->K[i]; ++ j ) {
          auto to = in->A[i][j] - 1;
          unlock_to[to].push_back(i);
        }
      }
    }

    void init_need() {
      for ( auto i = 0; i < N; ++ i ) {
        need[i] = in->K[i];
      }
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i ) {
        std::cin >> in->C[i];
      }
      for ( auto i = 0; i < in->N; ++ i ) {
        std::cin >> in->K[i];
        in->A[i].clear();
        for ( auto j = 0; j < in->K[i]; ++ j ) {
          Int a;
          std::cin >> a;
          in->A[i].push_back(a);
        }
      }
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

