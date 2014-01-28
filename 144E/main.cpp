
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

#include <array>

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 100000 + 11;
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::tuple <Int, Int, Int> Person;
  typedef std::set <Person> Set;
  typedef std::array <Set, SIZE> Sets;
  typedef std::array <Int, SIZE> IntArray;
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int M;
    Set S;
  };
  struct OutputStorage {
    Int AC;
    IntArray A;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Solver: SolverInterface {
    Sets S;

    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->AC = 0;
      generate_sets(in->S);
      find_solution(in->N, out->A, out->AC);
      return out;
    }

    void find_solution( const Int& N, IntArray& A, Int& AC ) {
      Set tmp;
      for ( Int r = N; r >= 1; -- r ) {
        for ( auto p : S[r] )
          tmp.insert(p);
        while ( ! tmp.empty() ) {
          auto p = *tmp.begin();
          tmp.erase(p);
          // cout << get<0>(p) << ", " << get<1>(p) << ", " << get<2>(p) << endl;
          if ( std::get<0>(p) >= N - r ) {
            A[AC ++] = std::get<2>(p);
            break;
          }
        }
      }
    }

    void generate_sets( const Set& s ) {
      std::for_each(begin(S), end(S), []( Set& a ){ a.clear(); });
      for ( auto p : s ) {
        S[std::get<0>(p)].insert(p);
      }
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->M ) )
        return false;
      for ( int i = 0; i < in->M; ++ i ) {
        Person p;
        std::cin >> std::get<1>(p) >> std::get<0>(p);
        std::get<2>(p) = i + 1;
        in->S.insert(p);
      }
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << out->AC << std::endl;
      for ( auto i = 0; i < out->AC; ++ i ) {
        std::cout << out->A[i] << " ";
      }
      std::cout << endl;
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

