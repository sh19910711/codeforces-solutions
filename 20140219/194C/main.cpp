
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
  const Int SIZE = 50 + 1;
  const Int MAX_V = SIZE * SIZE;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    String S[SIZE];
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
    
    typedef std::pair<Int, Int> Pos;
    typedef std::vector<Pos> PosVector;
    typedef std::array<PosVector, MAX_V> AdjacentList;

    Int N;
    Int H;
    Int W;
    AdjacentList G;
    bool used[MAX_V];
    bool forbidden[MAX_V];

    void init() {
    }
    
    void solve() {
      H = in->N;
      W = in->M;
      N = get_colored_num();
      generate_graph();
      out->result = count();
    }

    Int get_colored_num() {
      Int res = 0;
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = 0; j < W; ++ j ) {
          if ( is_colored(i, j) ) {
            res ++;
          }
        }
      }
      return res;
    }

    Int rec( const Int& r, const Int& c ) {
      auto id = get_index(r, c);
      if ( used[id] )
        return 0;
      used[id] = true;
      Int res = 1;
      for ( auto to : G[id] ) {
        auto next_id = get_index(to.first, to.second);
        if ( used[next_id] )
          continue;
        if ( forbidden[next_id] )
          continue;
        res += rec(to.first, to.second);
      }
      return res;
    }

    Int rec_start( const Int& r, const Int& c ) {
      auto id = get_index(r, c);
      for ( auto to : G[id] ) {
        return rec(to.first, to.second);
      }
      return 0;
    }

    bool check() {
      std::fill(forbidden, forbidden + MAX_V, false);
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = 0; j < W; ++ j ) {
          if ( is_colored(i, j) ) {
            forbidden[get_index(i, j)] = true;
            std::fill(used, used + MAX_V, false);
            auto ret = rec_start(i, j);
            if ( ret < N - 1 )
              return true;
            forbidden[get_index(i, j)] = false;
          }
        }
      }
      return false;
    }

    Int count() {
      if ( N <= 2 )
        return -1;
      if ( check() ) {
        return 1;
      } else {
        return 2;
      }
      return -2;
    }

    bool is_colored( const Int& r, const Int& c ) {
      return in->S[r][c] == '#';
    }

    Int get_index( const Int& r, const Int& c ) {
      return r * W + c;
    }

    void generate_graph() {
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = 0; j < W; ++ j ) {
          G[get_index(i, j)].clear();
        }
      }
      for ( auto i = 0; i < H; ++ i ) {
        for ( auto j = 0; j < W; ++ j ) {
          if ( ! is_colored(i, j) )
            continue;
          const int dr[4] = {1, -1, 0, 0};
          const int dc[4] = {0, 0, 1, -1};
          for ( int k = 0; k < 4; ++ k ) {
            int nr = i + dr[k];
            int nc = j + dc[k];
            if ( nr < 0 || nr >= H || nc < 0 || nc >= W )
              continue;
            if ( ! is_colored(nr, nc) )
              continue;
            G[get_index(i, j)].push_back(Pos {nr, nc});
          }
        }
      }
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N >> in->M ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->S[i] ) )
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

