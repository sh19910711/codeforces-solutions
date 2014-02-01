
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

#define __THIS_IS_CPP11__
#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif


// @snippet<sh19910711/contest-base:utils/collection.cpp>
namespace utils {
  // fill(A), fill(A, num), fill(A, num, value)
  template <class T> void fill( T& v ) { std::fill(std::begin(v), std::end(v), 0); }
  template <class T> void fill( T& v, const int& n ) { std::fill(std::begin(v), std::begin(v) + n, 0); }
  template <class T, class V> void fill( T& v, const int& n, const V& value ) { std::fill(std::begin(v), std::begin(v) + n, value); }
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t ) { std::copy(std::begin(s), std::end(s), std::begin(t)); }
  template <class T> void copy( const T& s, const int& n, T& t ) { std::copy(std::begin(s), std::begin(s) + n, std::begin(t)); }
  // sort(A), sort(A, num)
  template <class T> void sort( T& v ) { std::sort(std::begin(v), std::end(v)); }
  template <class T> void sort( T& v, const int& n ) { std::sort(std::begin(v), std::begin(v) + n); }
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
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int MAX_N = 100 + 11;
  const Int MAX_L = 4000 + 11;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  using namespace utils;
  typedef std::array<Int, MAX_N> IntArray;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int L;
    IntArray A;
    IntArray B;
  };
  
  struct OutputStorage {
    Int result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Counter {
    typedef std::array<std::array<std::array<Int, 2>, MAX_N>, MAX_L> IntTable;
    typedef std::array<std::array<std::array<bool, 2>, MAX_N>, MAX_L> BoolTable;
    const Int NONE = 0;
    const Int MOD = 1000000007LL;

    IntTable cnt;

    void init() {
      for ( auto i = 0; i < in->L; ++ i ) {
        for ( auto j = 0; j < MAX_N; ++ j ) {
          for ( auto k = 0; k < 2; ++ k ) {
            cnt[i][j][k] = NONE;
          }
        }
      }
    }

    Int count() {
      for ( auto i = 0; i < in->N; ++ i ) {
        cnt[in->A[i]][i][0] = 1;
        if ( in->A[i] == in->B[i] )
          continue;
        cnt[in->B[i]][i][1] = 1;
      }
      for ( auto i = 0; i < in->L; ++ i ) {
        for ( auto j = 0; j < in->N; ++ j ) {
          for ( auto rot_j = 0; rot_j < 2; ++ rot_j ) {
            if ( rot_j == 1 && in->A[j] == in->B[j] )
              continue;
            for ( auto k = 0; k < in->N; ++ k ) {
              if ( j == k )
                continue;
              for ( auto rot_k = 0; rot_k < 2; ++ rot_k ) {
                if ( rot_k == 1 && in->A[k] == in->B[k] )
                  continue;
                auto jw = rot_j ? in->B[j] : in->A[j];
                auto kw = rot_k ? in->B[k] : in->A[k];
                auto kh = rot_k ? in->A[k] : in->B[k];
                if ( jw != kh )
                  continue;
                cnt[i + kw][k][rot_k] += cnt[i][j][rot_j];
                cnt[i + kw][k][rot_k] %= MOD;
              }
            }
          }
        }
      }
      Int res = 0;
      for ( auto i = 0; i < in->N; ++ i ) {
        for ( auto j = 0; j < 2; ++ j ) {
          res += cnt[in->L][i][j];
          res %= MOD;
        }
      }
      return res;
    }

    const InputStorage* in;
    Counter(const InputStorage* in): in(in) { init(); }
  };
  typedef std::unique_ptr<Counter> CounterPointer;

  struct Solver: SolverInterface {
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      auto counter = CounterPointer(new Counter(in));
      out->result = counter->count();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->L ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->A[i] >> in->B[i] ) )
          return false;
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << out->result << std::endl;
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

