
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
  typedef std::set<int> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SECTORS = 1000 + 11;
  const int BRIDGES = 100000 + 11;
  const int P_SIZE = 10;
  // storages
  int n;
  int K[SECTORS];
  int* P[SECTORS];
  int bridges[BRIDGES];
  int bridges_num;

  int L[BRIDGES];
  int R[BRIDGES];

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      result = find_unstable_cells();
    }

    void normalize() {
      for ( int i = 0; i < n; ++ i ) {
        sort(P[i], P[i] + K[i]);
      }
    }

    int find_unstable_cells() {
      int res = 0;
      for ( int i = 0; i < n; ++ i ) {
        int prev = ( i - 1 + n ) % n;
        int next = ( i + 1 + n ) % n;
        for ( int j = 0; j < K[prev]; ++ j ) {
          L[j] = P[prev][j];
        }
        for ( int j = 0; j < K[next]; ++ j ) {
          R[j] = P[next][j];
        }

        for ( int j = 0; j + 1 < K[i]; ++ j ) {
          int a = P[i][j];
          int b = P[i][j + 1];
          int left_left = std::upper_bound(L, L + K[prev], a) - L;
          int left_right = std::upper_bound(L, L + K[prev], b) - L;
          int right_left = std::upper_bound(R, R + K[next], a) - R;
          int right_right = std::upper_bound(R, R + K[next], b) - R;
          int left_num = left_right - left_left;
          int right_num = right_right - right_left;
          if ( left_num != right_num ) {
            res ++;
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

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i ) {
        cin >> K[i];
        P[i] = bridges + bridges_num;
        for ( int j = 0; j < K[i]; ++ j ) {
          cin >> bridges[bridges_num ++];
        }
      }
      return true;
    }

    void output() {
      cout << result << endl;
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

