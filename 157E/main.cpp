
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
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base-queries.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    int queries;
    virtual ~SolutionBase() {};
    virtual bool input_query( InputStorage* in ) = 0;
    virtual bool action() {
      if ( ! this->input(this->storages->in) )
        return false;
      for ( int i = 0; i < queries; ++ i ) {
        this->input_query(this->storages->in);
        this->output(this->solver->solve(this->storages->in, this->storages->out));
      }
      return true;
    }
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
  const Int SIZE = 100 + 11;
  const Int MAX_SUM = SIZE * 26;
  const Int MOD = 1000000007LL;
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorageMembers {
    Int T;
    std::string S;
  };
  
  struct OutputStorageMembers {
    Int result;
  };
  
  struct InputStorage: InputStorageMembers {
    InputStorage() {}
    InputStorage( const InputStorage* p ) { InputStorage* self = this; *self = *p; }
  };
  
  struct OutputStorage: OutputStorageMembers {
    OutputStorage() {}
    OutputStorage( const OutputStorage* p ) { OutputStorage* self = this; *self = *p; }
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Solver: SolverInterface {
    Int C[SIZE][MAX_SUM];

    Solver() {
      for ( auto l : C )
        std::fill(l, l + MAX_SUM, 0);
      C[0][0] = 1;
      for ( auto i = 0; i + 1 < SIZE; ++ i ) {
        for ( auto j = MAX_SUM - 1; j >= 0; -- j ) {
          for ( auto k = 0; k < 26 && j + k < MAX_SUM; ++ k ) {
            Int& next_cnt = C[i + 1][j + k];
            next_cnt += C[i][j];
            next_cnt %= MOD;
          }
        }
      }
    }

    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      int n = in->S.size();
      int sum = 0;
      for ( auto i = 0; i < n; ++ i ) {
        sum += in->S[i] - 'a';
      }
      out->result = ( C[n][sum] - 1 + MOD ) % MOD;
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    Solution() {
    }

    bool input_query( InputStorage* in ) {
      return std::cin >> in->S;
    }

    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->T ) )
        return false;
      this->queries = in->T;
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


