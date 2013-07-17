
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
  typedef map <int, int> Map;
  typedef set <int> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 3 * 100000 + 11;
  // storages
  int n;
  int A[SIZE];

  LL S[SIZE];

  Map L;
  Map R;

  LL max_esthetic;
  int cut[SIZE];
  int cut_num;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {

      S[0] = get_value(0);
      for ( int i = 1; i < n; ++ i )
        S[i] = S[i - 1] + get_value(i);

      for ( int i = 0; i < n; ++ i ) {
        if ( ! L.count(A[i]) ) {
          L[A[i]] = i;
        } else {
          R[A[i]] = i;
        }
      }

      LL max_sum = std::numeric_limits<LL>::min();
      int max_value = 0;
      for ( int i = 0; i < n; ++ i ) {
        int a = A[i];
        if ( R.count(a) ) {
          int l = L[a];
          int r = R[a];
          LL sum = S[r - 1] - S[l] + a * 2;
          if ( sum > max_sum ) {
            max_sum = sum;
            max_value = a;
          }
        }
      }

      max_esthetic = max_sum;
      generate_cut(max_value);
    }

    void generate_cut( int a ) {
      int l = L[a];
      int r = R[a];
      for ( int i = 0; i < n; ++ i ) {
        if ( l <= i && i <= r ) {
          if ( i != l && i != r && A[i] < 0 ) {
            cut[cut_num ++] = i + 1;
          }
        } else {
          cut[cut_num ++] = i + 1;
        }
      }
    }

    LL get_value( int x ) {
      return A[x] < 0 ? 0 : A[x];
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
      max_esthetic = 0;
      cut_num = 0;
      L.clear();
      R.clear();
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> A[i];
      return true;
    }

    void output() {
      cout << max_esthetic << " " << cut_num << endl;
      for ( int i = 0; i < cut_num; ++ i ) {
        cout << cut[i] << " ";
      }
      cout << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

