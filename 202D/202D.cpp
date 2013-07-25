
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
  const int SIZE = 1000 + 11;
  const LL INF = std::numeric_limits<LL>::max();
  // storages
  int h, w;
  LL cost[SIZE][SIZE];

  LL R_sum[SIZE];
  LL C_sum[SIZE];
  LL R_t[SIZE];
  LL C_t[SIZE];

  LL result;
  int r, c;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      get_sum();
      get_time();
      result = find_minimum_steps();
    }

    void get_time() {
      for ( int i = 0; i < w; ++ i ) {
        for ( int j = 0; j < w; ++ j ) {
          R_t[i] += get_dist( 4 * ( i + 1 ) + 2 - 4 * ( j + 1 ) ) * R_sum[j];
        }
      }
      for ( int i = 0; i < h; ++ i ) {
        for ( int j = 0; j < h; ++ j ) {
          C_t[i] += get_dist(4 * ( i + 1 ) + 2 - 4 * ( j + 1 ) ) * C_sum[j];
        }
      }
    }

    LL sq( LL x ) {
      return x * x;
    }

    LL get_dist( LL diff ) {
      return sq(diff);
    }

    void get_sum() {
      for ( int i = 0; i < w; ++ i ) {
        for ( int j = 0; j < h; ++ j ) {
          R_sum[i] += cost[j][i];
        }
      }
      for ( int i = 0; i < h; ++ i ) {
        for ( int j = 0; j < w; ++ j ) {
          C_sum[i] += cost[i][j];
        }
      }
    }

    LL find_minimum_steps() {
      LL res = INF;
      for ( int i = 0; i < h; ++ i ) {
        for ( int j = 0; j < w; ++ j ) {
          LL sum = C_t[i] + R_t[j];
          if ( sum < res ) {
            r = i;
            c = j;
            res = sum;
          }
        }
      }
      return res;
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
      result = INF;
      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j < SIZE; ++ j ) {
          cost[i][j] = 0LL;
        }
      }
      std::fill(R_sum, R_sum + SIZE, 0LL);
      std::fill(C_sum, C_sum + SIZE, 0LL);
      std::fill(R_t, R_t + SIZE, 0LL);
      std::fill(C_t, C_t + SIZE, 0LL);
    }

    bool input() {
      if ( ! ( cin >> h >> w ) )
        return false;
      for ( int i = 1; i <= h; ++ i ) {
        for ( int j = 1; j <= w; ++ j ) {
          cin >> cost[i][j];
        }
      }
      h += 2;
      w += 2;
      return true;
    }

    void output() {
      cout << result << endl;
      cout << r << " " << c << endl;
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

