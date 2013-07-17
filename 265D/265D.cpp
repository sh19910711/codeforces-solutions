
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
  typedef set<int, less<int> > Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  // storages
  int n;
  int A[SIZE];

  Set P[SIZE];
  Set belongs_to[SIZE];
  int L[SIZE];

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_maximum_length();
    }

    int get_maximum_length() {

      for ( int i = 0; i < n; ++ i ) {
        int a = A[i];
        int t = a;
        for ( int j = 2; j * j <= a; ++ j ) {
          while ( t % j == 0 ) {
            P[i].insert(j);
            t /= j;
          }
        }
        if ( t >= 2 )
          P[i].insert(t);
      }

      for ( int i = 0; i < n; ++ i ) {
        for ( Set::iterator it_j = P[i].begin(); it_j != P[i].end(); ++ it_j ) {
          int prime = *it_j;
          belongs_to[prime].insert(A[i]);
        }
      }

      for ( int i = n - 1; i >= 0; -- i ) {
        int len = 1;
        int a = A[i];
        for ( Set::iterator it_j = P[i].begin(); it_j != P[i].end(); ++ it_j ) {
          int prime = *it_j;
          Set::iterator it_next = belongs_to[prime].upper_bound(a);
          if ( it_next != belongs_to[prime].end() ) {
            int next_value = *it_next;
            len = max(len, L[next_value] + 1);
          }
        }
        L[a] = len;
      }

      return *max_element(L, L + SIZE);
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
      fill(L, L + SIZE, 0);
      for ( int i = 0; i < SIZE; ++ i )
        P[i].clear();
      for ( int i = 0; i < SIZE; ++ i )
        belongs_to[i].clear();
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

