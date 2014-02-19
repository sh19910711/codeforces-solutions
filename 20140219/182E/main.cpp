
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
  const Int MAX_N = 100 + 11;
  const Int MAX_L = 3000 + 111;
  const Int MOD = 1000000007;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int L;
    Int A[MAX_N];
    Int B[MAX_N];
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
    
    Int dp[MAX_L][MAX_N][2];

    void init() {
    }
    
    void solve() {
      for ( auto i = 0; i < MAX_L; ++ i ) {
        for ( auto j = 0; j < MAX_N; ++ j ) {
          for ( auto k = 0; k < 2; ++ k ) {
            dp[i][j][k] = 0;
          }
        }
      }
      out->result = count();
    }

    Int count() {
      Int n = in->N;
      Int l = in->L;
      for ( auto i = 0; i < n; ++ i ) {
        dp[in->A[i]][i][0] = 1;
        if ( in->A[i] != in->B[i] )
          dp[in->B[i]][i][1] = 1;
      }
      for ( auto i = 0; i <= l; ++ i ) {
        for ( auto j = 0; j < n; ++ j ) {
          for ( auto rot_j = 0; rot_j < 2; ++ rot_j ) {
            for ( auto k = 0; k < n; ++ k ) {
              for ( auto rot_k = 0; rot_k < 2; ++ rot_k ) {
                if ( j == k )
                  continue;
                // Int wj = rot_j ? in->A[j] : in->B[j];
                Int lj = rot_j ? in->B[j] : in->A[j];
                Int wk = rot_k ? in->A[k] : in->B[k];
                Int lk = rot_k ? in->B[k] : in->A[k];
                if ( rot_k == 0 ) {
                  if ( lj == wk ) {
                    dp[i + lk][k][rot_k] += dp[i][j][rot_j];
                    dp[i + lk][k][rot_k] %= MOD;
                  }
                } else if ( rot_k == 1 && wk != lk ) {
                  if ( lj == wk ) {
                    dp[i + lk][k][rot_k] += dp[i][j][rot_j];
                    dp[i + lk][k][rot_k] %= MOD;
                  }
                }
              }
            }
          }
        }
      }
      Int res = 0;
      for ( auto i = 0; i < in->N; ++ i ) {
        for ( auto j = 0; j < 2; ++ j ) {
          res += dp[l][i][j];
          res %= MOD;
        }
      }
      return res;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N >> in->L ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->A[i] >> in->B[i] ) )
          return false;
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

