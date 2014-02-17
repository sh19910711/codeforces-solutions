
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
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int R[SIZE];
    Int M;
    Int V[SIZE];
    Int P[SIZE];
  };
  struct Output {
    Int results[SIZE];
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    typedef std::vector <Int> IntVector;

    Int num[SIZE];
    Int num_cnt;
    Int parents[SIZE];
    Int v_height[SIZE];
    IntVector G[SIZE];
    Int tree_size[SIZE];
    IntVector height[SIZE];

    void init() {
      std::fill(num, num + SIZE, 0);
    }
    
    void solve() {
      generate_graph();
      num_cnt = 0;
      set_num(0);
      count_size(0);
      split(0);

      std::fill(out->results, out->results + SIZE, -2);
      for ( auto i = 0; i < in->M; ++ i ) {
        Int pivot = in->V[i];
        for ( auto j = 0; j < in->P[i]; ++ j ) {
          pivot = parents[pivot];
        }
        if ( v_height[in->V[i]] - in->P[i] <= 0 ) {
          out->results[i] = 0;
        } else {
          IntVector& h = height[v_height[in->V[i]]];
          Int l = std::lower_bound(h.begin(), h.end(), pivot) - h.begin();
          Int r = std::upper_bound(h.begin(), h.end(), pivot + tree_size[pivot]) - h.begin();
          out->results[i] = r - l - 1;
        }
      }
    }

    void split( const Int& from, const Int& depth = 0 ) {
      height[depth].push_back(num[from]);
      v_height[from] = depth;
      for ( auto to : G[from] ) {
        split(to, depth + 1);
      }
    }

    Int count_size( const Int& from ) {
      tree_size[from] = 1;
      for ( auto to : G[from] ) {
        tree_size[from] += count_size(to);
      }
      return tree_size[from];
    }

    void set_num( const Int& from ) {
      num[from] = num_cnt;
      num_cnt += 1;
      for ( auto to : G[from] ) {
        set_num(to);
      }
    }

    void generate_graph() {
      std::fill(G, G + SIZE, IntVector());
      for ( auto i = 0; i < in->N; ++ i ) {
        auto parent = in->R[i];
        parents[i + 1] = parent;
        G[parent].push_back(i + 1);
      }
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->R[i] ) )
          return false;
      if ( ! ( std::cin >> in->M ) )
        return false;
      for ( auto i = 0; i < in->M; ++ i )
        if ( ! ( std::cin >> in->V[i] >> in->P[i] ) )
          return false;
      return true;
    }
    
    void output() {
      for ( auto i = 0; i < in->M; ++ i )
        std::cout << out->results[i] << " ";
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

