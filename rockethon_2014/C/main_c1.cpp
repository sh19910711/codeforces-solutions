
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
  const Int SIZE = 16;
  const Int INF = std::numeric_limits<Int>::max();
  typedef std::array<Int, SIZE> IntArray;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int K;
    IntArray P;
    IntArray E;
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
    
    IntArray P;
    IntArray PB;

    void solve() {
      out->result = get_min_efforts();
    }

    Int get_min_efforts() {
      Int res = INF;
      Int bn = Int(1) << in->N;
      P = in->P;
      PB = P;
      for ( Int s = 0; s < bn; ++ s ) {
        P = PB;
        Int points = get_points(s);
        Int efforts = get_efforts(s);
        Int rank = get_rank(points, s);
        if ( rank <= in->K )
          res = std::min(res, efforts);
      }
      return res;
    }

    Int get_rank( const Int& points, const Int& s ) {
      Int res = in->N + 1;
      for ( Int i = 0; i < in->N; ++ i ) {
        Int bi = Int(1) << i;
        if ( points > P[i] ) {
          res --;
        } else if ( points == P[i] && ( s & bi ) ) {
          res --;
        }
      }
      return res;
    }

    Int get_points( const Int& s ) {
      Int res = 0;
      Int tmp = s;
      while ( tmp > 0 ) {
        if ( tmp & 1 )
          res += 1;
        tmp >>= Int(1);
      }
      return res;
    }

    Int get_efforts( const Int& s ) {
      Int res = 0;
      for ( Int i = 0; i < in->N; ++ i ) {
        Int bi = Int(1) << i;
        if ( s & bi ) {
          res += in->E[i];
        } else {
          P[i] += 1;
        }
      }
      return res;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N >> in->K ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->P[i] >> in->E[i] ) )
          return false;
      return true;
    }
    
    void output() {
      if ( out->result == INF ) {
        std::cout << -1 << std::endl;
      } else {
        std::cout << out->result << std::endl;
      }
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

