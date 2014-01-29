
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

namespace math {
  template <int SIZE, long long MOD = 1000000007LL> struct ModFact {
    long long data[SIZE];
    ModFact() {
      data[0] = data[1] = 1;
      for ( int i = 2; i < SIZE; ++ i ) {
        data[i] = data[i - 1] * i;
        data[i] %= MOD;
      }
    }
  };
}

#include <array>

// @snippet<sh19910711/contest:math/extgcd.cpp>
namespace math {
  template <class T> T extgcd( T a, T b, T& x, T& y ) {
    for ( T u = y = 1, v = x = 0; a; ) {
      T q = b / a;
      std::swap( x -= q * u, u );
      std::swap( y -= q * v, v );
      std::swap( b -= q * a, a );
    }
    return b;
  }
}

// @snippet<sh19910711/contest:math/mod_inverse.cpp>
namespace math {
  // @desc mod mでaの逆元を求める
  template <class T> T mod_inverse( T a, T m ) {
    T x, y;
    extgcd( a, m, x, y );
    x %= m;
    while ( x < 0 )
      x += m;
    return x;
  }
}

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/constants.cpp>
namespace solution {
  // constants
  const Int MOD = 1000000007LL;
  const Int SIZE = 100000 + 11;
  const Int MAX_LUCKY_NUMBERS = 1022 + 11;
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef math::ModFact<SIZE> ModFact;
  typedef std::array<Int, SIZE> Seq;
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int K;
    Seq A;
  };
  struct OutputStorage {
    Int result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  struct Calc {
    typedef std::array<std::array<Int, MAX_LUCKY_NUMBERS>, MAX_LUCKY_NUMBERS> Table;
    typedef std::array<bool, SIZE> Flags;
    
    Int K;
    Int NA;
    Seq A;
    Table cnt;
    Flags is_lucky;
    Int unlucky;
    
    Int NB;
    Seq B; // lucky only
    Seq BC;
    
    ModFact mod_fact;
    
    Int run( const InputStorage* in ) {
      K = in->K;
      NA = in->N;
      A = in->A;
      
      std::sort(begin(A), begin(A) + NA);
      
      std::fill(begin(is_lucky), end(is_lucky), false);
      for ( auto i = 0; i < NA; ++ i )
        if ( check_lucky(A[i]) )
          is_lucky[i] = true;
      unlucky = 0;
      for ( auto i = 0; i < NA; ++ i )
        if ( ! is_lucky[i] )
          unlucky += 1;
      
      NB = 0;
      for ( auto i = 0; i < NA; ++ i ) {
        if ( check_lucky(A[i]) ) {
          auto b_id = NB ++;
          B[b_id]  = A[i];
          BC[b_id] = 1;
          if ( i + 1 < NA && A[i] == A[i + 1] ) {
            auto j = i + 1;
            for ( ; j < NA; ++ j ) {
              if ( A[i] == A[j] ) {
                BC[b_id] ++;
              } else {
                break;
              }
            }
            i = j - 1;
          }
        }
      }
      NB = std::distance(begin(B), std::unique(begin(B), begin(B) + NB));
      
      // count lucky only lucky seq
      for ( int i = 0; i < MAX_LUCKY_NUMBERS; ++ i ) {
        std::fill(begin(cnt[i]), end(cnt[i]), 0);
      }
      cnt[0][0] = 1;
      for ( auto i = 0; i < NB; ++ i ) {
        for ( auto j = 0; j <= i; ++ j ) {
          cnt[i + 1][j + 1] += ( cnt[i][j] * BC[i] ) % MOD;
          cnt[i + 1][j + 1] %= MOD;
          cnt[i + 1][j + 0] += cnt[i][j];
          cnt[i + 1][j + 0] %= MOD;
        }
      }
      
      Int res = 0;
      if ( unlucky >= K ) {
        res += calc_comb(unlucky, K);
        res %= MOD;
      }
      for ( auto i = 1; i <= K; ++ i ) {
        if ( unlucky >= K - i ) {
          res += cnt[NB][i] * calc_comb(unlucky, K - i);
          res %= MOD;
        }
      }

      return res % MOD;
    }
    
    Int calc_comb( const Int& N, const Int& R ) {
      if ( N == 0 || R == 0 || N == R )
        return 1;
      Int res = mod_fact.data[N] * math::mod_inverse(mod_fact.data[R], MOD);
      res %= MOD;
      res *= math::mod_inverse(mod_fact.data[N - R], MOD);
      res %= MOD;
      return res;
    }
    
    static bool check_lucky( const Int& x ) {
      Int tmp = x;
      while ( tmp > 0 ) {
        Int digit = tmp % 10;
        if ( digit != 4 && digit != 7 )
          return false;
        tmp /= 10;
      }
      return true;
    }
  };
  
  struct Solver: SolverInterface {
    Calc calc;
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->result = calc.run(in);
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->K ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        std::cin >> in->A[i];
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



