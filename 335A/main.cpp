
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
  typedef std::map<char, int> Map;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int NONE = -1;
  const string T_NONE = "-1";
  // storages
  string s;
  int n;

  Map s_cnt;
  Map t_cnt;

  string t;
  int k;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      if ( s.size() < n ) {
        k = 1;
        t = s + string(n - s.size(), 'a');
        return;
      }

      t = get_t();
      if ( t == T_NONE ) {
        k = NONE;
        return;
      }

      count_s();
      count_t();
      k = get_nice_k();

      if ( ! check_valid() ) {
        k = NONE;
      }
    }

    bool check_valid() {
      for ( char c = 'a'; c <= 'z'; ++ c ) {
        if ( t_cnt[c] * k < s_cnt[c] )
          return false;
      }
      return true;
    }

    void count_s() {
      int ns = s.size();
      for ( int i = 0; i < ns; ++ i ) {
        s_cnt[s[i]] ++;
      }
    }

    void count_t() {
      int nt = t.size();
      for ( int i = 0; i < nt; ++ i ) {
        t_cnt[t[i]] ++;
      }
    }

    int get_nice_k() {
      int lb = -1, ub = 10000000;
      while ( ub - lb > 1 ) {
        int mid = ( lb + ub ) / 2;
        if ( check(mid) ) {
          ub = mid;
        } else {
          lb = mid;
        }
      }
      return ub;
    }

    bool check( int k ) {
      for ( char c = 'a'; c <= 'z'; ++ c ) {
        if ( t_cnt[c] * k < s_cnt[c] )
          return false;
      }
      return true;
    }

    string get_t() {
      Map cnt;
      int ns = s.size();
      for ( int i = 0; i < ns; ++ i ) {
        cnt[s[i]] ++;
      }

      typedef std::pair <int, char> Entry;
      typedef std::vector<Entry> Entries;
      Entries E;
      for ( char c = 'a'; c <= 'z'; ++ c ) {
        if ( cnt[c] > 0 )
          E.push_back(std::make_pair(cnt[c], c));
      }

      std::sort(E.begin(), E.end(), std::greater<Entry>());

      int ne = E.size();
      int ind = 0;
      string res = "";

      if ( n < ne )
        return T_NONE;

      int sum = 0;
      for ( Entries::iterator it_i = E.begin(); it_i != E.end(); ++ it_i ) {
        int a = (*it_i).first;
        char c = (*it_i).second;
        double port = (double)a / ns;
        int num = max(1, (int)((double)n * port));
        sum += num;
        res += string(num, c);
        ind ++;
      }

      while ( sum < n ) {
        res += E[0].second;
        sum ++;
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
      k = NONE;
      s_cnt.clear();
      t_cnt.clear();
    }

    bool input() {
      return cin >> s >> n;
    }

    void output() {
      if ( k == NONE ) {
        cout << -1 << endl;
      } else {
        cout << k << endl;
        cout << t << endl;
      }
      cout << endl;
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

