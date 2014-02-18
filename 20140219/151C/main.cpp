
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
  typedef std::vector<Int> IntVector;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int Q;
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
    
    void init() {
    }

    bool is_prime( const Int& N ) {
      if ( N == 2 )
        return true;
      if ( N % 2 == 0 )
        return false;
      for ( Int i = 3; i * i <= N; i += 2 )
        if ( N % i == 0 )
          return false;
      return true;
    }
    
    void solve() {
      out->result.clear();
      IntVector p;
      Int tmp = in->Q;
      if ( tmp == 1 || is_prime(tmp) ) {
        out->result.push_back(0);
        return;
      }
      if ( is_prime(tmp) )
        return;
      for ( Int i = 2; i * i <= tmp; i += 1 ) {
        if ( tmp % i == 0 && is_prime(i) ) {
          while ( tmp % i == 0 ) {
            p.push_back(i);
            tmp /= i;
          }
        }
      }
      if ( tmp > 1 ) p.push_back(tmp);
      std::sort(std::begin(p), std::end(p));
      if ( ! p.empty() ) {
        if ( p.size() == 1 ) {
          out->result.push_back(p.back());
        } else {
          Int cnt = 0;
          for ( auto d : p )
            if ( is_prime(d) )
              cnt ++;
          if ( cnt == 2 )
            return;
          out->result.push_back(p[0] * p[1]);
        }
      }
    }
    
    bool input() {
      return std::cin >> in->Q;
    }
    
    void output() {
      if ( out->result.empty() ) {
        std::cout << 2 << std::endl;
      } else {
        std::cout << 1 << std::endl;
        for ( auto v : out->result ) {
          std::cout << v << " ";
        }
        std::cout << std::endl;
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

