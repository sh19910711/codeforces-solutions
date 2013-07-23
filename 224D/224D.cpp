
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
  const string YES    = "Yes";
  const string NO     = "No";
  const int SIZE      = 2 * 100000 + 11;
  const int ALPHABETS = 26;
  const int NONE      = -1;

  // storages
  string s;
  string t;
  int ns;
  int nt;

  int L[SIZE];
  int R[SIZE];
  int dp[ALPHABETS][SIZE];

  bool result;

}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      ns = s.size();
      nt = t.size();
      result = check_subsequence();
    }

    bool check_subsequence() {
      if ( is_invalid_case() )
        return false;

      for ( int i = 1; i <= ns; ++ i ) {
        int tp = L[i - 1];
        if ( tp == NONE ) {
          tp = 1;
          L[i] = ( s[i - 1] == t[tp - 1] ? 1 : NONE );
        } else {
          L[i] = min(nt, tp + ( s[i - 1] == t[tp] ? 1 : 0 ));
        }
      }

      for ( int i = ns; i >= 1; -- i ) {
        int tp = R[i + 1];
        if ( tp == NONE ) {
          tp = nt;
          R[i] = ( s[i - 1] == t[tp - 1] ? nt : NONE );
        } else {
          int ti = max(0, tp - 2);
          R[i] = max(1, tp - ( s[i - 1] == t[ti] ? 1 : 0 ));
        }
      }

      for ( char c = 'a'; c <= 'z'; ++ c ) {
        int ind = c - 'a';
        dp[ind][0] = 0;
        for ( int j = 1; j <= nt; ++ j ) {
          int ti = j - 1;
          dp[ind][j] = dp[ind][j - 1] + ( c == t[ti] ? 1 : 0 );
        }
      }

      for ( int i = 1; i <= ns; ++ i ) {
        int r = L[i];
        int l = R[i];
        if ( l > r )
          return false;
        if ( r == NONE )
          return false;
        if ( l == NONE )
          return false;
        char c = s[i - 1];
        int ind = c - 'a';
        if ( dp[ind][r] - dp[ind][l - 1] == 0 )
          return false;
      }

      return true;
    }

    bool is_invalid_case() {
      set <char> used;
      for ( string::iterator it_i = t.begin(); it_i != t.end(); ++ it_i ) {
        used.insert(*it_i);
      }
      for ( string::iterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
        if ( ! used.count(*it_i) ) {
          return true;
        }
      }
      return false;
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
      std::fill(L, L + SIZE, NONE);
      std::fill(R, R + SIZE, NONE);
      for ( int i = 0; i < ALPHABETS; ++ i )
        std::fill(dp[i], dp[i] + SIZE, 0);
    }

    bool input() {
      return cin >> s >> t;
    }

    void output() {
      cout << ( result ? YES : NO ) << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

