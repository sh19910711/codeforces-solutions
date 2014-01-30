
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

namespace utils {}


// @snippet<sh19910711/contest-base:solution/define-classes.cpp>
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

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  using namespace utils;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 1000 + 11;
  const Int MAX_N = 500 + 11;
  const Int INF = std::numeric_limits<Int>::max();
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::array<Int, SIZE> IntArray;
  typedef std::array<std::array<bool, MAX_N>, MAX_N> Graph;
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int M;
    IntArray A;
    IntArray B;
  };
  
  struct OutputStorage {
    Int result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Counter {
    Graph G;
    IntArray d_in;
    IntArray d_out;

    void init() {
      init_graph();
      init_degree();
      // for ( auto i = 0; i < in->N; ++ i ) { cout << i << ": in = " << d_in[i] << " / out = " << d_out[i] << endl; }
    }

    void fill( IntArray& t, Int v = 0 ) {
      std::fill(begin(t), end(t), v);
    }

    void init_degree() {
      fill(d_in, 0);
      fill(d_out, 0);
      for ( auto from = 0; from < in->N; ++ from ) {
        for ( auto to = 0; to < in->N; ++ to ) {
          if ( G[from][to] ) {
            d_in[to]    += 1;
            d_out[from] += 1;
          }
        }
      }
    }

    void init_graph() {
      for ( auto i = 0; i < MAX_N; ++ i ) {
        for ( auto j = 0; j < MAX_N; ++ j ) {
          G[i][j] = false;
        }
      }
      for ( auto i = 0; i < in->M; ++ i ) {
        int a = in->A[i] - 1;
        int b = in->B[i] - 1;
        G[a][b] = true;
      }
    }

    Int count() {
      Int res = INF;
      for ( auto i = 0; i < in->N; ++ i ) {
        res = std::min(res, count(i));
      }
      return res;
    }

    Int count( const Int& center ) {
      Int res = 0;
      for ( auto i = 0; i < in->N; ++ i ) {
        if ( i == center ) {
          if ( ! G[center][center] )
            res ++;
          continue;
        }
        Int remove_in = d_in[i] - (G[center][i] ? 1 : 0) - (G[i][i] ? 1 : 0);
        Int remove_out = d_out[i] - (G[i][center] ? 1 : 0) - (G[i][i] ? 1 : 0);
        // cout << "  i = " << i + 1 << ", removes: in = " << remove_in << ", out = " << remove_out << endl;
        Int add_in = 1 - (G[center][i] ? 1 : 0) - (G[i][i] ? 0 : 0);
        Int add_out = 1 - (G[i][center] ? 1 : 0) - (G[i][i] ? 0 : 0);
        // cout << "  i = " << i + 1 << ", adds:    in = " << add_in << ", out = " << add_out << endl;
        // if ( ! G[i][i] ) cout << "  need loop" << endl;
        res += remove_in + remove_out + add_in + add_out + (G[i][i] ? 0 : 1);
      }
      // cout << "@center = " << center + 1 << ": res = " << res << endl;
      // cout << endl;
      return res;
    }

    const InputStorage* in;
    Counter(const InputStorage* in): in(in) { init(); }
  };

  struct Solver: SolverInterface {
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      Counter counter(in);
      out->result = counter.count();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->M ) )
        return false;
      for ( auto i = 0; i < in->M; ++ i )
        std::cin >> in->A[i] >> in->B[i];
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

