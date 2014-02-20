
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
  const Int SIZE = 100000 + 11;
  typedef std::vector<Int> IntVector;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int D;
    Int A;
    Int B;
    Int X[SIZE];
    Int Y[SIZE];
  };
  struct Output {
    IntVector result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    typedef std::pair <Int, Int> IntPair;
    typedef std::vector <IntPair> IntPairVector;

    void init() {
    }
    
    void solve() {
      out->result.clear();
      IntPairVector l;
      for ( auto i = 0; i < in->N; ++ i ) {
        l.push_back(std::make_pair(in->X[i] * in->A + in->Y[i] * in->B, i));
      }
      std::sort(std::begin(l), std::end(l));
      Int rem = in->D;
      for ( Int i = 0; i < in->N; ++ i ) {
        if ( rem - l[i].first >= 0 ) {
          rem -= l[i].first;
          out->result.push_back(l[i].second + 1);
        }
      }
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N >> in->D ) )
        return false;
      if ( ! ( std::cin >> in->A >> in->B ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->X[i] >> in->Y[i] ) )
          return false;
      return true;
    }
    
    void output() {
      std::cout << out->result.size() << std::endl;
      for ( auto v : out->result ) {
        std::cout << v << " ";
      }
      std::cout << std::endl;
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

