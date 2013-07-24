
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
  const int SIZE = 1000000 + 11;
  const int INF = std::numeric_limits<int>::max();
  const string NONE = "IMPOSSIBLE";
  // storages
  int n;
  int r;

  int mistakes;
  string result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      mistakes = find_min_mistakes();
    }

    int find_min_mistakes() {
      int min_mistakes = INF;
      int min_x;
      for ( int x = 1; x < r; ++ x ) {
        int ret = calc_mistakes(x, r);
        if ( ret < min_mistakes ) {
          min_mistakes = ret;
          min_x = x;
        }
      }

      if ( min_mistakes != INF ) {
        generate_result(min_x, r);
      }

      return min_mistakes;
    }

    int calc_mistakes( int a, int b ) {
      int res = 0;
      int operations = 0;

      while ( a > 0 ) {
        int num = b / a;
        res += num - 1;
        operations += num;
        b %= a;
        swap(a, b);
      }

      if ( operations != n )
        return INF;
      return a == 0 && b == 1 ? res - 1 : INF;
    }

    void generate_result( int a, int b ) {
      bool top = true;
      result = "";
      while ( a > 0 ) {
        if ( a == 1 ) {
          int num = b - 1;
          result += string(num, top ? 'T' : 'B') + "B";
          top = ! top;
          b %= a;
          swap(a, b);
          break;
        } else {
          int num = b / a;
          result += string(num, top ? 'T' : 'B');
          top = ! top;
          b %= a;
          swap(a, b);
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
      mistakes = 0;
      result = NONE;
    }

    bool input() {
      return cin >> n >> r;
    }

    void output() {
      if ( result == NONE ) {
        cout << result << endl;
      } else {
        cout << mistakes << endl;
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

