
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
  typedef unsigned long long Int;


  const int hash_bases_num = 6;
  const Int hash_bases[hash_bases_num] = { 89, 97, 61, 67, 223, 227 };

  class Hash {
  public:
    Int hashs[hash_bases_num];

    Hash() {
      for ( int i = 0; i < hash_bases_num; ++ i )
        hashs[i] = 0;
    }

    void add( Int value ) {
      for ( int i = 0; i < hash_bases_num; ++ i )
        hashs[i] = hashs[i] * hash_bases[i] + value;
    }

    friend bool operator == ( const Hash& l, const Hash& r ) {
      for ( int i = 0; i < hash_bases_num; ++ i )
        if ( l.hashs[i] != r.hashs[i] )
          return false;
      return true;
    }

    friend bool operator != ( const Hash& l, const Hash& r ) {
      return ! ( operator == (l, r) );
    }

    friend ostream& operator << ( ostream& os, const Hash& hash ) {
      os << "{";
      for ( int i = 0; i < hash_bases_num; ++ i )
        os << hash.hashs[i] << ", ";
      os << "}";
      return os;
    }
  };
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE   = 100 + 11;
  const string YES = "YES";
  const string NO  = "NO";
  // storages
  int n, k;
  Int Q[SIZE];
  Int S[SIZE];
  Hash hash_s;

  Int T[SIZE];

  Int P[SIZE];
  Hash hash_p;
  Hash hash_p_first;
  Int tmp[SIZE];

  bool result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();

      calc_table_t();
      calc_hash_s();

      result = check();
    }

    void print_array( Int* arr, int n ) {
      for ( int i = 0; i < n; ++ i ) {
        cout << arr[i] << ", ";
      }
      cout << endl;
    }

    void calc_table_t() {
      for ( int i = 0; i < n; ++ i ) {
        P[i] = i;
      }
      for ( int i = 0; i < n; ++ i ) {
        tmp[Q[i]] = P[i];
      }
      for ( int i = 0; i < n; ++ i ) {
        T[i] = tmp[i];
      }
    }

    void normalize() {
      for ( int i = 0; i < n; ++ i ) {
        Q[i] --;
        S[i] --;
      }
    }

    void calc_hash_s() {
      hash_s = Hash();
      for ( int i = 0; i < n; ++ i )
        hash_s.add(S[i]);
    }

    bool check() {
      if ( is_invalid_case() )
        return false;

      if ( is_invalid_case_k() )
        return false;

      return true;
    }

    bool is_invalid_case() {
      for ( int i = 0; i < n; ++ i )
        P[i] = i;

      hash_p = Hash();
      for ( int i = 0; i < n; ++ i )
        hash_p.add(P[i]);
      hash_p_first = hash_p;

      if ( hash_p_first == hash_s )
        return true;

      do {
        get_next_permutation_p();
        if ( hash_p == hash_s )
          return false;
      } while ( hash_p != hash_p_first );

      return true;
    }

    bool is_invalid_case_k() {
      int left_rolls  = get_minimum_operations_a();
      int right_rolls = get_minimum_operations_b();

      if ( left_rolls == 1 && right_rolls == 1 )
        return k != 1;

      if ( k >= left_rolls && k % 2 == left_rolls % 2 )
        return false;

      if ( k >= right_rolls && k % 2 == right_rolls % 2 )
        return false;
 
      return true;
    }

    int get_minimum_operations_a() {
      for ( int i = 0; i < n; ++ i )
        P[i] = i;

      hash_p = Hash();
      for ( int i = 0; i < n; ++ i )
        hash_p.add(P[i]);

      int res = 0;
      while ( hash_p != hash_s ) {
        get_next_permutation_p();
        res ++;
      }
      return res;
    }

    int get_minimum_operations_b() {
      for ( int i = 0; i < n; ++ i )
        P[i] = i;

      hash_p = Hash();
      for ( int i = 0; i < n; ++ i )
        hash_p.add(P[i]);

      int res = 0;
      while ( hash_p != hash_s ) {
        get_next_permutation_p_rev();
        res ++;
      }
      return res;
    }

    void get_next_permutation_p() {
      for ( int i = 0; i < n; ++ i ) {
        tmp[Q[i]] = P[i];
      }
      for ( int i = 0; i < n; ++ i ) {
        P[i] = tmp[i];
      }

      hash_p = Hash();
      for ( int i = 0; i < n; ++ i ) {
        hash_p.add(P[i]);
      }
    }

    void get_next_permutation_p_rev() {
      for ( int i = 0; i < n; ++ i ) {
        tmp[T[i]] = P[i];
      }
      for ( int i = 0; i < n; ++ i ) {
        P[i] = tmp[i];
      }

      hash_p = Hash();
      for ( int i = 0; i < n; ++ i ) {
        hash_p.add(P[i]);
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
    }

    bool input() {
      if ( ! ( cin >> n >> k ) )
        return false;
      for ( int i = 0; i < n; ++ i )
        cin >> Q[i];
      for ( int i = 0; i < n; ++ i ) 
        cin >> S[i];
      return true;
    }

    void output() {
      cout << ( result ? YES : NO ) << endl << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

