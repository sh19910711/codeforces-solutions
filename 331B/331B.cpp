
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

// @snippet<sh19910711/contest:tree/binary_indexed_tree.cpp>
namespace tree {
  template <class T> class BinaryIndexedTree {
  public:
    int n;
    std::vector<T> data;
    
    BinaryIndexedTree() {}
    BinaryIndexedTree( const int& n ): n(n) {
      data = std::vector<T>(n + 1, 0);
    }
    
    T sum( int i ) {
      i ++;
      int res = 0;
      while ( i > 0 ) { res += data[i]; i -= i & -i; }
      return res;
    }
    
    void add( int i, const T& x ) {
      i ++;
      while ( i <= n ) { data[i] += x; i += i & -i; }
    }
    
    T get( const int& x ) {
      return sum(x) - sum(x - 1);
    }
    
    void set( const int& x, const T& new_value ) {
      add(x, new_value - get(x));
    }
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
  typedef tree::BinaryIndexedTree<int> BIT;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 3 * 100000 + 111;
  const int NONE = -1;
  // storages
  int n;
  int A[SIZE];
  int q;
  int P[SIZE];
  int X[SIZE];
  int Y[SIZE];
  
  int B[SIZE];
  BIT bit;
  
  int results[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      B[0] = std::numeric_limits<int>::min();
      B[n + 1] = std::numeric_limits<int>::max();
      for ( int i = 1; i <= n; ++ i )
        B[A[i]] = i;
      
      for ( int i = 1; i <= n; ++ i )
        if ( B[i] > B[i + 1] )
          set_value(i, 1);
      
      for ( int i = 0; i < q; ++ i )
        results[i] = query(P[i], X[i], Y[i]);
    }
    
    int get_value( int x ) {
      return bit.sum(x) - bit.sum(x - 1);
    }
    
    void set_value( int x, int new_value ) {
      int value = get_value(x);
      bit.add(x, -value);
      bit.add(x, new_value);
    }
    
    int query( int p, int x, int y ) {
      if ( p == 1 ) {
        return query_a(x, y);
      } else if ( p == 2 ) {
        return query_b(x, y);
      }
      return NONE;
    }
    
    int query_a( int x, int y ) {
      return bit.sum(y - 1) - bit.sum(x - 1) + 1;
    }
    
    int query_b( int x, int y ) {
      int value_x = A[x];
      int value_y = A[y];
      B[value_x] = y;
      B[value_y] = x;
      swap(A[x], A[y]);
      
      for ( int i = -1; i <= 1; ++ i ) {
        int n_value_x = value_x + i;
        int n_value_y = value_y + i;
        if ( n_value_x > 0 && n_value_x + 1 <= n ) {
          set_value(n_value_x, B[n_value_x] > B[n_value_x + 1] ? 1 : 0);
        }
        if ( n_value_y > 0 && n_value_y + 1 <= n ) {
          set_value(n_value_y, B[n_value_y] > B[n_value_y + 1] ? 1 : 0);
        }
      }
      
      return NONE;
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
      bit = BIT(SIZE);
    }
    
    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 1; i <= n; ++ i )
        cin >> A[i];
      cin >> q;
      for ( int i = 0; i < q; ++ i )
        cin >> P[i] >> X[i] >> Y[i];
      return true;
    }
    
    void output() {
      for ( int i = 0; i < q; ++ i )
        if ( results[i] != NONE )
          cout << results[i] << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}


