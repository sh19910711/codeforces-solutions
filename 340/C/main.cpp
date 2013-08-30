
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
    
    void sort(const int& begin, const int& end) {
      std::sort(data + begin, data + end);
    }
    ValueType sum(const int& begin, const int& end) {
      return std::accumulate(data + begin, data + end, ValueType());
    }
    
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

// @snippet<sh19910711/contest:math/big_integer.cpp>
namespace math {
  // 多倍長整数の実装
  class BigInteger {
  public:
    char *digits;
    int size, capacity, sign;
    
    BigInteger() {
      capacity = 128;
      sign = 0;
      digits = new char[capacity];
      memset( digits, 0, capacity );
      size = 0;
    }
    BigInteger( int n, int cap ) {
      cap = std::max( cap, (int)sizeof(n) * 8 );
      capacity = cap, sign = sig(n), n *= sign, digits = new char[cap];
      memset( digits, 0, cap );
      for ( size = 0; n; ++ size ) digits[size] = n % 10, n /= 10;
    }
    BigInteger( int n ) {
      capacity = 1024, sign = sig(n), n *= sign, digits = new char[capacity];
      memset( digits, 0, capacity );
      size = 0;
      while (n) digits[size++] = n % 10, n /= 10;
    }
    BigInteger( std::string s ) {
      capacity = std::max( (int)s.size(), 16 );
      sign = 0, digits = new char[capacity];
      memset( digits, 0, capacity );
      std::istringstream in(s);
      in >> (*this);
    }
    BigInteger( const BigInteger& n ) {
      capacity = n.capacity;
      sign = n.sign, size = n.size, digits = new char[capacity];
      memcpy( digits, n.digits, capacity );
    }
    
    static bool isDigit( int c ) { return ( c >= (int)'0' && c <= (int)'9' ); }
    
    friend std::istream& operator >>( std::istream& in, BigInteger& n ) {
      n.size = 0, n.sign = 1;
      int sign = 1, c;
      while ( ( c = in.peek() ) >= 0 && ( c == ' ' || c == '\t' || c == '\r' || c == '\n' ) )
        in.get();
      if ( c < 0 || ( c != (int)'-' && ! isDigit(c) ) ) {
        in >> c; return in;      
      }
      if ( c == (int)'-' ) {
        sign = -1; in.get();
      }
      while ( ( c = in.peek() ) >= 0 && isDigit(c) ) {
        in.get(); n *= 10; n += ( c - (int)'0' );
      }
      n.sign = sign; n.normalize();
      return in;
    }
    
    friend std::ostream& operator <<( std::ostream& out, BigInteger n ) {
      return out << n.toString();
    }
    
    const BigInteger& operator =( const BigInteger& n ) {
      if ( &n != this ) {
        if ( capacity < n.size ) {
          capacity = n.capacity;
          delete[] digits;
          digits = new char[capacity];
        }
        sign = n.sign, size = n.size;
        memcpy( digits, n.digits, size );
        memset( digits + size, 0, capacity - size );
      }
      return *this;
    }
    
    const BigInteger& operator =( int n ) {
      sign = sig(n), n *= sign;
      for ( size = 0; n; ++ size ) {
        digits[size] = n % 10;
        n /= 10;
      }
      return *this;
    }
    
    ~BigInteger() {
      delete[] digits;
    }
    
    void normalize() {
      while ( size && ! digits[size-1] ) size --;
      if ( ! size ) sign = 0;
    }
    
    int toInt() {
      int result = 0;
      for ( int i = size - 1; i >= 0; -- i ) {
        result *= 10, result += digits[i];
        if ( result < 0 ) return sign * 0x7FFFFFFF;
      }
      return sign * result;
    }
    
    std::string toString() {
      std::string s = ( sign >= 0 ? "" : "-" );
      for ( int i = size - 1; i >= 0; -- i ) s += ( digits[i] + '0' );
      if ( size == 0 ) s += '0';
      return s;
    }
    
    int sig( int n ) {
      return ( n > 0 ? 1 : ( n == 0 ? 0 : -1 ) );
    }
    
    void grow() {
      char* olddigits = digits;
      int oldCap = capacity;
      capacity *= 2;
      digits = new char[capacity];
      memcpy( digits, olddigits, oldCap );
      memset( digits + oldCap, 0, oldCap );
      delete [] olddigits;
    }
    
    BigInteger operator ++() { operator +=(1); return *this;}
    BigInteger operator ++( int ) { return operator ++(); }
    BigInteger operator --() { operator -=(1); return *this; }
    BigInteger operator --( int ) { return operator--(); }
    BigInteger operator -() { BigInteger result(*this); result.sign *= -1; return result; }
    BigInteger operator +( int n ) { BigInteger result(*this); result += n; return result; }
    BigInteger operator +( BigInteger n ) { BigInteger result(*this); result += n; return result; }
    
    BigInteger& operator +=( int n ) {
      if ( size == capacity ) grow();
      int nsign = sig(n);
      if ( ! nsign ) return *this;
      if ( ! sign ) sign = nsign;
      if ( sign == nsign ) {
        n *= nsign;
        int carry = 0, i;
        for ( i = 0; n || carry; ++ i ) {
          int dig = n % 10, newdig = digits[i] + dig + carry;
          digits[i] = newdig % 10, carry = newdig / 10, n /= 10;
        }
        size = std::max( i, size );
      } else {
        operator -=( -n );
      }
      return *this;
    }
    
    BigInteger& operator +=( BigInteger n ) {
      int maxS = std::max( size, n.size ) + 1;
      while ( maxS >= capacity ) grow();
      if ( ! n.sign ) return *this;
      if ( ! sign ) sign = n.sign;
      if ( sign == n.sign ) {
        int carry = 0, i;
        for ( i = 0; i < maxS - 1 || carry; ++ i ) {
          int newdig = carry;
          if ( i < size ) newdig += digits[i];
          if ( i < n.size ) newdig += n.digits[i];
          digits[i] = newdig % 10;
          carry = newdig / 10;
        }
        size = std::max( i, size );
      } else {
        n.sign *= -1, operator-=(n), n.sign *= -1;
      }
      return *this;
    }
    
    BigInteger operator-( int n ) { BigInteger result(*this); result -= n; return result; }
    BigInteger operator-( BigInteger n ) { BigInteger result(*this); result -= n; return result; }
    BigInteger operator-=( int n ) {
      if ( size == capacity ) grow();
      int nsign = sig(n);
      if ( ! nsign ) return *this;
      if ( ! sign ) sign = 1;
      if ( sign == nsign ) {
        BigInteger bin = n;
        if ( ( sign >= 0 && *this < bin ) || ( sign < 0 && *this > bin ) ) {
          operator=( toInt() - n );
          return *this;
        }
        n *= nsign;
        int carry = 0, i;
        for ( i = 0; n || carry; ++ i ) {
          int dig = n % 10, newdig = digits[i] - dig + carry;
          if ( newdig < 0 ) newdig += 10, carry = -1;
          else carry = 0;
          digits[i] = newdig, n /= 10;
        }
        normalize();
      } else {
        operator+=(-n);
      }
      return *this;
    }
    
    BigInteger operator-=( BigInteger n ) {
      int maxS = std::max( size, n.size ) + 1;
      while ( maxS >= capacity ) grow();
      if ( ! n.sign ) return *this;
      if ( ! sign ) sign = 1;
      if ( sign == n.sign ) {
        if ( ( sign >= 0 && *this < n ) || ( sign < 0 && *this > n ) ) {
          BigInteger tmp = n;
          tmp -= *this, *this = tmp, sign = -sign;
          return *this;
        }
        int carry = 0, i;
        for ( i = 0; i < maxS - 1; ++ i ) {
          int newdig = carry;
          if ( i < size ) newdig += digits[i];
          if ( i < n.size ) newdig -= n.digits[i];
          if ( newdig < 0 ) newdig += 10, carry = -1;
          else carry = 0;
          digits[i] = newdig;
        }
        if ( carry ) {
          if (i) digits[0] = 10 - digits[0];
          size = ( i ? 1 : 0 );
          for ( int j = 1; j < i; ++ j ) {
            digits[j] = 9 - digits[j];
            if ( digits[i] ) size = j + 1;
          }
          sign *= -1;
        }
        normalize();
      } else {
        n.sign *= -1; operator +=(n); n.sign *= -1;
      }
      return *this;
    }
    
    BigInteger operator*( int n ) {
      BigInteger result( 0, size + (int)sizeof(n) * 8 );
      int nsign = sig(n);
      n *= nsign;
      result.sign = sign * nsign;
      if ( ! result.sign ) return result;
      int i, j;
      for ( i = 0; n; ++ i ) {
        int dig = n % 10;
        if ( dig ) {
          int carry = 0;
          for ( j = 0; j < size || carry; ++ j ) {
            int newDig = result.digits[i+j] + ( j < size ? dig * digits[j] : 0 ) + carry;
            result.digits[i+j] = newDig % 10, carry = newDig / 10;
          }
        }
        n /= 10;
      }
      result.size = i + j - 1;
      return result;
    }
    
    BigInteger operator*( BigInteger n ) {
      BigInteger result( 0, size + n.size );
      result.sign = sign * n.sign;
      if ( ! result.sign )
        return result;
      
      int i, j;
      for ( i = 0; i < n.size; ++ i ) {
        if ( n.digits[i] ) {
          int carry = 0;
          for ( j = 0; j < size || carry; ++ j ) {
            int newDig = result.digits[i+j] +
              ( j < size ? n.digits[i] * digits[j] : 0 ) + carry;
            result.digits[i+j] = newDig % 10, carry = newDig / 10;
          }
        }
      }
      result.size = i + j - 1;
      return result;
    }
    
    void operator *=( int n ) { operator=( operator*( n ) ); }
    void operator *=( BigInteger n ) { operator=( operator*( n ) ); }
    
    BigInteger operator/( int n ) {
      if (!n) n /= n;
      BigInteger result(*this);
      result /= n;
      return result;
    }
    
    BigInteger operator/( BigInteger n ) {
      if (!n) n.size /= n.size;
      BigInteger result(*this);
      result /= n;
      return result;
    }
    
    void operator/=( int n ) { divide(n); }
    void operator/=( BigInteger n ) { divide(n); }
    BigInteger operator%( BigInteger n ) { BigInteger tmp(*this); return tmp.divide(n); }
    BigInteger operator%( int n ) { BigInteger tmp(*this); return tmp.divide(n); }
    void operator%=( int n ) { operator=(divide(n)); }
    
    int divide( int n ) {
      if (!n) n /= n;
      int nsign = sig(n);
      n *= nsign;
      if (!sign) return 0;
      sign *= nsign;
      int tmp = 0;
      for ( int i = size - 1; i >= 0; -- i ) {
        tmp *= 10, tmp += digits[i], digits[i] = tmp / n, tmp -= digits[i] * n;
      }
      normalize();
      return tmp;
    }
    
    BigInteger divide( BigInteger n ) {
      if (!n) n.size /= n.size;
      if (!sign) return 0;
      sign *= n.sign;
      int oldSign = n.sign;
      n.sign = 1;
      BigInteger tmp( 0, size );
      for ( int i = size - 1; i >= 0; -- i ) {
        tmp *= 10, tmp += digits[i], digits[i] = 0;
        while ( tmp >= n ) {
          tmp -= n, digits[i] ++;
        }
      }
      normalize();
      n.sign = oldSign;
      return tmp;
    }
    
    BigInteger operator <<( int n ) { BigInteger result(*this); result <<= n; return result; }
    BigInteger operator <<( BigInteger n ) { return operator <<( n.toInt() ); }
    void operator <<=( int n ) {
      if ( n < 0 ) {
        operator >>=( -n );
      } else if ( n > 0 ) {
        BigInteger mult( 1, 4 * n );
        for ( int i = ( 1 << 30 ); i; i >>= 1 ) {
          mult *= mult;
          if ( n & i ) mult *= 2;
        }
        operator*=(mult);
      }
    }
    
    BigInteger operator >>( int n ) { BigInteger result(*this); result >>= n; return result; }
    BigInteger operator >>( BigInteger n ) { return operator >>( n.toInt() ); }
    
    void operator >>=( int n ) {
      if ( n < 0 ) {
        operator<<=(-n);
      } else if ( n > 0 ) {
        BigInteger mult( 1, 4 * n );
        for ( int i = ( 1 << 30 ); i; i >>= 1 ) {
          mult *= mult;
          if ( n & i ) mult *= 2;
        }
        operator /=(mult);
      }
    }
    
    bool operator!() { return !size; }
    operator int() { return toInt(); }
    operator bool() { std::cout << "this = " << (*this) << std::endl; return size != 0; }
    operator std::string() { return toString(); }
    bool operator <( const BigInteger& n ) const { return ( compare(n) < 0 );}
    bool operator >( const BigInteger& n ) const { return ( compare(n) > 0 ); }
    bool operator ==( const BigInteger& n ) const { return ( compare(n) == 0 ); }
    bool operator !=( const BigInteger& n ) const { return ( compare(n) != 0 ); }
    bool operator <=( const BigInteger& n ) const { return ( compare(n) <= 0 ); }
    bool operator >=( const BigInteger& n ) const { return ( compare(n) >= 0 ); }
    bool operator <( const int& n ) const { return ( compare(BigInteger(n)) < 0 ); }
    bool operator >( const int& n ) const { return ( compare(BigInteger(n)) > 0 ); }
    bool operator ==( const int& n ) const { return ( compare(BigInteger(n)) == 0 ); }
    bool operator !=( const int& n ) const { return ( compare(BigInteger(n)) != 0 ); }
    bool operator <=( const int& n ) const { return ( compare(BigInteger(n)) <= 0 ); }
    bool operator >=( const int& n ) const { return ( compare(BigInteger(n)) >= 0 ); }
    
    int compare( const BigInteger& n ) const {
      if ( sign < n.sign ) return -1;
      if ( sign > n.sign ) return 1;
      if ( size < n.size ) return -sign;
      if ( size > n.size ) return sign;
      for ( int i = size - 1; i >= 0; -- i ) {
        if ( digits[i] < n.digits[i] ) return -sign;
        else if ( digits[i] > n.digits[i] ) return sign;
      }
      return 0;
    }
  };
  
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef math::BigInteger Int;
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
  const int SIZE = 100000 + 11;
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  class Storages {
  public:
    typedef storage::Vector<Int, SIZE>::Type List;
    
    int N;
    List A;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
    }
    
    Int test_sum( const Storages::List& A_, const int& N ) {
      Storages::List A = A_;
      A.sort(0, N);
      Int cur_sum = A.sum(0, N);
      Int sum = 0;
      for ( Int i = 0; i < N; ++ i ) {
        Int k = i + 1;
        cur_sum -= A[i] * ( Int(N) - k );
        sum += cur_sum * 2;
      }
      return sum;
    }
    
    Int test_sum_2( const Storages::List& A_, const int& N ) {
      Storages::List A = A_;
      A.sort(0, N);
      Int sum_total = A.sum(0, N) * N;
      Int sum = 0;
      for ( Int i = 0; i < N; ++ i ) {
        Int k = i + 1;
        sum += A[i] * ( Int(N) - k );
        sum_total -= sum;
      }
      return sum_total * 2;
    }
    
  protected:
    
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
      if ( ! ( std::cin >> s.N ) )
        return false;
      for ( int i = 0; i < s.N; ++ i )
        std::cin >> s.A[i];
      return true;
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



