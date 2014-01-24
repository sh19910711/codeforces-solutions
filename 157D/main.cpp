
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

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual int run() = 0;
    
  protected:
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      pre_calc();
      while ( action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef std::vector<std::string> VS;
  typedef long long LL;
  typedef int INT;
  typedef std::vector<INT> VI;
  typedef std::vector<VI> VVI;
  typedef std::pair<INT,INT> II;
  typedef std::vector<II> VII;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE                = 100000 + 11;
  const int RESULT_LIE          = 0;
  const int RESULT_TRUTH        = 1;
  const int RESULT_NOT_DEFINED  = 2;
  const string TEXT_TRUTH       = "Truth";
  const string TEXT_LIE         = "Lie";
  const string TEXT_NOT_DEFINED = "Not defined";

  // storages
  int n, m;
  int A[SIZE];

  int suspect[SIZE];
  int not_suspect[SIZE];
  int guardmans;
  int attackers;
  bool is_committer[SIZE];
  int committers;

  int result[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      calc_suspect();
      calc_not_suspect();
      guardmans = calc_guardmans();
      attackers = calc_attackers();
      check_committers();
      committers = calc_committers();

      for ( int i = 0; i < n; ++ i ) {
        result[i] = check_result(i);
      }
    }

    int check_result( int k ) {
      if ( A[k] > 0 ) {
        if ( is_committer[A[k] - 1] ) {
          if ( committers == 1 ) {
            return RESULT_TRUTH;
          } else {
            return RESULT_NOT_DEFINED;
          }
        }
      } else {
        if ( ! is_committer[abs(A[k]) - 1] ) {
          return RESULT_TRUTH;
        } else {
          if ( committers != 1 ) {
            return RESULT_NOT_DEFINED;
          }
        }
      }
      return RESULT_LIE;
    }

    int calc_committers() {
      return std::count(is_committer, is_committer + n, true);
    }

    void check_committers() {
      for ( int i = 0; i < n; ++ i ) {
        int ret = guardmans - not_suspect[i] + suspect[i];
        is_committer[i] = ( ret == m );
      }
    }

    int calc_guardmans() {
      int res = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( A[i] < 0 ) {
          res ++;
        }
      }
      return res;
    }

    int calc_attackers() {
      int res = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( A[i] > 0 ) {
          res ++;
        }
      }
      return res;
    }

    void calc_suspect() {
      for ( int i = 0; i < n; ++ i ) {
        if ( A[i] > 0 ) {
          suspect[A[i] - 1] ++;
        }
      }
    }

    void calc_not_suspect() {
      for ( int i = 0; i < n; ++ i ) {
        if ( A[i] < 0 ) {
          not_suspect[abs(A[i]) - 1] ++;
        }
      }
    }

    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }

    void init() {
      std::fill(suspect, suspect + SIZE, 0);
      std::fill(not_suspect, not_suspect + SIZE, 0);
    }

    bool input() {
      if ( ! ( cin >> n >> m ) )
        return false;
      for ( int i = 0; i < n; ++ i ) {
        cin >> A[i];
      }
      return true;
    }

    void output() {
      for ( int i = 0; i < n; ++ i ) {
        if ( result[i] == RESULT_LIE ) {
          cout << TEXT_LIE << endl;
        } else if ( result[i] == RESULT_TRUTH ) {
          cout << TEXT_TRUTH << endl;
        } else if ( result[i] == RESULT_NOT_DEFINED ) {
          cout << TEXT_NOT_DEFINED << endl;
        }
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif


