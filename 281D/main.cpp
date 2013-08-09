
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
  typedef std::map <int, int> Map;
  typedef std::set <int, std::greater<int> > Set;
  typedef std::set <int, std::less<int> > SetRev;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  // storages
  int n;
  int A[SIZE];

  Map pos_to_value;
  Map value_to_pos;
  Set pos;
  SetRev pos_rev;

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      sort_a();
      result = find_maximum_xor();
    }

    int find_maximum_xor() {
      int res = 0;
      for ( int i = 0; i < n; ++ i ) {
        int v = A[i];
        int p = value_to_pos[v];
        Set::iterator it_before = pos.upper_bound(p);
        SetRev::iterator it_after = pos_rev.upper_bound(p);
        if ( it_before != pos.end() ) {
          int gv = pos_to_value[*it_before];
          res = max(res, v ^ gv);
        }
        if ( it_after != pos_rev.end() ) {
          int gv = pos_to_value[*it_after];
          res = max(res, v ^ gv);
        }

        pos.insert(p);
        pos_rev.insert(p);
      }
      return res;
    }

    void sort_a() {
      std::sort(A, A + n, std::greater<int>());
    }

    void normalize() {
      for ( int i = 0; i < n; ++ i ) {
        pos_to_value[i] = A[i];
        value_to_pos[A[i]] = i;
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
      pos_to_value.clear();
      value_to_pos.clear();
      pos.clear();
      pos_rev.clear();
      result = 0;
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> A[i];
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

