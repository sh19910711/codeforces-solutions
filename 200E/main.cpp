
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
  typedef int Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 300 + 11;
  const Int NONE = std::numeric_limits<Int>::max();
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
    Int S;
    IntArray A;
  };
  
  struct Output {
    Int best_f;
    Int best_K[3];
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Finder {
    Int best_f;
    Int best_K[3];
    Int C[3];

    void init() {
      best_f = NONE;
      init_c();
    }

    void init_c() {
      fill(C, 3, 0);
      for ( auto i = 0; i < in->N; ++ i ) {
        C[in->A[i] - 3] ++;
      }
    }

    Int f( const Int& k3, const Int& k4, const Int& k5 ) {
      // f(k3, k4, k5) = |c3*k3 - c4*k4| + |c4*k4 - c5*k5|
      return std::abs(C[0] * k3 - C[1] * k4) + std::abs(C[1] * k4 - C[2] * k5);
    }

    Int get_sum( const Int& k3, const Int& k4, const Int& k5 ) {
      return k3 * C[0] + k4 * C[1] + k5 * C[2];
    }

    void find() {
      for ( auto k3 = in->S / in->N; k3 >= 0; -- k3 ) {
        for ( auto k4 = ( in->S - k3 * C[0] ) / ( in->N - C[0] ); k4 >= k3; -- k4 ) {
          Int mid = ( in->S - k3 * C[0] - k4 * C[1] ) / ( in->N - C[0] - C[1] );
          if ( mid * C[2] - k4 * C[1] > best_f )
            break;
          if ( get_sum(k3, k4, mid) == in->S ) {
            auto ret = f(k3, k4, mid);
            if ( ret < best_f ) {
              best_f = ret;
              best_K[0] = k3;
              best_K[1] = k4;
              best_K[2] = mid;
            }
          }
          continue;
          // std::cout << k3 << ", " << k4 << ", " << k5 << std::endl;
          Int lb = 0;
          Int ub = in->S + 1;

          while ( ub - lb > 1 ) {
            Int mid = ( lb + ub ) * 0.5;
            auto sum = get_sum(k3, k4, mid);
            if ( sum <= in->S ) {
              // std::cout << "mid = " << mid << ": " << k3 << ", " << k4 << ", " << mid << ", sum = " << sum << std::endl;
              if ( sum == in->S ) {
                auto ret = f(k3, k4, mid);
                if ( ret < best_f ) {
                  best_f = ret;
                  best_K[0] = k3;
                  best_K[1] = k4;
                  best_K[2] = mid;
                }
              }
              lb = mid;
            } else {
              ub = mid;
            }
          }
        }
      }
    }

    const Input* in;
    Finder( const Input* in ): in(in) { init(); }
    typedef std::unique_ptr<Finder> Pointer;
    static Pointer create( const Input* in ) { return Pointer(new Finder(in)); }
  };

  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      auto finder = Finder::create(in);
      finder->find();
      if ( finder->best_f != NONE ) {
        out->best_f = finder->best_f;
        for ( auto i = 0; i < 3; ++ i ) {
          out->best_K[i] = finder->best_K[i];
        }
      } else {
        out->best_f = NONE;
      }
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->N >> in->S ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->A[i] ) )
          return false;
      return true;
    }
    void output( const Output* out ) {
      if ( out->best_f != NONE ) {
        for ( auto i = 0; i < 3; ++ i ) {
          std::cout << out->best_K[i] << " ";
        }
        std::cout << std::endl;
      } else {
        std::cout << -1 << std::endl;
      }
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

