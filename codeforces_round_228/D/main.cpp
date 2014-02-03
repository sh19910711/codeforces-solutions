
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
  const Int SIZE = 1000 + 11;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace utils;
  typedef std::array<bool, SIZE> BoolArray;
  typedef std::array<BoolArray, SIZE> BoolTable;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct Input {
    Int K;
  };
  
  struct Output {
    Int N;
    BoolTable G;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Solver: SolverInterface {
    Int K;
    Int N;
    BoolTable G;
    Int last;

    const Output* solve( const Input* in, Output* out ) {
      K = in->K;
      init_graph();


      Int tmp = K;
      last = 2;
      Int max_x = -1;

      if ( tmp & 1 ) {
        generate_edges_single(log2(K) - 3);
        tmp --;
      }
      // copy(out);
      // return out;

      for ( Int i = 30; i > 0; -- i ) {
        Int c = std::pow(2LL, i);
        if ( i == 0 && c <= tmp ) {
        } else if ( c <= tmp ) {
          // std::cout << i << ": " << c << ", " << tmp << std::endl;
          generate_edges(max_x, i);
          tmp -= c;
          max(max_x, i);
        }
      }

      copy(out);
      return out;
    }

    void set_edge( Int u, Int v ) {
      G[u][v] = G[v][u] = true;
    }

    void generate_edges_single( Int max_x ) {
      if ( max_x == 0 )
        return;
      Int prev = last - 1;
      for ( auto i = 0; i < max_x; ++ i ) {
        set_edge(prev, last);
        prev = last;
        last ++;
      }
      set_edge(prev, 1);
    }

    void generate_edges( Int max_x, Int x ) {
      Int prev = 0;
      for ( auto i = 0; i < x; ++ i ) {
        if ( prev == 0 ) {
          set_edge(prev, last);
          set_edge(prev, last + 1);
        } else {
          set_edge(prev, last);
          set_edge(prev, last + 1);
          set_edge(prev + 1, last);
          set_edge(prev + 1, last + 1);
        }
        prev = last;
        last += 2;
      }
      // Int next = 1;

      set_edge(last - 2, x);
      set_edge(last - 1, x);

      /*
      if ( x > 0 && max_x == -1 ) {
        set_edge(last - 2, next);
        set_edge(last - 1, next);
      } else {
        Int l = last - 2;
        for ( auto i = x; i < max_x; ++ i ) {
          if ( l == last - 2 ) {
            set_edge(l, last);
            set_edge(l + 1, last);
          } else {
            set_edge(l, last);
          }
          l = last;
          last ++;
        }
        set_edge(l, 1);
      }
      */
    }

    void init_graph() {
      N = 1000;
      for ( auto i = 0; i < N; ++ i ) {
        for ( auto j = 0; j < N; ++ j ) {
          G[i][j] = false;
        }
      }
    }

    void copy( Output* out ) {
      out->N = last;
      out->G = G;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->K ) )
        return false;
      return true;
    }
    void output( const Output* out ) {
      std::cout << out->N << std::endl;
      for ( auto i = 0; i < out->N; ++ i ) {
        for ( auto j = 0; j < out->N; ++ j ) {
          std::cout << ( out->G[i][j] ? 'Y' : 'N' );
        }
        std::cout << std::endl;
      }
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

