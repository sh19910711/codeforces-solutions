
// @snippet<sh19910711/contest-base:headers.cpp>
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

#include <memory>
#include <array>


// @snippet<sh19910711/contest-base:utils/collection.cpp>
namespace utils {
  // fill(A), fill(A, num), fill(A, num, value)
  template <class T> void fill( T& v ) { std::fill(std::begin(v), std::end(v), 0); }
  template <class T> void fill( T& v, const int& n ) { std::fill(std::begin(v), std::begin(v) + n, 0); }
  template <class T, class V> void fill( T& v, const int& n, const V& value ) { std::fill(std::begin(v), std::begin(v) + n, value); }
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t ) { std::copy(std::begin(s), std::end(s), std::begin(t)); }
  template <class T> void copy( const T& s, const int& n, T& t ) { std::copy(std::begin(s), std::begin(s) + n, std::begin(t)); }
}

// @snippet<sh19910711/contest-base:solution/template-class.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    SolverInterface* solver;
    Storages* storages;
    virtual int run() = 0;
    virtual bool input( InputStorage* s ) = 0;
    virtual void output( const OutputStorage* s ) = 0; 
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    virtual bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    virtual int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-primitive-types.cpp>
namespace solution {
  typedef int Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 1000000 + 11;
  const Int NONE = -1;
  const Int MAX_A = 4 * 1000000 + 11;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  using namespace utils;
  typedef std::array<Int, SIZE> IntArray;
  typedef std::array<bool, MAX_A> BoolArray;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    IntArray A;
  };
  
  struct OutputStorage {
    Int N;
    IntArray B;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  IntArray B;
  Int max_a;
  BoolArray E;

  struct Search {
    void init() {
      fill(E, MAX_A, false);
      max_a = 0;
      for ( auto i = 0; i < in->N; ++ i ) {
        Int a = in->A[i];
        max_a = std::max(max_a, a);
        E[a] = true;
      }
    }

    const IntArray& find_array() {
      for ( auto i = 0; i < in->N; ++ i ) {
        B[i] = find_number(in->A[i]);
      }
      return B;
    }

    Int find_number( const Int& a ) {
      for ( auto i = 0; i < MAX_A; ++ i ) {
        if ( ( a & i ) == 0 && E[i] )
          return i;
      }
      return NONE;
    }

    const InputStorage* in;
    Search(const InputStorage* in): in(in) { init(); }
  };

  struct Solver: SolverInterface {
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->N = in->N;
      Search search(in);
      const IntArray& ret = search.find_array();
      copy(ret, out->B);
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        std::cin >> in->A[i];
      return true;
    }
    void output( const OutputStorage* out ) {
      for ( auto i = 0; i < out->N; ++ i )
        std::cout << out->B[i] << " ";
      std::cout << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  using namespace solution;
  std::cin.sync_with_stdio(false);
  static InputStorage in;
  static OutputStorage out;
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

