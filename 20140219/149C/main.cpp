
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
  const Int A_MAX = 10000 + 11;
  typedef std::vector<Int> IntVector;
  typedef std::multiset<Int, std::greater<Int>> IntSet;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int A[SIZE];
  };
  struct Output {
    IntVector X;
    IntVector Y;
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
      out->X.clear();
      out->Y.clear();
      IntSet s;
      IntVector v[A_MAX];
      for ( auto i = 0; i < in->N; ++ i ) {
        s.insert(in->A[i]);
        v[in->A[i]].push_back(i + 1);
      }
      bool flag = true;
      for ( auto a : s ) {
        if ( flag ) {
          out->X.push_back(v[a].back());
          v[a].pop_back();
        } else {
          out->Y.push_back(v[a].back());
          v[a].pop_back();
        }
        flag = ! flag;
      }
    }
    
    void solve2() {
      out->X.clear();
      out->Y.clear();

      IntSet s;
      IntVector v[A_MAX];
      for ( auto i = 0; i < in->N; ++ i ) {
        s.insert(in->A[i]);
        v[in->A[i]].push_back(i + 1);
      }

      Int max_a = *s.begin();
      Int sum1 = 0;
      Int sum2 = 0;
      bool flag = true;
      while ( ! s.empty() ) {
        Int cand = -1;
        for ( auto v : s ) {
          if ( flag ) {
            if ( sum1 == 0 ) {
              cand = v;
              break;
            }
            if ( std::abs(sum1 + v - sum2) <= max_a ) {
              cand = v;
            } else {
              break;
            }
          } else {
            if ( std::abs(sum1 - ( sum2 + v )) <= max_a ) {
              cand = v;
            } else {
              break;
            }
          }
        }
        if ( cand == -1 ) {
          flag = ! flag;
          continue;
        }
        if ( flag ) {
          out->X.push_back(v[cand].back());
          v[cand].pop_back();
          sum1 += cand;
        } else {
          out->Y.push_back(v[cand].back());
          v[cand].pop_back();
          sum2 += cand;
        }
        s.erase(s.find(cand));
        flag = ! flag;
      }

      while ( std::abs( (Int)out->X.size() - out->Y.size() ) > 1 ) {
        if ( out->X.size() > out->Y.size() ) {
          Int tmp = out->X.back();
          out->X.pop_back();
          out->Y.push_back(tmp);
        } else {
          Int tmp = out->Y.back();
          out->Y.pop_back();
          out->X.push_back(tmp);
        }
      }
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->A[i] ) )
          return false;
      return true;
    }
    
    void output() {
      std::cout << out->X.size() << std::endl;
      for ( auto v : out->X ) {
        std::cout << v << " ";
      }
      std::cout << std::endl;
      std::cout << out->Y.size() << std::endl;
      for ( auto v : out->Y ) {
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

