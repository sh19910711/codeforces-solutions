
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
  typedef std::map<int, int> Map;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int INF = std::numeric_limits<int>::max();
  const int IMPOSSIBLE = -1;
  // storages
  int n;
  int A[SIZE];
  int B[SIZE];

  Map cnt;

  int good_values[4];
  int good_values_num;

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      count_values();
      find_good_values();
      result = find_minimum_flips();
    }

    void find_good_values() {
      for ( Map::reverse_iterator it_i = cnt.rbegin(); it_i != cnt.rend(); ++ it_i ) {
        std::pair<const int, int> p = *it_i;
        if ( p.second >= (int)ceil((double)n / 2) ) {
          good_values[good_values_num ++] = p.first;
        }
      }
    }

    void count_values() {
      for ( int i = 0; i < n; ++ i ) {
        int a = A[i];
        int b = B[i];
        if ( a == b ) {
          cnt[a] ++; 
        } else {
          cnt[a] ++;
          cnt[b] ++;
        }
      }
    }

    int find_minimum_flips() {
      int res = INF;
      for ( int i = 0; i < good_values_num; ++ i ) {
        int value = good_values[i];
        res = min(res, calc_flips(value));
      }
      return res;
    }

    int calc_flips( int value ) {
      int num = 0;
      int res = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( A[i] == value ) {
          num ++;
        }
      }
      for ( int i = 0; i < n; ++ i ) {
        if ( A[i] == value ) {
          continue;
        }
        if ( num < (int)ceil((double)n / 2) ) {
          if ( B[i] == value ) {
            num ++;
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

    void init() {
      good_values_num = 0;
      cnt.clear();
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i ) {
        cin >> A[i] >> B[i];
      }
      return true;
    }

    void output() {
      if ( result == INF ) {
        cout << IMPOSSIBLE << endl;
      } else {
        cout << result << endl;
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

