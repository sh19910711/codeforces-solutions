
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
  int K0, K1;
  int K[P_SIZE];
  int P0[BRIDGES];
  int P1[BRIDGES];
  int P[P_SIZE][BRIDGES];
  int P_offset;

  int L[BRIDGES];
  int R[BRIDGES];

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = find_unstable_cells();
    }

    int find_unstable_cells() {
      int res = 0;
      for ( int t = 0; t < n; ++ t ) {
        cin >> K[P_offset];
        for ( int i = 0; i < K[P_offset]; ++ i ) {
          cin >> P[P_offset][i];
        }

        if ( t == 0 ) {
          K0 = K[P_offset];
          for ( int i = 0; i < K0; ++ i ) {
            P0[i] = P[P_offset][i];
          }
        }

        if ( t == 1 ) {
          K1 = K[P_offset];
          for ( int i = 0; i < K1; ++ i ) {
            P1[i] = P[P_offset][i];
          }
        }

        if ( t > 0 && t < n - 1 ) {
          int prev = ( P_offset - 1 + P_SIZE ) % P_SIZE;
          int next = ( P_offset + 1 ) % P_SIZE;
          for ( int i = 0; i < n; ++ i ) {
            for ( int j = 0; j < K[prev]; ++ j ) {
              L[j] = P[prev][j];
            }
            for ( int j = 0; j < K[next]; ++ j ) {
              R[j] = P[next][j];
            }
          }
          sort(L, L + K[prev]);
          sort(R, R + K[next]);

          for ( int i = 0; i + 1 < K[P_offset]; ++ i ) {
            int a = P[P_offset][i];
            int b = P[P_offset][i + 1];
            int left_left   = std::upper_bound(L, L + K[prev], a) - L;
            int left_right  = std::upper_bound(L, L + K[prev], b) - L;
            int right_left  = std::upper_bound(R, R + K[next], a) - R;
            int right_right = std::upper_bound(R, R + K[next], b) - R;
            int left_num    = max(0, left_right - left_left);
            int right_num   = max(0, right_right - right_left);
            if ( left_num != right_num ) {
              res ++;
            }
          }
        }

        P_offset = ( P_offset + 1 ) % P_SIZE;
      }

      K[P_offset] = K0;
      for ( int i = 0; i < K0; ++ i ) {
        P[P_offset][i] = P0[i];
      }
      P_offset = ( P_offset + 1 + P_SIZE ) % P_SIZE;

      K[P_offset] = K1;
      for ( int i = 0; i < K1; ++ i ) {
        P[P_offset][i] = P1[i];
      }
      P_offset = ( P_offset + 1 + P_SIZE ) % P_SIZE;

      P_offset = ( P_offset - 3 + P_SIZE ) % P_SIZE;
      for ( int t = 0; t < 2; ++ t ) {
        int prev = ( P_offset - 1 + P_SIZE ) % P_SIZE;
        int next = ( P_offset + 1 ) % P_SIZE;
        for ( int i = 0; i < n; ++ i ) {
          for ( int j = 0; j < K[prev]; ++ j ) {
            L[j] = P[prev][j];
          }
          for ( int j = 0; j < K[next]; ++ j ) {
            R[j] = P[next][j];
          }
        }
        sort(L, L + K[prev]);
        sort(R, R + K[next]);

        for ( int i = 0; i + 1 < K[P_offset]; ++ i ) {
          int a = P[P_offset][i];
          int b = P[P_offset][i + 1];
          int left_left   = std::upper_bound(L, L + K[prev], a) - L;
          int left_right  = std::upper_bound(L, L + K[prev], b) - L;
          int right_left  = std::upper_bound(R, R + K[next], a) - R;
          int right_right = std::upper_bound(R, R + K[next], b) - R;
          int left_num    = max(0, left_right - left_left);
          int right_num   = max(0, right_right - right_left);
          if ( left_num != right_num ) {
            res ++;
          }
        }

        P_offset = ( P_offset + 1 ) % P_SIZE;
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

