
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
  class ISolution {
  public:
    virtual int run() = 0;
    
  protected:
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public ISolution {
  public:
    virtual int run() {
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
  typedef set<int> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int NONE = -1;
  // storages
  int n;
  int A[SIZE];

  Set deads;
  int prev[SIZE];
  int next[SIZE];

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_steps();
    }

    int get_steps() {
      for ( int i = n; i < 2 * n; ++ i )
        deads.insert(i);

      for ( int i = 0; i < n; ++ i ) {
        prev[i] = i - 1;
        next[i] = i + 1;
      }

      VI current;
      for ( int i = 1; i < n; ++ i )
        current.push_back(i);

      for ( int t = 0; t < SIZE; ++ t ) {

        VI cand;
        for ( VI::iterator it_i = current.begin(); it_i != current.end(); ++ it_i ) {
          // a, b
          int k = *it_i;
          int a = A[prev[k]];
          int b = A[k];
          if ( a > b ) {
            deads.insert(k);
            cand.push_back(k);
          }
        }

        if ( cand.empty() )
          return t;

        VI next_current;
        for ( VI::iterator it_i = cand.begin(); it_i != cand.end(); ++ it_i ) {
          // a, b, c => a, c]
          int k = *it_i;
          int a = prev[k];
          int c = next[k];
          next[a] = c;
          prev[c] = a;

          // x, x, o, -> o
          if ( ! deads.count(c) )
            next_current.push_back(c);
        }

        current = next_current;
      }

      return -3;
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
      deads.clear();
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
int main() {
  return solution::Solution().run();
}

