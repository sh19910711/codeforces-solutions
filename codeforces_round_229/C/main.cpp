
// @snippet<sh19910711/contest-base:headers.cpp>
#define __THIS_IS_CPP11__
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

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif


// @snippet<sh19910711/contest:utils/collection_prototype.cpp>
namespace utils {
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class Iterator, class Value> void fill( Iterator, const int&, const Value& );
  
  // copy(from, num, to)
  template <class Iterator> void copy( const Iterator& from, const int& num, Iterator& to );
  
  // sort(begin, num)
  template <class Iterator> void sort( Iterator begin, const int& n );
  
  // reverse(begin, num)
  template <class Iterator> void reverse( Iterator begin, const int& n );
  
#endif
}

// @snippet<sh19910711/contest:utils/misc_prototype.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b );
  template <class T> void min( T& a, const T& b );
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v );
  template <class T> T to_type( const std::string& s );
  
}

// @snippet<sh19910711/contest:utils_prototypes.cpp>

// @snippet<sh19910711/contest-base:solution/template-class.cpp>
namespace solution {
  struct Input;
  struct Output;
  struct Storages {
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const Output* solve( const Input* in, Output* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    virtual bool action() = 0;
    virtual bool input( Input* s ) = 0;
    virtual void output( const Output* s ) = 0;
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    SolverInterface* solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    
    int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
    
    bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-primitive-types.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 100000 + 11;
  const Int MAX_K = 10 + 1;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace utils;
  typedef std::array<Int, SIZE> IntArray;
  typedef std::array<IntArray, MAX_K> IntTable;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct Input {
    Int N;
    Int K;
    Int W;
    String S;
    IntArray L;
    IntArray R;
  };
  
  struct Output {
    Int W;
    IntArray result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Counter {
    IntTable cnt_one;
    IntTable sum_one;
    IntTable cnt_zero;
    IntTable sum_zero;

    IntArray A;

    void init() {
      for ( auto& line : cnt_one ) {
        fill(std::begin(line), SIZE, 0);
      }
      for ( auto& line : sum_one ) {
        fill(std::begin(line), SIZE, 0);
      }
      for ( auto& line : cnt_zero ) {
        fill(std::begin(line), SIZE, 0);
      }
      for ( auto& line : sum_zero ) {
        fill(std::begin(line), SIZE, 0);
      }
      init_a();
    }

    void init_a() {
      for ( auto i = 0; i < in->N; ++ i ) {
        A[i] = in->S[i] == '1' ? 1 : 0;
      }
    }

    Int get_prev_sum_one( const Int& mod, const Int& k ) {
      if ( k == 0 )
        return 0;
      return sum_one[mod][k - 1];
    }

    Int get_prev_sum_zero( const Int& mod, const Int& k ) {
      if ( k == 0 )
        return 0;
      return sum_zero[mod][k - 1];
    }

    void count() {
      count_one();
      count_zero();
    }

    void debug_print_table( IntTable& t ) {
      for ( auto m = 0; m < in->K; ++ m ) {
        std::cout << "m = " << m << ": ";
        for ( auto i = 0; i < in->N; ++ i ) {
          std::cout << t[m][i] << " ";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }

    void debug() {
      std::cout << "sum_one: " << std::endl; debug_print_table(sum_one);
      std::cout << "sum_zero: " << std::endl; debug_print_table(sum_zero);
    }

    void count_one() {
      for ( auto i = 0; i < in->N; ++ i ) {
        if ( A[i] == 1 )
          cnt_one[i % in->K][i] ++;
      }
      for ( auto m = 0; m < in->K; ++ m ) {
        for ( auto i = 0; i < in->N; ++ i ) {
          sum_one[m][i] = get_prev_sum_one(m, i) + cnt_one[m][i];
        }
      }
    }

    void count_zero() {
      for ( auto i = 0; i < in->N; ++ i ) {
        if ( A[i] == 0 ) {
          for ( auto m = 0; m < in->K; ++ m ) {
            if ( i % in->K != m ) {
              cnt_zero[m][i] ++;
            }
          }
        }
      }
      for ( auto m = 0; m < in->K; ++ m ) {
        for ( auto i = 0; i < in->N; ++ i ) {
          sum_zero[m][i] = get_prev_sum_zero(m, i) + cnt_zero[m][i];
        }
      }
    }

    const Input* in;
    Counter( const Input* in ): in(in) { init(); }
    typedef std::unique_ptr<Counter> Pointer;
    static Pointer create( const Input* in ) { return Pointer(new Counter(in)); }
  };

  struct Query {
    IntTable cnt_one;
    IntTable sum_one;
    IntTable cnt_zero;
    IntTable sum_zero;

    Int mod;
    IntArray result;

    void init() {
    }

    void proc() {
      proc_queries();
    }

    void proc_queries() {
      for ( auto i = 0; i < in->W; ++ i ) {
        result[i] = proc_query(in->L[i] - 1, in->R[i] - 1);
      }
    }

    // (l, r]
    Int get_sum_one( const Int& l, const Int& r ) {
      return sum_one[mod][r] - sum_one[mod][l];
    }

    // (l, r]
    Int get_sum_zero( const Int& l, const Int& r ) {
      return sum_zero[mod][r] - sum_zero[mod][l];
    }

    Int proc_query( const Int& l, const Int& r ) {
      mod = l % in->K;
      auto ret_one = get_sum_one(l, r);
      auto ret_zero = get_sum_zero(l, r);
      auto bad_one = std::max(Int(0), ( r - l - 1 ) / in->K) - ret_one;
      auto bad_zero = r - l - 1 - std::max(Int(0), ( r - l - 1 ) / in->K) - ret_zero;
      return bad_one + bad_zero + ( in->S[l] == '1' ? 1 : 0 );
    }

    const Input* in;
    Query( const Input* in ): in(in) { init(); }
    typedef std::unique_ptr<Query> Pointer;
    static Pointer create( const Input* in ) { return Pointer(new Query(in)); }
  };

  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      out->W = in->W;
      if ( in->N == 1 ) {
        out->result[0] = 1;
        if ( in->S[0] == '1' )
          out->result[0] = 0;
        return out;
      }
      auto counter = Counter::create(in);
      counter->count();
      auto query = Query::create(in);
      query->cnt_one = counter->cnt_one;
      query->sum_one = counter->sum_one;
      query->cnt_zero = counter->cnt_zero;
      query->sum_zero = counter->sum_zero;
      query->proc();
      out->result = query->result;
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->N >> in->K >> in->W ) )
        return false;
      if ( ! ( std::cin >> in->S ) )
        return false;
      for ( auto i = 0; i < in->W; ++ i )
        if ( ! ( std::cin >> in->L[i] >> in->R[i] ) )
          return false;
      return true;
    }
    void output( const Output* out ) {
      for ( auto i = 0; i < out->W; ++ i )
        std::cout << out->result[i] << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base:main_func.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  // desc: http://meme.biology.tohoku.ac.jp/students/iwasaki/cxx/speed.html#id18
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  // 
  using namespace solution;
  static Input      in;
  static Output     out;
  static Storages   storages;
  static Solution   solution;
  static Solver     solver;
  storages.in       = &in;
  storages.out      = &out;
  solution.storages = &storages;
  solution.solver   = &solver;
  return solution.run();
}
#endif

// @snippet<sh19910711/contest:utils/collection.cpp>
namespace utils {
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class Iterator, class V> void fill( Iterator begin, const int& num, const V& value ) {
    std::fill(begin, begin + num, value);
  }
  
  // copy(from, num, to)
  template <class Iterator> void copy( const Iterator from, const int& num, Iterator to ) {
    std::copy(from, from + num, to);
  }
  
  // sort(begin, num)
  template <class Iterator> void sort( Iterator begin, const int& num ) {
    std::sort(begin, begin + num);
  }
  
  // reverse(begin, num)
  template <class Iterator> void reverse( Iterator begin, const int& num ) {
    std::reverse(begin, begin + num);
  }
  
#endif
}

// @snippet<sh19910711/contest:utils/misc.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b ) { a = std::max(a, b); }
  template <class T> void min( T& a, const T& b ) { a = std::min(a, b); }
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v ) { std::ostringstream oss; oss << v; return oss.str(); }
  template <class T> T to_type( const std::string& s ) { std::istringstream iss(s); T res; iss >> res; return res; }
  
}

// @snippet<sh19910711/contest:utils.cpp>

// @snippet<sh19910711/contest-base:main.cpp>

