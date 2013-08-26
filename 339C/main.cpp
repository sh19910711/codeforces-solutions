
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
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const Int SIZE = 1000 + 11;
  const Int WEIGHTS = 10 + 11;
  const Int NONE = -1;
  const String YES = "YES";
  const String NO = "NO";
  const char WEIGHT_EXIST = '1';
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  class Storages {
  public:
    typedef storage::Vector<Int, SIZE>::Type Result;
    typedef storage::Vector<Int, WEIGHTS>::Type Weights;
    typedef Int WeightsNum;

    String S;
    Int M;

    Weights W;
    WeightsNum WC;

    Int result_num;
    Result result_list;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      get_weights(s.S, s.W, s.WC);
      if ( s.M == 1 ) {
        if ( s.WC >= 1 ) {
          s.result_list[0] = s.W[0];
          s.result_num = 1;
        } else {
          s.result_num = NONE;
        }
        return;
      } else if ( s.M == 2 ) {
        if ( s.WC >= 2 ) {
          s.result_list[0] = s.W[0];
          s.result_list[1] = s.W[1];
          s.result_num = 2;
        } else {
          s.result_num = NONE;
        }
        return;
      }
      s.result_num = find_good_list(s.W, s.WC, s.M, s.result_list, s.result_num);
    }
  protected:
    void get_weights( const String& s, Storages::Weights& weights, Storages::WeightsNum& weights_num ) {
      weights_num = 0;
      for ( int i = 0; i < s.size(); ++ i )
        if ( s[i] == WEIGHT_EXIST )
          weights[weights_num ++] = i + 1;
    }

    Int find_good_list( const Storages::Weights& w, const Storages::WeightsNum& n, const Int& m, Storages::Result& result_list, Int& result_num ) {
      Int sum = 0;
      for ( int i = n - 1; i >= 0; -- i ) {
        for ( int j = i - 1; j >= 0; -- j ) {
          Int k1 = w[j];
          Int k2 = w[i];
          Int x = std::max(Int(0), k2 / ( k2 - k1 ) - 1);
          sum += 2 * x - 1;
          if ( k2 % ( k2 - k1 ) == 0 )
            sum ++;
        }
      }
      if ( sum < m )
        return NONE;

      result_num = 0;
      Int remains = m;
      for ( int i = n - 1; i >= 0; -- i ) {
        for ( int j = i - 1; j >= 0; -- j ) {
          Int k1 = w[j];
          Int k2 = w[i];
          Int x = std::max(Int(0), k2 / ( k2 - k1 ) - 1);
          if ( x > 0 && remains > 0 ) {
            x --;
            result_list[result_num ++] = k1;
            remains --;
          }
          for ( int k = 0; k < x; ++ k ) {
            if ( remains > 0 ) {
              result_list[result_num ++] = k2;
              remains --;
            }
            if ( remains > 0 ) {
              result_list[result_num ++] = k1;
              remains --;
            }
          }
          if ( k2 % ( k2 - k1 ) == 0 && remains > 0 ) {
            if ( remains > 0 ) {
              result_list[result_num ++] = k2;
              remains --;
            }
          }
        }
      }
      return result_num;
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
      if ( ! ( std::cin >> s.S ) )
        return false;
      return std::cin >> s.M;
    }

    void output( const Storages& s ) const {
      if ( s.result_num == NONE ) {
        std::cout << NO << std::endl;
      } else {
        std::cout << YES << std::endl;
        for ( int i = 0; i < s.result_num; ++ i ) {
          std::cout << s.result_list[i] << " ";
        }
        std::cout << std::endl;
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
  std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif


