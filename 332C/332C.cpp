
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

// @snippet<sh19910711/contest:io/pair.cpp>
namespace io {
  template <class A, class B> std::ostream& operator<<( std::ostream& os, const std::pair<A,B>& p ) {
    return os << "(" << p.first << "," << p.second << ")";
  }
  template <class A, class B> std::istream& operator>>( std::istream& is, std::pair<A,B>& p ) {
    return is >> p.first >> p.second;
  }
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
  using namespace io;
}

// @snippet<sh19910711/contest:tree/interface_segment_tree.cpp>
namespace tree {
  // Segment Tree の実装
  template <class T> class ISegmentTree {
  public:
    virtual void init( int n ) {}
    virtual void update( int k, T a ) = 0;
  };
}

// @snippet<sh19910711/contest:tree/rmq_tree.cpp>
namespace tree {
  // RMQ Tree の実装
  template <class T> class RMQTree: public tree::ISegmentTree<T> {
  public:
    T INF;
    int n;
    std::vector<T> D;
    RMQTree(): INF( std::numeric_limits<T>::max() ) { n = 0; }
    RMQTree( int n_ ): INF( std::numeric_limits<T>::max() ) {init(n_);}
    void init( int n_ ) {
      n = 1;
      while ( n < n_ ) n *= 2;
      D.resize( 2 * n - 1 );
      for ( int i = 0; i < 2 * n - 1; ++ i ) D[i] = INF;
    }
    int parent( const int k ) { return ( k - 1 ) / 2; }
    int left( const int k ) { return 2 * k + 1; }
    int right( const int k ) { return 2 * k + 2; }
    // D[k] = a;
    void update( int k, T a ) {
      k += n - 1, D[k] = a;
      while ( k > 0 ) k = parent(k), D[k] = std::min( D[left(k)], D[right(k)] );
    }
    T query( int a, int b, int k, int l, int r ) {
      if ( r <= a || b <= l ) return INF;
      if ( a <= l && r <= b ) return D[k];
      T vl = query( a, b, left(k), l, ( l + r ) / 2 );
      T vr = query( a, b, right(k), ( l + r ) / 2, r );
      return std::min( vl, vr );
    }
    T query( int a, int b ) { return query( a, b, 0, 0, n ); }
  };
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int SEG_TREE_DATA_SIZE = 2 * SIZE - 1 + 11;
  const LL IDENTITY = std::numeric_limits<LL>::min();
  
  // storages
  int n, p, k;
  LL A[SIZE];
  LL B[SIZE];
  
  II C[SIZE]; // (A[i], i)
  II D[SIZE]; // (B[i], i)
  
  int nice[SIZE];
  int nice_num;
  
  class SegmentTree {
  public:
    SegmentTree() {}
    SegmentTree( int n ): n(n) {
      std::fill(data, data + SEG_TREE_DATA_SIZE, IDENTITY);
    }
    
    void update( int k, LL a ) {
      k += n - 1;
      data[k] = a;
      while ( k > 0 ) {
        k = ( k - 1 ) / 2;
        data[k] = std::max(data[k * 2 + 1], data[k * 2 + 2]);
      }
    }
    
    // [a, b)の最大値
    LL query( int a, int b, int k, int l, int r ) {
      if ( r <= a || b <= l ) {
        return IDENTITY;
      }
      if ( a <= l && r <= b ) {
        return data[k];
      } else {
        int mid = ( l + r ) / 2;
        LL vl = query(a, b, k * 2 + 1, l, mid);
        LL vr = query(a, b, k * 2 + 2, mid, r);
        return std::max(vl, vr);
      }
      
    }
    
    int n;
    LL data[SEG_TREE_DATA_SIZE];
  };
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      
      /*
         cout << "C:" << endl;
         for ( int i = 0; i < n; ++ i ) {
         cout << i << ": " << C[i] << endl;
         }
         cout << "D:" << endl;
         for ( int i = 0; i < n; ++ i ) {
         cout << i << ": " << D[i] << endl;
         }
         */
      
      find_nice_orders();
      
      
      SegmentTree tree(n);
      for ( int i = 1; i <= n; ++ i ) {
        tree.update(i, A[i]);
      }
      
      for ( int i = 1; i + 1 <= n; ++ i ) {
        cout << i << ": " << tree.query(i, i + 1, 0, 0, n) << endl;
      }
    }
    
    void normalize() {
      for ( int i = 0; i < n; ++ i ) {
        C[i] = II(A[i], i);
        D[i] = II(B[i], i);
      }
      sort(C, C + n, std::greater<II>());
      sort(D, D + n, std::greater<II>());
    }
    
    void find_nice_orders() {
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
      nice_num = 0;
    }
    
    bool input() {
      if ( ! ( cin >> n >> p >> k ) )
        return false;
      for ( int i = 1; i <= n; ++ i ) {
        cin >> A[i] >> B[i];
      }
      return true;
    }
    
    void output() {
      for ( int i = 0; i < nice_num; ++ i ) {
        cout << nice[i] << " ";
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



