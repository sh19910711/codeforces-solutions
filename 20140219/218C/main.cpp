
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

// @snippet<sh19910711/contest:setlib/disjoints_set.cpp>
namespace setlib {
  // @desc 素集合データ構造
  class DisjointSets {
  public:
    std::vector<int> data;
    DisjointSets( int size ): data(size, -1) {};
    void init( int size ) { data.resize(size); std::fill( data.begin(), data.end(), -1 ); }
    bool merge( int x, int y ) {
      x = root(x), y = root(y);
      if ( x != y ) {
        if ( data[y] < data[x] ) std::swap( x, y );
        data[x] += data[y], data[y] = x;
      }
      return x != y;
    }
    bool same( int x, int y ) { return root(x) == root(y); }
    int root( int x ) { return data[x] < 0 ? x : data[x] = root(data[x]); }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int MAX_N = 100 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int X[MAX_N];
    Int Y[MAX_N];
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
    
    typedef setlib::DisjointSets UnionFind;
    typedef std::map<Int, Int> IntMap;
    typedef std::set<Int> IntSet;

    IntMap xx;
    IntMap yy;

    void init() {
    }

    Int get_index( const Int& x, const Int& y ) {
      return x + y * xx.size();
    }
    
    void solve() {
      xx.clear();
      yy.clear();
      Int cnt = 0;
      for ( auto i = 0; i < in->N; ++ i ) {
        if ( ! xx.count(in->X[i]) ) {
          xx[in->X[i]] = cnt ++;
        }
        if ( ! yy.count(in->Y[i]) ) {
          yy[in->Y[i]] = cnt ++;
        }
      }
      UnionFind uf(2000 * 2000);
      for ( auto i = 0; i < in->N; ++ i ) {
        for ( auto j = 0; j < in->N; ++ j ) {
          if ( in->X[i] == in->X[j] || in->Y[i] == in->Y[j] ) {
            uf.merge(get_index(xx[in->X[i]], yy[in->Y[i]]), get_index(xx[in->X[j]], yy[in->Y[j]]));
          }
        }
      }
      IntSet g;
      for ( auto i = 0; i < in->N; ++ i ) {
        Int id = get_index(xx[in->X[i]], yy[in->Y[i]]);
        g.insert(uf.root(id));
      }
      out->result = g.size() - 1;
    }
    
    bool input() {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->X[i] >> in->Y[i] ) )
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


