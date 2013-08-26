
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

// @snippet<sh19910711/contest:solution/define_classes.cpp>
namespace solution {
  class Solution;
  class Solver;
  class Storages;
}

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    
  protected:
    SolutionInterface() {}
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input( Storages& s ) { return false; };
    virtual void output( const Storages& s ) const {};
    virtual void before_action( const int& test_no ) const {}
    virtual void after_action( const int& test_no ) const {}
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}
    virtual int run() {
      this->pre_calc();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:misc/smart_pointer_reference_count.cpp>
namespace misc {
  class SmartPointerReferenceCount {
  public:
    void add() { count ++; }
    int release() { return -- count; }
  private:
    int count;
  };
}

// @snippet<sh19910711/contest:misc/smart_pointer.cpp>
namespace misc {
  template <typename Type> class SmartPointer {
  public:
    SmartPointer(): pointer(0), reference(0) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(Type* value): pointer(value) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(const SmartPointer<Type>& sp): pointer(sp.pointer), reference(sp.reference) {
      reference->add();
    }
    ~SmartPointer() {
      if ( reference->release() == 0 ) {
        delete pointer;
        delete reference;
      }
    }
    Type& operator *() { return *pointer; }
    const Type& operator *() const { return *pointer; }
    Type* operator +( const int& x ) { return pointer + x; }
    const Type* operator +( const int& x ) const { return pointer + x; }
    Type* operator ->() { return pointer; }
    SmartPointer<Type>& operator = ( const SmartPointer<Type>& sp ) {
      if ( this != &sp ) {
        if ( reference->release() == 0 ) {
          delete pointer;
          delete reference;
        }
        pointer = sp.pointer;
        reference = sp.reference;
        reference->add();
      }
      return *this;
    }
  private:
    Type* pointer;
    misc::SmartPointerReferenceCount* reference;
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef misc::SmartPointer<ValueType> Pointer;
    VectorClass() { data = Pointer(new ValueType[SIZE]); }
    ValueType& operator [] ( const int& index ) { return *(data + index); }
    const ValueType& operator [] ( const int& index ) const { return *(data + index); }
  private:
    Pointer data;
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  const int VECTOR_NONE = -1;
  template <typename ValueType, int SIZE_X = VECTOR_NONE, int SIZE_Y = VECTOR_NONE, int SIZE_Z = VECTOR_NONE> struct Vector {
    typedef storage::VectorClass<ValueType, SIZE_X> Type__;
    typedef storage::VectorClass<Type__, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_Z> Type;
  };
  template <typename ValueType, int SIZE_X, int SIZE_Y> struct Vector<ValueType, SIZE_X, SIZE_Y, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X> struct Vector<ValueType, SIZE_X, VECTOR_NONE, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type;
  };
}

namespace tree {
  template <class T> class ISegmentTree {
  public:
    virtual void init( int n ) {}
    virtual void update( int k, T a ) = 0;
  };
}

namespace tree {
  template <class T> class MyTree: public tree::ISegmentTree<T> {
  public:
    T INF;
    int n;
    std::vector<T> D;
    MyTree(): INF( std::numeric_limits<T>::max() ) { n = 0; }
    MyTree( int n_ ): INF( std::numeric_limits<T>::max() ) {init(n_);}

    void init( int n_ ) {
      n = 1;
      while ( n < n_ ) n *= 2;
      D.resize( 2 * n - 1 );
      for ( int i = 0; i < 2 * n - 1; ++ i ) D[i] = 0;
    }

    int parent( const int k ) { return ( k - 1 ) / 2; }
    int left( const int k ) { return 2 * k + 1; }
    int right( const int k ) { return 2 * k + 2; }

    T operation( const T& a, const T& b, const int& x ) {
      if ( (T)log2(n) % T(2) == 0 ) {
        if ( x % 2 == 0 ) {
          return a | b;
        } else {
          return a ^ b;
        }
      } else {
        if ( x % 2 == 0 ) {
          return a ^ b;
        } else {
          return a | b;
        }
      }
    }

    // D[k] = a;
    void update( int k, T a ) {
      using namespace std;
      int t = 0;
      k += n - 1, D[k] = a;
      cout << "@MyTree#update: k = " << k << ", a = " << a << endl;
      while ( k > 0 ) {
        k = parent(k);
        cout << "@MYTree#update: before: D[k] = " << D[k] << " / l = " << D[left(k)] << ", r = " << D[right(k)] << endl;
        D[k] = operation( D[left(k)], D[right(k)], t );
        cout << "@MYTree#update: before: D[k] = " << D[k] << endl;
        t ++;
      }
    }

    // 
    T query( int a, int b, int k, int l, int r, int t ) {
      using namespace std;
      if ( r <= a || b <= l ) return 0;
      if ( a <= l && r <= b ) return D[k];
      T vl = query( a, b, left(k), l, ( l + r ) / 2, t + 1 );
      T vr = query( a, b, right(k), ( l + r ) / 2, r, t + 1 );
      printf("@MyTree#query: a = %d, b = %d, k = %d, l = %d, r = %d, t = %d\n", a, b, k, l, r, t);
      cout << "@MyTree#query: " << "vl = " << vl << " / vr = " << vr << endl;
      return operation( vl, vr, t );
    }
    T query( int a, int b ) { return query( a, b, 0, 0, 2 * n - 1, 0 ); }
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  typedef tree::MyTree<Int> SegTree;
}

namespace solution {
  class QueryInfo {
  public:
    int pos;
    int new_value;
  };
  
  istream& operator >> ( istream& is, QueryInfo& query ) {
    return is >> query.pos >> query.new_value;
  }
  ostream& operator << ( ostream& os, const QueryInfo& query ) {
    return os << "(" << query.pos << ", " << query.new_value << ")";
  }
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const Int SIZE = 140 * 1024;
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  class Storages {
  public:
    typedef storage::Vector<Int, SIZE>::Type Sequence;
    typedef storage::Vector<QueryInfo, SIZE>::Type Queries;
    typedef storage::Vector<Int, SIZE>::Type QueryResults;
    
    Int N;
    Int M;
    Sequence A;
    Int A_num;
    Queries Q;

    SegTree T;
    
    QueryResults query_results;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.A_num = std::pow(Int(2), s.N);
      s.T = generate_segment_tree(s.A, s.A_num);

      for ( int i = 1; i <= s.A_num; ++ i ) {
        cout << i << ": " << s.T.query(i, i + 1) << endl;
      }

      for ( int i = 1; i <= s.A_num; ++ i ) {
        cout << s.A[i] << ", ";
      }
      cout << endl;
      proc_queries(s.Q, s.A_num, s.M, s.T, s.query_results);
    }
  protected:

    SegTree generate_segment_tree( const Storages::Sequence& A, const Int& N ) {
      SegTree res(N);
      for ( int i = 1; i <= N; ++ i ) {
        res.update(i, A[i]);
      }
      return res;
    }

    void proc_queries( const Storages::Queries& Q, const Int& N, const Int& M, SegTree& T, Storages::QueryResults& query_results ) {
      for ( int i = 0; i < M; ++ i ) {
        cout << "@proc_queries: query = " << Q[i] << endl;
        query_results[i] = proc_query(Q[i], N, T);
      }
    }

    Int proc_query( const QueryInfo& Q, const Int& N, SegTree& T ) {
      T.update(Q.pos, Q.new_value);
      return T.query(1, N);
    }
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {}
    Solution(Storages* p): storages(p) {}
    
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input(*this->storages) )
        return false;
      solver.solve(*this->storages);
      this->output(*this->storages);
      return true;
    }
    
    bool input( Storages& s ) {
      if ( ! ( std::cin >> s.N >> s.M ) )
        return false;
      for ( Int i = 1; i <= std::pow(Int(2), s.N); ++ i )
        std::cin >> s.A[i];
      for ( Int i = 0; i < s.M; ++ i )
        std::cin >> s.Q[i];
      return true;
    }

    void output( const Storages& s ) const {
      for ( int i = 0; i < s.M; ++ i ) {
        std::cout << s.query_results[i] << endl;
      }
    }
    
  private:
    Solver solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  // std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif



