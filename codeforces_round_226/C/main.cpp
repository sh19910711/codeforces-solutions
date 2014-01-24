
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

// @snippet<sh19910711/contest-base:solution/define_classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
  class SolverInterface {
  public:
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    SolverInterface* solver;
    Storages* storages;
  protected:
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
  class SolutionBase: public SolutionInterface {
  public:
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
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const Int SIZE = 1000000 + 11;
  const Int MAX_N = 10000000 + 11;
  
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int A[SIZE];
    Int M;
    Int L[SIZE];
    Int R[SIZE];
  };
  struct OutputStorage {
    Int M;
    Int results[SIZE];
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  class Solver: public SolverInterface {
  public:
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      count(in);
      out->M = in->M;
      for ( int i = 0; i < in->M; ++ i ) {
        out->results[i] = query(in->L[i], in->R[i]);
      }
      return out;
    }

  protected:
    Int query( const Int& L, const Int& R ) {
      int lid = std::lower_bound(p, p + pc, L) - p;
      int rid = std::lower_bound(p, p + pc, R) - p;
      if ( p[rid] != R )
        rid -= 1;
      return std::max(0LL, get_sum(rid) - get_sum(lid - 1));
    }

    Int get_sum( const int& id ) {
      if ( id < 0 )
        return 0;
      return sum[id];
    }

    void count( const InputStorage* in ) {
      std::fill(is_p, is_p + MAX_N, false);
      std::fill(cnt, cnt + MAX_N, 0);
      std::fill(used, used + MAX_N, 0);
      std::fill(sum, sum + MAX_N, 0);
      generate_primes();
      generate_cnt(in->N, in->A);
      generate_used();
      generate_sum();
    }

    void generate_sum() {
      Int tmp = 0;
      for ( int i = 0; i < pc; ++ i ) {
        tmp += used[i];
        sum[i] = tmp;
      }
    }

    void generate_cnt( const Int& N, const Int A[SIZE] ) {
      for ( int i = 0; i < N; ++ i ) {
        cnt[A[i]] += 1;
      }
    }

    void generate_used() {
      for ( int i = 0; i < pc; ++ i ) {
        for ( int j = p[i]; j < MAX_N; j += p[i] ) {
          used[i] += cnt[j];
        }
      }
    }

    void generate_primes() {
      is_p[2] = true;
      for ( int i = 3; i < MAX_N; i += 2 ) {
        is_p[i] = true;
      }
      for ( int i = 3; i < MAX_N; i += 2 ) {
        if ( ! is_p[i] )
          continue;
        for ( int j = i + i; j < MAX_N; j += i )
          is_p[j] = false;
      }
      pc = 0;
      p[pc ++] = 2;
      for ( int i = 3; i < MAX_N; i += 2 ) {
        if ( is_p[i] )
          p[pc ++] = i;
      }
    }

    Int cnt[MAX_N];
    Int used[MAX_N];
    Int sum[MAX_N];
    bool is_p[MAX_N];
    Int p[MAX_N];
    Int pc;
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N ) ) {
        return false;
      }
      for ( int i = 0; i < in->N; ++ i ) {
        std::cin >> in->A[i];
      }
      std::cin >> in->M;
      for ( int i = 0; i < in->M; ++ i ) {
        std::cin >> in->L[i] >> in->R[i];
      }
      return true;
    }

    void output( const OutputStorage* out ) {
      for ( int i = 0; i < out->M; ++ i ) {
        std::cout << out->results[i] << std::endl;
      }
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  static solution::InputStorage in;
  static solution::OutputStorage out;
  static solution::Storages storages;
  static solution::Solution solution;
  static solution::Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif

