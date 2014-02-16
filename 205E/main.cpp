
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
  typedef double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int MAX_N = 2 * 100000 + 11;
  const Int MAX_C = 26;
  typedef std::array<Int, MAX_C> IntArray;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    String A;
    String B;
  };
  struct Output {
    Double result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //

    IntArray cnt_a;
    IntArray cnt_b;

    void solve() {
      std::fill(std::begin(cnt_a), std::end(cnt_a), Int(0));
      std::fill(std::begin(cnt_b), std::end(cnt_b), Int(0));
      Double ret = f();
      Double N = in->N;
      out->result = ret / N / ( N + 1.0 ) / ( 2.0 * N + 1.0 ) * 6.0;
    }

    Double f() {
      Double res = 0;
      Double N = in->N;
      for ( Int i = 0; i < in->N; ++ i ) {
        Int a = in->A[i] - 'A';
        Int b = in->B[i] - 'A';
        cnt_b[b] += i + 1;
        res += ( N - (Double)i ) * (Double)cnt_a[b];
        res += ( N - (Double)i ) * (Double)cnt_b[a];
        cnt_a[a] += i + 1;
      }
      return res;
    }
    
    bool input() {
      return std::cin >> in->N >> in->A >> in->B;
    }
    
    void output() {
      std::cout << std::setprecision(12) << out->result << std::endl;
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

