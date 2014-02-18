
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
  const Int SIZE = 3000 + 11;
  typedef std::pair <Int, String> Person;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Person persons[SIZE];
  };
  struct Output {
    bool ok;
    Person persons[SIZE];
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
    
    void solve() {
      out->ok = can_make();
    }

    bool can_make() {
      Person persons[SIZE];
      std::copy(in->persons, in->persons + in->N, persons);
      std::sort(persons, persons + in->N);
      for ( auto i = 0; i < in->N; ++ i ) {
        Int a = persons[i].first;
        if ( a > i ) {
          return false;
        }
      }
      std::vector<Person> res;
      for ( auto i = 0; i < in->N; ++ i ) {
        res.insert(res.begin() + persons[i].first, std::make_pair(1000000000 - persons[i].first, persons[i].second));
      }
      std::copy(std::begin(res), std::end(res), out->persons);
      return true;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->persons[i].second >> in->persons[i].first ) )
          return false;
      return true;
    }
    
    void output() {
      if ( out->ok ) {
        for ( auto i = 0; i < in->N; ++ i ) {
          std::cout << out->persons[i].second << " " << out->persons[i].first << std::endl;
        }
      } else {
        std::cout << -1 << std::endl;
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

