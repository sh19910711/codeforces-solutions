
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
  typedef std::set<II> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  // storages
  int n;
  int m;
  int R[SIZE];
  int C[SIZE];

  Set B;
  Set remains;

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      result = calc_good_cells();
    }

    void normalize() {
      for ( int i = 0; i < m; ++ i ) {
        R[i] --;
        C[i] --;
      }
    }

    int calc_good_cells() {
      return all_cells() - banned_cells() - collisions();
    }

    int all_cells() {
      return ( n - 2 ) * 4;
    }

    int banned_cells() {
      for ( int i = 0; i < m; ++ i ) {
        ban_r(R[i]);
        ban_c(C[i]);
      }
      B.erase(II(0, 0));
      B.erase(II(0, n - 1));
      B.erase(II(n - 1, 0));
      B.erase(II(n - 1, n - 1));
      return B.size();
    }

    void ban_r( int x ) {
      B.insert(II(x, 0));
      B.insert(II(x, n - 1));
    }

    void ban_c( int x ) {
      B.insert(II(0, x));
      B.insert(II(n - 1, x));
    }

    int collisions() {
      for ( int i = 1; i < n - 1; ++ i ) {
        remains.insert(II(0, i));
        remains.insert(II(n - 1, i));
        remains.insert(II(i, 0));
        remains.insert(II(i, n - 1));
      }
      for ( Set::iterator it_i = B.begin(); it_i != B.end(); ++ it_i ) {
        remains.erase(*it_i);
      }

      int res = 0;
      for ( int i = 1; i < n - 1; ++ i ) {
        if ( remains.count(II(n - 1, i)) ) {
          cout << "check: " << n - 1 << ", " << i << endl;
          cout << i << ", " << n - 1 << endl;
          cout << i << ", " << n - i - 1 << endl;
          cout << i << ", " << 0 << endl;
          res += remove_remains(i, n - i - 1);
          res += remove_remains(0, i);
          res += remove_remains(i, 0);
        }
        if ( remains.count(II(i, n - 1)) ) {
          res += remove_remains(n - i - 1, i);
          res += remove_remains(0, i);
          res += remove_remains(i, 0);
        }
      }
      cout << endl;
      cout << "remains" << endl;
      for ( Set::iterator it_i = remains.begin(); it_i != remains.end(); ++ it_i ) {
        cout << (*it_i).first << ", " << (*it_i).second << endl;
      }
      cout << " -- " << endl;
      return res;
    }

    int remove_remains( int r, int c ) {
      if ( remains.count(II(r, c)) ) {
        remains.erase(II(r, c));
        return 1;
      }
      return 0;
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
      B.clear();
      remains.clear();
    }

    bool input() {
      if ( ! ( cin >> n >> m ) )
        return false;
      for ( int i = 0; i < m; ++ i ) {
        cin >> R[i] >> C[i];
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

