
// @snippet<sh19910711/contest:headers.cpp>
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

// @snippet<sh19910711/contest:solution/define_classes.cpp>
namespace solution {
  class Solution;
  class Solver;
  struct InputStorage;
  struct OutputStorage;
  struct DataStorage;
  class Storages;
}

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    
  protected:
    SolutionInterface() {}
    virtual bool action() = 0;
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) const {}
    virtual void after_action( const int& test_no ) const {}
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}
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
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::set<Int> Set;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int A[SIZE];
  };
  
  struct OutputStorage {
    Int N;
    Set results;
  };
  
  struct DataStorage {
    Int A[SIZE];
  };
  
  struct Storages {
    InputStorage  in;
    OutputStorage out;
    DataStorage   data;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      out.N = in.N;
      std::copy(in.A, in.A + in.N, data.A);
      std::sort(data.A, data.A + in.N);
      out.results = find_numbers(in.N, data.A);
      out.results = format_results(in.N, data.A, out.results);
      return out;
    }
    
  protected:
    static Set format_results( const Int& N, const Int A[SIZE], Set results ) {
      Int B[SIZE];
      Set res;
      for ( Set::iterator it_i = results.begin(); it_i != results.end(); ++ it_i ) {
        std::copy(A, A + N, B);
        B[N] = *it_i;
        std::sort(B, B + N + 1);
        if ( is_ok(N + 1, B) ) {
          res.insert(*it_i);
        }
      }
      return res;
    }

    static Set find_numbers( const Int& N, const Int A[SIZE] ) {
      if ( ! is_ok(N, A) && is_dup(N, A) ) {
        return Set();
      }

      if ( N == 1 ) {
        return Set();
      }

      Set res;
      if ( is_ok(N, A) ) {
        Int diff = A[1] - A[0];
        res.insert(A[0] - diff);
        res.insert(A[N - 1] + diff);
      }

      for ( int i = 0; i + 1 < N; ++ i ) {
        res.insert(A[i] + ( A[i + 1] - A[i] ) / 2);
        res.insert(A[i] - ( A[i + 1] - A[i] ) / 2);
      }

      return res;
    }

    static bool is_ok( const Int& A, const Int& B, const Int& C ) {
      return B - A == C - B;
    }

    static bool is_dup( const Int& N, const Int A[SIZE] ) {
      if ( N <= 1 ) {
        return false;
      }
      for ( int i = 0; i + 1 < N; ++ i ) {
        if ( A[i] == A[i + 1] ) {
          return true;
        }
      }
      return false;
    }

    static bool is_ok( const Int& N, const Int A[SIZE] ) {
      if ( N <= 2 ) {
        return true;
      }
      Int diff = A[1] - A[0];
      for ( int i = 0; i + 1 < N; ++ i ) {
        if ( A[i + 1] - A[i] != diff ) {
          return false;
        }
      }
      return true;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {}
    Solution(Storages* p): storages(p) {}
    
  protected:
    virtual bool action() {
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      if ( ! ( std::cin >> in.N ) ) {
        return false;
      }
      for ( int i = 0; i < in.N; ++ i ) {
        std::cin >> in.A[i];
      }
      return true;
    }

    void output( const OutputStorage& out ) const {
      if ( out.N <= 1 ) {
        std::cout << -1 << std::endl;
      } else {
        std::cout << out.results.size() << std::endl;
        for ( Set::iterator it_i = out.results.begin(); it_i != out.results.end(); ++ it_i ) {
          std::cout << *it_i << " ";
        }
        std::cout << std::endl;
      }
    }
    
  private:
    Solver solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif

