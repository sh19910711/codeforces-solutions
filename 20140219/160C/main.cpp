
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
  typedef std::map <Int, Int> IntMap;
  typedef std::pair <Int, Int> IntPair;
  typedef std::vector <IntPair> IntPairVector;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int K;
    Int A[SIZE];
  };
  struct Output {
    Int A;
    Int B;
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
      Int B[SIZE];
      std::copy(in->A, in->A + in->N, B);
      std::sort(B, B + in->N);
      Int tmp = 0;
      Int i;
      Int k = in->K;
      k -= 1;
      for ( i = 0; i < in->N; i += tmp ) {
        for ( tmp = 1; B[i] == B[i + tmp]; ++ tmp );
        if ( tmp * in->N > k )
          break;
        k -= tmp * in->N;
      }
      out->A = B[i];
      out->B = B[k / tmp];
    }

    void solve3() {
      Int B[SIZE];
      std::copy(in->A, in->A + in->N, B);
      std::sort(B, B + in->N);
      IntMap cnt;
      for ( auto i = 0; i < in->N; ++ i ) {
        ++ cnt[B[i]];
      }
      IntPairVector v;
      for ( auto p : cnt ) {
        v.push_back(std::make_pair(p.first, p.second));
      }
      Int sum = 0;
      Int ai = 0;
      for ( ai = 0; ai < v.size(); ) {
        if ( sum + v[ai].second * in->N >= in->K )
          break;
        sum += v[ai].second * in->N;
        ai += 1;
      }
      out->A = v[ai].first;
      Int rem = in->K - sum - 1;
      Int bi = 0;
      while ( rem > 0 ) {
        rem -= v[bi].second;
        bi += 1;
      }
      out->B = v[bi].first;
    }
    
    void solve2() {
      Int B[SIZE];
      std::copy(in->A, in->A + in->N, B);
      std::sort(B, B + in->N);
      Int ai = 0;
      while ( ( ai + 1 ) * in->N < in->K )
        ai += 1;
      out->A = B[ai];
      Int bi = 0;
      while ( bi < in->N && ai * in->N + bi + 1 < in->K )
        bi += 1;
      out->B = B[bi];
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N >> in->K ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->A[i] ) )
          return false;
      return true;
    }
    
    void output() {
      std::cout << out->A << " " << out->B << std::endl;
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

