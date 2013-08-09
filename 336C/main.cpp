
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
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int G_SIZE = 32;
  const int NONE = -1;
  // storages
  int n;
  LL A[SIZE];
  
  int GC[G_SIZE];
  LL G[G_SIZE][SIZE];
  
  int TC;
  LL T[SIZE];
  
  int BC;
  LL B[SIZE];
}

// @snippet<sh19910711/contest:misc/get_binary_string.cpp>
namespace misc {
  // @desc 2進表記した文字列を求める
  template <class T> std::string GetBinaryString( const T& v ) {
    std::ostringstream oss;
    for ( int i = 0; i < static_cast<int>(sizeof v) * 8; ++ i ) {
      int bi = ( v >> i ) & 1;
      oss << bi;
    }
    std::string res = oss.str();
    std::reverse( res.begin(), res.end() );
    return res;
  }
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      find_group();
      int v = find_v();
      while ( ( v = find_v() ) != NONE ) {
        generate_t(v);
        generate_b(v);
        if ( BC != NONE )
          return;
      }
    }
    
    void generate_b( int v ) {
      LL and_sum = bit(G_SIZE) - 1;
      for ( int i = 0; i < TC; ++ i ) {
        and_sum &= T[i];
      }
      Set s;
      for ( int i = 0; i < GC[v]; ++ i )
        s.insert(G[v][i]);
      for ( int i = 0; i < v - 1; ++ i ) {
        LL bi = bit(i);
        if ( and_sum & bi ) {
          for ( int j = 0; j < GC[i]; ++ j ) {
            s.erase(G[i][j]);
          }
        }
      }
      if ( s.size() ) {
        BC = 0;
        for ( Set::iterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
          B[BC ++] = *it_i;
        }
      }
      else
        GC[v] = 0;
    }
    
    void generate_t( int v ) {
      TC = 0;
      for ( int i = 0; i < GC[v]; ++ i ) {
        T[TC ++] = G[v][i];
      }
    }
    
    int find_v() {
      int res = NONE;
      for ( int i = 0; i < G_SIZE; ++ i ) {
        if ( GC[i] )
          res = max(res, i);
      }
      return res;
    }
    
    LL bit( int k ) {
      return 1LL << k;
    }
    
    void find_group() {
      for ( int i = 0; i < n; ++ i ) {
        for ( int j = 0; j < G_SIZE; ++ j ) {
          LL bi = bit(j);
          if ( A[i] & bi )
            G[j][GC[j] ++] = A[i];
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
      BC = NONE;
      for ( int i = 0; i < G_SIZE; ++ i )
        GC[i] = 0;
    }
    
    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> A[i];
      return true;
    }
    
    void output() {
      if ( BC == NONE ) {
        cout << A[0] << endl;
      } else {
        cout << BC << endl;
        for ( int i = 0; i < BC; ++ i ) {
          cout << B[i] << " ";
        }
        cout << endl;
      }
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


