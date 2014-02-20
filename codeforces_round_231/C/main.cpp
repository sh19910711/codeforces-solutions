
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
  const Int SIZE = 1000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int H;
    Int W;
    String S[SIZE][SIZE];
  };
  struct Output {
    String S[SIZE][SIZE];
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

    Int H;
    Int W;
    Int C[3];
    
    void solve() {
      H = in->H;
      W = in->W;
      std::fill(C, C + 3, 0);
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = 0; j < W; ++ j ) {
          if ( in->S[i][j] == "00" ) {
            C[0] ++;
          } else if ( in->S[i][j] == "01" ) {
            C[1] ++;
          } else {
            C[2] ++;
          }
        }
      }
      // std::cout << "00: " << C[0] << ", 01: " << C[1] << ", 11: " << C[2] << std::endl;
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = 0; j < W; ++ j ) {
          out->S[i][j] = "00";
        }
      }
      set_11(C[2]);
      set_01(C[1]);
    }

    void set_11( const Int& n ) {
      Int cnt = 0;
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = 0; j < W; ++ j ) {
          if ( cnt < n ) {
            cnt ++;
            out->S[i][j] = "11";
          }
        }
      }
    }

    void set_01( const Int& n ) {
      Int cnt = 0;
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = W - 1; j >= 0; -- j ) {
          if ( cnt < n ) {
            if ( i == 0 && out->S[i][j] == "00" ) {
              cnt ++;
              out->S[i][j] = "01";
            }
          }
        }
        for ( auto j = W - 1; j >= 0; -- j ) {
          if ( cnt < n ) {
            if ( out->S[i][j] == "00" ) {
              if ( i > 0 && out->S[i - 1][j] == "01" ) {
                cnt ++;
                out->S[i][j] = "10";
              } else if ( i > 0 && out->S[i - 1][j] == "10" ) {
                cnt ++;
                out->S[i][j] = "01";
              }
            }
          }
        }
      }
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = W - 1; j >= 0; -- j ) {
          if ( cnt < n ) {
            if ( out->S[i][j] == "00" ) {
              if ( i > 0 && out->S[i - 1][j] == "01" ) {
                cnt ++;
                out->S[i][j] = "10";
              } else if ( i > 0 && out->S[i - 1][j] == "10" ) {
                cnt ++;
                out->S[i][j] = "01";
              } else if ( out->S[i][j] == "00" ) {
                cnt ++;
                out->S[i][j] = "01";
              }
            }
          }
        }
      }
    }
    
    bool input() {
      if ( ! ( std::cin >> in->H >> in->W ) )
        return false;
      for ( auto i = 0; i < in->H; ++ i ) {
        for ( auto j = 0; j < in->W; ++ j ) {
          String s;
          std::cin >> s;
          std::sort(std::begin(s), std::end(s));
          in->S[i][j] = s;
        }
      }
      return true;
    }
    
    void output() {
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = 0; j < W; ++ j ) {
          std::cout << out->S[i][j] << " ";
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

