
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
  typedef LL INT;
  typedef std::vector<INT> VI;
  typedef std::vector<VI> VVI;
  typedef std::pair<INT,INT> II;
  typedef std::vector<II> VII;
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
  template <class T> class RMQTree_min: public tree::ISegmentTree<T> {
  public:
    T INF;
    int n;
    std::vector<T> D;
    RMQTree_min(): INF( std::numeric_limits<T>::max() ) { n = 0; }
    RMQTree_min( int n_ ): INF( std::numeric_limits<T>::max() ) {init(n_);}
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

// @snippet<sh19910711/contest:tree/rmq_tree.cpp>
namespace tree {
  // RMQ Tree の実装
  template <class T> class RMQTree: public tree::ISegmentTree<T> {
  public:
    T INF;
    int n;
    std::vector<T> D;
    RMQTree(): INF( std::numeric_limits<T>::min() ) { n = 0; }
    RMQTree( int n_ ): INF( std::numeric_limits<T>::min() ) {init(n_);}
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
      while ( k > 0 ) k = parent(k), D[k] = std::max( D[left(k)], D[right(k)] );
    }
    T query( int a, int b, int k, int l, int r ) {
      if ( r <= a || b <= l ) return INF;
      if ( a <= l && r <= b ) return D[k];
      T vl = query( a, b, left(k), l, ( l + r ) / 2 );
      T vr = query( a, b, right(k), ( l + r ) / 2, r );
      return std::max( vl, vr );
    }
    T query( int a, int b ) { return query( a, b, 0, 0, n ); }
  };
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  using namespace io;

  typedef II Entry; // (value, real-index, pos)
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int SEG_TREE_DATA_SIZE = 2 * SIZE - 1 + 11;
  const LL IDENTITY = std::numeric_limits<LL>::min();
  const LL IDENTITY_MIN = std::numeric_limits<LL>::max();
  const Entry IDENTITY_ENTRY(IDENTITY, IDENTITY);
  const Entry IDENTITY_ENTRY_MIN(IDENTITY_MIN, IDENTITY_MIN);
  
  // storages
  int n, p, k;
  LL A[SIZE];
  LL B[SIZE];
  
  II C[SIZE]; // (A[i], i)
  II D[SIZE]; // (B[i], i)
  tree::RMQTree<Entry> tree_a;
  tree::RMQTree<Entry> tree_b;
  int tree_pos_a[SIZE]; // A[i]がtreeの何番目にあるか
  int tree_pos_b[SIZE]; // B[i]がtreeの
  
  int nice[SIZE];
  int nice_num;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      generate_tree();

      cout << "C:" << endl;
      for ( int i = 0; i < n; ++ i ) {
        cout << i << ": " << C[i] << endl;
      }
      cout << "D:" << endl;
      for ( int i = 0; i < n; ++ i ) {
        cout << i << ": " << D[i] << ": A = " << A[D[i].second] << endl;
      }

      // [l, r)
      // cout << tree_a.query(0, 1, 0, 0, 2 * n - 1);
      //
      cout << "query_test: " << tree_b.query(0, n, 0, 0, 2 * n - 1) << endl;

      find_nice_orders();
    }

    void generate_tree() {
      tree_a.init(n);
      tree_b.init(n);
      for ( int i = 0; i < n; ++ i ) {
        tree_pos_a[C[i].second] = i;
        tree_a.update(i, Entry(A[C[i].second], C[i].second));
        tree_pos_b[D[i].second] = i;
        tree_b.update(i, Entry(B[D[i].second], D[i].second));
      }
    }
    
    void normalize() {
      for ( int i = 0; i < n; ++ i ) {
        C[i] = II(A[i], i);
        D[i] = II(B[i], i);
      }
      sort(C, C + n, std::greater<II>());
      sort(D, D + n, std::less<II>());
    }
    
    void find_nice_orders() {
      int need_bad_num = p - k;
      int bad_num = 0;
      printf("@find_nice_orders: need_bad_num = %d\n", need_bad_num);

      for ( int i = 0; i < n && nice_num < p; ++ i ) {
        Entry nice_entry = tree_a.query(0, n, 0, 0, 2 * n - 1);
        int good_order_index = nice_entry.second;
        int a = A[good_order_index];
        int b = B[good_order_index];

        cout << "nice_entry: " << nice_entry << " : " << a << ", " << b << endl;
        bad_num ++;
        nice[nice_num ++] = good_order_index;
        tree_a.update(tree_pos_a[good_order_index], IDENTITY_ENTRY);
        tree_b.update(tree_pos_b[good_order_index], IDENTITY_ENTRY);

        while ( nice_num < p && bad_num < need_bad_num ) {
          cout << "hello" << endl;
          int left_cand = std::lower_bound(D, D + n, II(b, -1)) - D;
          cout << "left_cand = " << left_cand << endl;
          Entry bad_but_nice_entry = tree_b.query(0, left_cand, 0, 0, 2 * n - 1);
          if ( bad_but_nice_entry == IDENTITY_ENTRY )
            break;
          cout << "max_orderのB以下でBの最大値 = " << bad_but_nice_entry << endl;
          int order_index = bad_but_nice_entry.second;
          nice[nice_num ++] = order_index;
          bad_num ++;
          tree_a.update(tree_pos_a[order_index], IDENTITY_ENTRY);
          tree_b.update(tree_pos_b[order_index], IDENTITY_ENTRY);
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
      nice_num = 0;
    }
    
    bool input() {
      if ( ! ( cin >> n >> p >> k ) )
        return false;
      for ( int i = 0; i < n; ++ i ) {
        cin >> A[i] >> B[i];
      }
      return true;
    }
    
    void output() {
      for ( int i = 0; i < nice_num; ++ i ) {
        cout << nice[i] + 1 << " ";
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



