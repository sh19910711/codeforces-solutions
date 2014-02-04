
// @snippet<sh19910711/contest-base:headers.cpp>
#define __THIS_IS_CPP11__
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif


// @snippet<sh19910711/contest:utils/collection_prototype.cpp>
namespace utils {
  // collection
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class T, class V> void fill( T& v, const int& n, const V& value );
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t );
  template <class T> void copy( const T& s, const int& n, T& t );
  // sort(A), sort(begin, num)
  template <class T> void sort( T& v );
  template <class T> void sort( T& v, const int& n );
#endif
}

// @snippet<sh19910711/contest:utils/misc_prototype.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b );
  template <class T> void min( T& a, const T& b );
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v );
  template <class T> T to_type( const std::string& s );
  
}

// @snippet<sh19910711/contest:utils_prototypes.cpp>

// @snippet<sh19910711/contest-base:solution/template-class.cpp>
namespace solution {
  struct Input;
  struct Output;
  struct Storages {
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const Output* solve( const Input* in, Output* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    virtual int run()                             = 0;
    virtual bool action()                         = 0;
    virtual bool input( Input* s )         = 0;
    virtual void output( const Output* s ) = 0;
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    SolverInterface* solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    
    int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
    
    bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-primitive-types.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 100000 + 11;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace utils;
  typedef std::array<Int, SIZE> IntArray;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct Input {
    Int N;
    IntArray U;
    IntArray V;
    Int K;
    IntArray A;
    IntArray B;
  };
  
  struct Output {
    Int N;
    IntArray A;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  typedef std::tuple<Int, Int> VertexBase;
  struct Vertex: VertexBase {
    using VertexBase::tuple;
    Int& get_to() { return std::get<0>(*this); }
    const Int& get_to() const { return std::get<0>(*this); }
    Int& get_edge_id() { return std::get<1>(*this); }
    const Int& get_edge_id() const { return std::get<1>(*this); }
  };

  struct Counter {
    typedef std::vector<Vertex> VertexVector;
    typedef std::array<VertexVector, SIZE> AdjacentList;

    IntArray cnt;
    AdjacentList G;
    IntArray D; // depth
    IntArray P; // parent
    IntArray A;

    void init() {
      std::cout << "@Counter#init" << std::endl;
      fill(cnt, SIZE, 0);
      fill(D, SIZE, 0);
      fill(P, SIZE, 0);
      fill(A, SIZE, 0);
      init_graph();
    }

    void add_edge( const Int& u, const Int& v, const Int& edge_id ) {
      G[u].push_back(VertexBase {v, edge_id});
      G[v].push_back(VertexBase {u, edge_id});
    }

    void init_graph() {
      for ( auto& list : G ) {
        list.clear();
      }
      for ( auto i = 0; i < in->N - 1; ++ i ) {
        auto u = in->U[i] - 1;
        auto v = in->V[i] - 1;
        add_edge(u, v, i);
      }
    }

    Int get_lca( const Int& a, const Int& b ) {
      // std::cout << "@get_lca: " << a << ", " << D[a] << ", " << b << ", " << D[b] << std::endl;
      Int u = a;
      Int v = b;
      while ( D[u] > D[v] ) u = P[u];
      while ( D[u] < D[v] ) v = P[v];
      while ( u != v ) {
        u = P[u];
        v = P[v];
      }
      return u;
    }

    void calc_depth( const Int& cur, const Int& from = -1, const Int& depth = 0 ) {
      D[cur] = depth;
      P[cur] = from;
      // std::cout << "@calc_depth: " << cur << ", " << D[cur] << std::endl;
      for ( auto v : G[cur] ) {
        if ( v.get_to() == from )
          continue;
        // std::cout << cur << " - " << v.get_to() << std::endl;
        calc_depth(v.get_to(), cur, depth + 1);
      }
    }

    void count_used( const Int& cur, const Int& from = -1 ) {
      for ( auto v : G[cur] ) {
        if ( v.get_to() == from )
          continue;
        count_used(v.get_to(), cur);
        A[v.get_to()] += cnt[v.get_to()];
      }
    }

    void count() {
      calc_depth(0);
      for ( auto i = 0; i < in->K; ++ i ) {
        auto u = in->A[i] - 1;
        auto v = in->B[i] - 1;
        cnt[u] ++;
        cnt[v] ++;
        auto lca = get_lca(u, v);
        // std::cout << "lca = " << lca << std::endl;
        if ( lca != u )
          cnt[lca] --;
      }
      for ( auto i = 0; i < in->N; ++ i ) {
        std::cout << i << ": " << cnt[i] << std::endl;
      }
      count_used(0);
      std::cout << "A:" << std::endl;
      for ( auto i = 0; i < in->N - 1; ++ i ) {
        std::cout << i << ": " << A[i] << std::endl;
      }
    }

    const Input* in;
    Counter(const Input* in): in(in) { init(); }
  };
  typedef std::unique_ptr<Counter> CounterPointer;

  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      out->N = in->N - 1;
      auto counter = CounterPointer(new Counter(in));
      counter->count();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N - 1; ++ i )
        if ( ! ( std::cin >> in->U[i] >> in->V[i] ) )
          return false;
      if ( ! ( std::cin >> in->K ) )
        return false;
      for ( auto i = 0; i < in->K; ++ i )
        if ( ! ( std::cin >> in->A[i] >> in->B[i] ) )
          return false;
      return true;
    }
    void output( const Output* out ) {
      for ( auto i = 0; i < out->N; ++ i )
        std::cout << out->A[i] << " ";
      std::cout << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base:main_func.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  // desc: http://meme.biology.tohoku.ac.jp/students/iwasaki/cxx/speed.html#id18
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  // 
  using namespace solution;
  static Input in;
  static Output out;
  static Storages storages;
  static Solution solution;
  static Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif

// @snippet<sh19910711/contest:utils/collection.cpp>
namespace utils {
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class T, class V> void fill( T& v, const int& n, const V& value ) { std::fill(std::begin(v), std::begin(v) + n, value); }
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t ) { std::copy(std::begin(s), std::end(s), std::begin(t)); }
  template <class T> void copy( const T& s, const int& n, T& t ) { std::copy(std::begin(s), std::begin(s) + n, std::begin(t)); }
  // sort(A), sort(begin, num)
  template <class T> void sort( T& v ) { std::sort(std::begin(v), std::end(v)); }
  template <class T> void sort( T& v, const int& n ) { std::sort(std::begin(v), std::begin(v) + n); }
#endif
}

// @snippet<sh19910711/contest:utils/misc.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b ) { a = std::max(a, b); }
  template <class T> void min( T& a, const T& b ) { a = std::min(a, b); }
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v ) { std::ostringstream oss; oss << v; return oss.str(); }
  template <class T> T to_type( const std::string& s ) { std::istringstream iss(s); T res; iss >> res; return res; }
  
}

// @snippet<sh19910711/contest:utils.cpp>

// @snippet<sh19910711/contest-base:main.cpp>

