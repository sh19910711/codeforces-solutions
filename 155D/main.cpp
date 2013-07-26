
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
  typedef std::map<int, Set> Map;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int QUERIES = 100000 + 11;
  // storages
  int n, m;
  string S[QUERIES];
  int V[QUERIES];

  bool activates[SIZE];
  Map T;
  int P[SIZE][20];
  int PC[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      get_primes();
      for ( int i = 0; i < m; ++ i ) {
        if ( S[i] == "+" ) {
          query_activate(V[i]);
        } else {
          query_deactivate(V[i]);
        }
      }
    }

    void query_activate( int v ) {
      if ( activates[v] ) {
        cout << "Already on" << endl;
        return;
      }

      for ( int i = 0; i < PC[v]; ++ i ) {
        int p = P[v][i];
        if ( T[p].size() ) {
          cout << "Conflict with " << *T[p].begin() << endl;
          return;
        }
      }

      for ( int i = 0; i < PC[v]; ++ i ) {
        int p = P[v][i];
        T[p].insert(v);
      }

      cout << "Success" << endl;
      activates[v] = true;
    }

    void query_deactivate( int v ) {
      if ( ! activates[v] ) {
        cout << "Already off" << endl;
        return;
      }

      for ( int i = 0; i < PC[v]; ++ i ) {
        int p = P[v][i];
        T[p].erase(v);
      }

      cout << "Success" << endl;
      activates[v] = false;
    }

    void get_primes() {
      for ( int i = 2; i <= n; ++ i ) {
        int tmp = i;
        for ( int j = 2; j * j <= tmp; ++ j ) {
          if ( tmp % j ) {
            continue;
          }
          while ( tmp % j == 0 ) {
            tmp /= j;
          }
          P[i][PC[i] ++] = j;
        }
        if ( tmp > 1 ) {
          P[i][PC[i] ++] = tmp;
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
      std::fill(PC, PC + SIZE, 0);
      std::fill(activates, activates + SIZE, false);
      T.clear();
    }

    bool input() {
      if ( ! ( cin >> n >> m ) ) 
        return false;
      for ( int i = 0; i < m; ++ i ) {
        cin >> S[i] >> V[i];
      }
      return true;
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

