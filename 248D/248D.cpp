
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
  const int SIZE = 5 * 100000 + 11;
  const LL INF = std::numeric_limits<LL>::max() / 3;

  const char CHAR_EMPTY = '.';
  const char CHAR_SHOP  = 'S';
  const char CHAR_HOUSE = 'H';

  // storages
  int n;
  int t;
  string s;

  LL result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = get_minimum_k();
    }

    LL get_minimum_k() {
      LL lb = -1;
      LL ub = INF;

      while ( ub - lb > 1 ) {
        LL mid = ( lb + ub ) / 2LL;
        if ( check(mid) ) {
          ub = mid;
        } else {
          lb = mid;
        }
      }

      return ub;
    }

    bool check( LL k ) {
      LL ret1 = get_minimum_cost(k);
      return ret1 <= t;
    }

    LL get_minimum_cost( LL k ) {
      LL res = 0;
      std::stack<int> st;
      LL remains = k;
      std::vector<II> ranges;
      LL last = -1;

      for ( int i = 0; i < n; ++ i ) {
        if ( s[i] == CHAR_EMPTY ) {
          continue;
        } else if ( s[i] == CHAR_HOUSE ) {
          last = i;
          if ( remains > 0 ) {
            remains --;
          } else {
            st.push(i);
          }
        } else if ( s[i] == CHAR_SHOP ) {
          if ( st.empty() ) {
            remains ++;
          } else {
            if ( st.size() == 1 ) {
              int l = st.top();
              int r = i;
              ranges.push_back(II(l, r));
            }
            last = i;
            st.pop();
          }
        }
      }

      if ( ! st.empty() )
        return INF;

      res = last + 1;
      for ( std::vector<II>::iterator it_i = ranges.begin(); it_i != ranges.end(); ++ it_i ) {
        II range = *it_i;
        res += ( range.second - range.first ) * 2;
      }

      LL tmp = res;
      ranges.push_back(II(last, last));
      for ( std::vector<II>::reverse_iterator it_i = ranges.rbegin() + 1; it_i != ranges.rend(); ++ it_i ) {
        II range = *it_i;
        II prev_range = *(it_i - 1);
        tmp -= range.second - range.first;
        tmp += prev_range.first - range.second;
        res = min(res, tmp);
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
      if ( ! ( cin >> n >> t ) )
        return false;
      return cin >> s;
    }

    void output() {
      if ( result == INF ) {
        cout << -1 << endl;
      } else {
        cout << result << endl;
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

