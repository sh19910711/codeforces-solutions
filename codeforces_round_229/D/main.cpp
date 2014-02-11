
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
  const Int MAX_N = 100 + 11;
  const Int MAX_K = MAX_N * MAX_N + 11;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace utils;

  typedef std::tuple<Int, Int> PosBase;
  struct Pos: PosBase {
    // using PosBase::tuple;

    Pos() {}

    Pos( const Int& r, const Int& c ) {
      this->get_row() = r;
      this->get_col() = c;
    }
    
    Pos( const Pos& pos ) {
      *this = pos;
    }

    Int& get_row() { return std::get<0>(*this); }
    const Int& get_row() const { return std::get<0>(*this); }
    Int& get_col() { return std::get<1>(*this); }
    const Int& get_col() const { return std::get<1>(*this); }
  };
  Pos POS_NONE;

  typedef std::vector<Pos> Path;
  typedef std::array<Path, MAX_K> Paths;
  typedef std::array<Pos, MAX_N> PosArray;
  typedef std::array<PosArray, MAX_N> PosMatrix;
  typedef std::array<Pos, MAX_K> VisitOrder;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int K;
  };
  
  struct Output {
    Int K;
    Int min_penalty;
    Paths paths;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Search {
    typedef std::array<bool, MAX_N> BoolArray;
    typedef std::array<BoolArray, MAX_N> BoolMatrix;
    typedef std::queue <Pos> Queue;

    PosMatrix prev;
    BoolMatrix used;
    VisitOrder visit_order;
    Int cnt;

    void init() {
      for ( auto i = 0; i < MAX_N; ++ i ) {
        for ( auto j = 0; j < MAX_N; ++ j ) {
          prev[i][j] = POS_NONE;
          used[i][j] = false;
        }
      }
      cnt = 0;
    }

    void search() {
      Queue Q;
      used[0][0] = true;
      Q.push(Pos(0, 0));

      auto limit = in->N * in->M;
      while ( cnt < limit && ! Q.empty() ) {
        const Pos& pos = Q.front();
        Q.pop();
        const int dr[4] = {1, -1, 0, 0};
        const int dc[4] = {0, 0, 1, -1};

        visit_order[cnt] = pos;
        cnt ++;

        // std::cout << "pos: r = " << pos.get_row() << ", c = " << pos.get_col() << ", cnt = " << cnt << std::endl;

        for ( int k = 0; k < 4; ++ k ) {
          int nr = pos.get_row() + dr[k];
          int nc = pos.get_col() + dc[k];
          if ( nr < 0 || nr >= in->N || nc < 0 || nc >= in->M )
            continue;
          if ( used[nr][nc] )
            continue;
          used[nr][nc] = true;
          prev[nr][nc] = pos;
          if ( cnt >= limit )
            continue;
          Q.push(Pos(nr, nc));
        }
      }
    }

    const Input* in;
    Search( const Input* in ): in(in) { init(); }
    typedef std::unique_ptr<Search> Pointer;
    static Pointer create( const Input* in ) { return Pointer(new Search(in)); }
  };

  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      POS_NONE.get_row() = -1;
      POS_NONE.get_col() = -1;
      for ( auto& path : out->paths ) path.clear();

      out->K = in->K;
      auto search = Search::create(in);
      search->search();

      Int len = 0;
      Int cnt = 0;
      for ( auto i = in->K - 1; i >= 0; -- i ) {
        len += generate_path(search->prev, search->visit_order[i], out->paths[cnt]);
        ++ cnt;
      }
      out->min_penalty = len;

      return out;
    }

    Int generate_path( const PosMatrix& prev, const Pos& start, Path& path ) {
      Pos cur = start;
      while ( cur != POS_NONE ) {
        path.push_back(cur);
        cur = prev[cur.get_row()][cur.get_col()];
      }
      std::reverse(std::begin(path), std::end(path));
      return path.size();
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      return std::cin >> in->N >> in->M >> in->K;
    }
    void output( const Output* out ) {
      std::cout << out->min_penalty << std::endl;
      for ( auto i = 0; i < out->K; ++ i ) {
        output_path(out->paths[i]);
      }
    }
    void output_path( const Path& path ) {
      for ( auto pos : path ) {
        std::cout << "(" << pos.get_row() + 1 << "," << pos.get_col() + 1 << ") ";
      }
      std::cout << std::endl;
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

