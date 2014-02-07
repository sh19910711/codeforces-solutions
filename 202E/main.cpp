
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
  const Int NONE = std::numeric_limits<Int>::min();
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
    IntArray A;
  };
  
  struct Output {
    Int result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Counter {
    Int bridges;
    IntArray A;
    IntArray left;
    IntArray right;
    IntArray odd;
    IntArray even;
    IntArray sum_odd;

    void init() {
      copy(in->A, A);
    }

    void init_vars() {
      bridges = in->N - 1;
      init_odd_even();
      init_left_right();
      init_sum_odd();

      // std::cout << "N = " << in->N << std::endl;
      // std::cout << "odd: " << std::endl; for ( auto i = 0; i < bridges; ++ i ) std::cout << i << ": " << odd[i] << std::endl;
      // std::cout << "even: " << std::endl; for ( auto i = 0; i < bridges; ++ i ) std::cout << i << ": " << even[i] << std::endl;
      // std::cout << "sum_odd: " << std::endl; for ( auto i = 0; i < bridges; ++ i ) std::cout << i << ": " << sum_odd[i] << std::endl;
      // std::cout << "left: " << std::endl; for ( auto i = 0; i < bridges; ++ i ) std::cout << i << ": " << left[i] << std::endl;
      // std::cout << "right: " << std::endl; for ( auto i = 0; i < bridges; ++ i ) std::cout << i << ": " << right[i] << std::endl;
      // 
      // Int l = 0, r = 4;
      // std::cout << "l = " << l << ", r = " << r << std::endl;
      // std::cout << left[l] << " + " << right[r] << " + " << sum_odd[r] << " - " << sum_odd[l] << " => " << left[l] + right[r] + ( sum_odd[r] - sum_odd[l] ) << std::endl;
      // std::cout << std::endl;
    }

    static Int get_even( const Int& x ) {
      if ( x % 2 == 0 )
        return x;
      return x - 1;
    }

    static Int get_odd( const Int& x ) {
      if ( x % 2 == 1 )
        return x;
      return x - 1;
    }

    void init_sum_odd() {
      sum_odd[0] = 0;
      for ( auto i = 1; i <= bridges; ++ i ) {
        sum_odd[i] = sum_odd[i - 1] + ( i - 1 < bridges ? odd[i - 1] : 0 );
      }
    }

    void init_left_right() {
      left[0] = 0;
      for ( auto i = 1; i <= bridges; ++ i ) {
        if ( A[i - 1] == 1 ) {
          left[i] = 0;
        } else {
          left[i] = left[i - 1] + ( i - 1 < bridges ? even[i - 1] : 0 );
        }
      }
      right[bridges] = right[bridges - 1] = 0;
      for ( auto i = bridges - 1; i >= 0; -- i ) {
        if ( i < bridges && A[i] == 1 ) {
          right[i] = 0;
        } else {
          right[i] = right[i + 1] + ( i < bridges ? even[i] : 0 );
        }
      }
    }

    void init_odd_even() {
      for ( auto i = 0; i < bridges; ++ i ) {
        odd[i] = get_odd(A[i]);
        even[i] = get_even(A[i]);
      }
    }

    Int f( const Int& l, const Int& r ) {
      return left[l] + right[r] + ( sum_odd[r] - sum_odd[l] );
    }

    Int find_max() {
      Int res = 0;
      Int best = 0;
      for ( auto i = 0; i <= bridges; ++ i ) {
        max(best, left[i] - sum_odd[i]);
        max(res, best + right[i] + sum_odd[i]);
      }
      return res;
    }

    Int count() {
      if ( in->N == 2 )
        return in->A[0];
      Int res = in->N - 1;
      init_vars();
      max(res, find_max());
      std::reverse(std::begin(A), std::begin(A) + bridges);
      init_vars();
      max(res, find_max());
      return res;
    }

    const Input* in;
    Counter( const Input* in ): in(in) { init(); }
    typedef std::unique_ptr<Counter> Pointer;
    static Pointer create( const Input* in ) { return Pointer(new Counter(in)); }
  };

  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      auto counter = Counter::create(in);
      out->result = counter->count();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->N && in->N >= 2 ) )
        return false;
      for ( auto i = 0; i < in->N - 1; ++ i )
        if ( ! ( std::cin >> in->A[i] ) )
          return false;
      return true;
    }
    void output( const Output* out ) {
      std::cout << out->result << std::endl;
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

