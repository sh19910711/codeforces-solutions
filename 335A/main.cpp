
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
  const int NONE = -100;
  const string T_NONE = "";
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
      t = get_t();
      if ( t == T_NONE ) {
        k = NONE;
        return;
      }

      count_t();
      k = 0;
      string tmp_s = s;
      while ( ! tmp_s.empty() ) {
        int len = tmp_s.size();
        len = std::min(len, n);
        string sub = tmp_s.substr(0, len);
        s = sub;
        count_s();

        k += get_nice_k();
        tmp_s = tmp_s.substr(len);
      }
    }

    bool check_valid() {
      if ( k == 0 )
        return false;
      for ( char c = 'a'; c <= 'z'; ++ c ) {
        if ( t_cnt[c] * k < s_cnt[c] )
          return false;
      }
      return true;
    }

    void count_s() {
      s_cnt.clear();
      int ns = s.size();
      for ( int i = 0; i < ns; ++ i ) {
        s_cnt[s[i]] ++;
      }
    }

    void count_t() {
      t_cnt.clear();
      int nt = t.size();
      for ( int i = 0; i < nt; ++ i ) {
        t_cnt[t[i]] ++;
      }
    }

    int get_nice_k() {
      int lb = 0, ub = 2000;
      for ( int i = 0; i < 200; ++ i ) {
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

      typedef std::pair<int, char> Entry;
      typedef std::vector<Entry> Entries;
      Entries E;
      for ( char c = 'a'; c <= 'z'; ++ c ) {
        if ( cnt[c] > 0 ) {
          E.push_back(std::make_pair(cnt[c], c));
        }
      }
      std::sort(E.begin(), E.end(), std::greater<Entry>());

      int ne = E.size();
      if ( n < ne )
        return T_NONE;

      string res;
      int sum = 0;
      while ( sum < n ) {
        bool ok = false;
        for ( int i = 0; i < ne && sum < n; ++ i ) {
          char c = E[i].second;
          if ( cnt[c] > 0 ) {
            res += c;
            sum ++;
            cnt[c] --;
            ok = true;
          }
        }
        if ( ! ok )
          break;
      }

      int id = 0;
      while ( sum < n ) {
        res += E[id].second;
        sum ++;
        id = ( id + 1 ) % ne;
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
      t.clear();
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

