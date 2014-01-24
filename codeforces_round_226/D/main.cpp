
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
  const int SIZE = 20 + 1;
  const int BIT_SIZE = 1 << SIZE;
  
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int L;
    Int R;
    Int X[SIZE];
    Int Y[SIZE];
    Int A[SIZE];
  };
  struct OutputStorage {
    Double result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  class Search {
  public:
    const InputStorage* in;
    Double dp[BIT_SIZE];

    Double run() {
      Double L = in->L;
      Double R = in->R;
      std::fill(dp, dp + BIT_SIZE, L);
      Int n = in->N;
      Int bit_n = 1 << n;
      for ( Int s = 0; s < bit_n; ++ s ) {
        for ( Int lid = 0; lid < n; ++ lid ) {
          if ( is_visited(s, lid) )
            continue;

          Int next_s = s | ( 1 << lid );
          Double x = in->X[lid];
          Double y = in->Y[lid];
          Double sx = dp[s];
          if ( std::abs(x - sx) <= 1e-5 ) {
            dp[next_s] = std::numeric_limits<int>::max();
          } else {
            Double a = (Double)in->A[lid] * M_PI / 180.0;
            Double b = std::atan2(sx - x, y);
            Double tx = y * tan(a + b) + x;

            Int next_s = s | ( 1 << lid );
            dp[next_s] = std::max(dp[next_s], tx);
          }
        }
      }
      return std::min(R - L, *std::max_element(dp, dp + BIT_SIZE) - L);
    }

    bool is_visited( Int s, Int id ) {
      return s & ( 1 << id );
    }
  };

  class Solver: public SolverInterface {
  public:
    Search search;
  public:
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      search.in = in;
      out->result = search.run();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->L >> in->R ) )
        return false;
      for ( int i = 0; i < in->N; ++ i )
        std::cin >> in->X[i] >> in->Y[i] >> in->A[i];
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << std::setprecision(15) << out->result << std::endl;
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

