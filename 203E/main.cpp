
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
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class T, class V> void fill( T& v, const int& n, const V& value );
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t );
  template <class T> void copy( const T& s, const int& n, T& t );
  // sort(A), sort(begin, num)
  template <class T> void sort( T& v );
  template <class T> void sort( T& v, const int& n );
  // reverse(A), reverse(begin, num)
  template <class T> void reverse( T& v );
  template <class T> void reverse( T& v, const int& n );
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
    virtual int run()                      = 0;
    virtual bool action()                  = 0;
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
  typedef std::string String;
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
    Int D;
    Int S;
    IntArray C;
    IntArray F;
    IntArray L;
  };
  
  struct Output {
    Int max_robots;
    Int min_fuels;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct IndexList {
    static const Int offset = 1;
    Int N;
    IntArray I;
    IntArray L;
    IntArray R;

    IndexList() {
      fill(L, SIZE, 0);
      fill(R, SIZE, 0);
      for ( auto i = 0; i < SIZE; ++ i ) {
        I[i] = i;
      }
      update();
    }

    template <class Func> void each( Func f ) {
      for ( auto i = R[0]; i <= N; i = R[i] ) {
        f(get_index_inverse(i));
      }
    }

    void remove( const Int& x ) {
      Int index = get_index(x);
      Int l = L[index];
      Int r = R[index];
      R[l] = r;
      L[r] = l;
    }

    void update() {
      R[0] = I[0];
      for ( auto i = 0; i <= N; ++ i ) {
        L[get_index(I[i])] = get_index(I[i - 1]);
        R[get_index(I[i])] = get_index(I[i + 1]);
      }
      R[N] = N;
    }

    static Int get_index( const Int& x ) {
      return x + offset;
    }

    static Int get_index_inverse( const Int& x ) {
      return x - offset;
    }
  };

  struct Counter {
    Int max_robots;
    Int min_fuels;

    IndexList carriables;

    void init() {
      std::cout << "@Counter#init" << std::endl;
      max_robots = 0;
      min_fuels = 0;

      carriables.N = in->N;
      carriables.each([&]( const Int& x ) { std::cout << "x = " << x << std::endl; });
    }

    void count() {
    }

    const Input* in;
    Counter( const Input* in ): in(in) { init(); }
    typedef std::unique_ptr<Counter> Pointer;
    static Pointer create( const Input* in ) { return Pointer(new Counter(in)); }
  };
  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      auto counter = Counter::create(in);
      out->max_robots = counter->max_robots;
      out->min_fuels = counter->min_fuels;
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->N >> in->D >> in->S ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->C[i] >> in->F[i] >> in->L[i] ) )
          return false;
      return true;
    }
    void output( const Output* out ) {
      std::cout << out->max_robots << " " << out->min_fuels << std::endl;
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
  static Input      in;
  static Output     out;
  static Storages   storages;
  static Solution   solution;
  static Solver     solver;
  storages.in       = &in;
  storages.out      = &out;
  solution.storages = &storages;
  solution.solver   = &solver;
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
  // reverse(A), reverse(begin, num)
  template <class T> void reverse( T& v ) { std::reverse(std::begin(v), std::end(v)); }
  template <class T> void reverse( T& v, const int& n ) { std::reverse(std::begin(v), std::begin(v) + n); }
  // unique(A)
  template <class T> void unique( T& v ) { v.erase(std::unique(std::begin(v), std::end(v)), std::end(v)); }
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

