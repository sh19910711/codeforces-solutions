
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
  typedef double Double;
  typedef std::pair<Double, std::pair<LL, LL> > Entry;
  typedef std::set<std::pair<LL, LL> > Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  // storages
  int n;
  LL X[SIZE];
  LL B[SIZE];

  Entry entries[SIZE];
  Set s;
  LL x_sum;
  LL b_sum;

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      std::sort(entries, entries + n);
      calc_sum();
      result = get_angles();
    }

    void calc_sum() {
      x_sum = std::accumulate(X, X + n, 0LL);
      b_sum = std::accumulate(B, B + n, 0LL);
    }

    void normalize() {
      for ( int i = 0; i < n; ++ i ) {
        Double m;
        if ( X[i] != 0 ) {
          m = -(Double)B[i] / X[i];
        } else {
          m = 0;
        }
        entries[i] = std::make_pair(m, std::make_pair(X[i], B[i]));
      }
    }

    int get_angles() {
      for ( int i = 0; i < n; ++ i ) {
        if ( X[i] != 0 ) {
          s.insert(std::make_pair(x_sum, b_sum));
        }
        x_sum -= entries[i].second.first;
        b_sum -= entries[i].second.second;
      }
      return s.size();
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
      s.clear();
      result = 0;
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i ) {
        cin >> X[i] >> B[i];
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

