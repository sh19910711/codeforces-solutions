
// @snippet<sh19910711/contest-base:headers.cpp>
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

#define __THIS_IS_CPP11__
#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif


// @snippet<sh19910711/contest-base:utils/collection.cpp>
namespace utils {
  // fill(A), fill(A, num), fill(A, num, value)
  template <class T> void fill( T& v ) { std::fill(std::begin(v), std::end(v), 0); }
  template <class T> void fill( T& v, const int& n ) { std::fill(std::begin(v), std::begin(v) + n, 0); }
  template <class T, class V> void fill( T& v, const int& n, const V& value ) { std::fill(std::begin(v), std::begin(v) + n, value); }
  // copy(from, to), copy(from, num, to)
  template <class T> void copy( const T& s, T& t ) { std::copy(std::begin(s), std::end(s), std::begin(t)); }
  template <class T> void copy( const T& s, const int& n, T& t ) { std::copy(std::begin(s), std::begin(s) + n, std::begin(t)); }
  // sort(A), sort(A, num)
  template <class T> void sort( T& v ) { std::sort(std::begin(v), std::end(v)); }
  template <class T> void sort( T& v, const int& n ) { std::sort(std::begin(v), std::begin(v) + n); }
}

// @snippet<sh19910711/contest-base:solution/template-class.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    SolverInterface* solver;
    Storages* storages;
    virtual int run() = 0;
    virtual bool input( InputStorage* s ) = 0;
    virtual void output( const OutputStorage* s ) = 0; 
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    virtual bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    virtual int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-primitive-types.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int MAX_N = 5 * 100000 + 11;
  const Int MAX_M = 1000000 + 11;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  using namespace utils;
  typedef std::array<Int, MAX_M> Vertices;
  typedef std::vector<Int> GroupVertices;
  typedef std::array<GroupVertices, MAX_N> Groups;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int M;
    Vertices A;
    Vertices B;
  };
  
  struct OutputStorage {
    Int groups_cnt;
    Groups groups;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Find {
    typedef std::array<Int, MAX_N> IntArray;
    typedef std::array<bool, MAX_N> BoolArray;
    typedef std::vector<Int> Vertices;
    typedef std::array<Vertices, MAX_N> AdjacentList;
    typedef std::queue <Int> Queue;

    Int groups_cnt;
    Groups groups;

    AdjacentList G;
    IntArray D;
    AdjacentList cand;
    BoolArray used;
    IntArray L;
    IntArray R;

    void init() {
      groups_cnt = 0;
      for ( auto& g : groups ) g.clear();
      init_graph();
      for ( auto& u : used ) u = false;
      for ( auto i = 0; i <= in->N; ++ i ) {
        L[i] = i - 1;
        R[i] = i + 1;
      }
    }

    void init_graph() {
      for ( auto& g : G ) g.clear();
      for ( auto& d : D ) d = 0;
      for ( auto i = 0; i < in->M; ++ i ) {
        auto a = in->A[i] - 1;
        auto b = in->B[i] - 1;
        G[a].push_back(b);
        G[b].push_back(a);
        D[a] ++;
        D[b] ++;
      }
      for ( auto i = 0; i < in->N; ++ i ) {
        std::sort(begin(G[i]), end(G[i]));
      }
      for ( auto& c : cand ) c.clear();
      for ( auto i = 0; i < in->N; ++ i ) {
        cand[D[i]].push_back(i);
      }
    }

    void find() {
      for ( auto i = 0; i < in->N; ++ i ) {
        for ( auto v : cand[i] ) {
          if ( used[v] ) 
            continue;
          search(v);
          groups_cnt ++;
        }
      }
    }

    void remove( const Int& x ) {
      // x-1, x, x+1 -> x-1, x+1
      used[x - 1] = true;
      auto l = L[x];
      auto r = R[x];
      L[r] = l;
      R[l] = r;
    }

    void print_r() {
      for ( int i = 0; i <= in->N; ++ i )
        cout << i << ": " << L[i] << " - " << R[i] << endl;
      cout << endl;
    }

    void search( const Int& start ) {
      Queue Q;
      Q.push(start);
      groups[groups_cnt].push_back(start);
      remove(start + 1);

      while ( ! Q.empty() ) {
        const Int& v = Q.front();
        Q.pop();
        for ( auto t = R[0]; t <= in->N; t = R[t] ) {
          auto u = t - 1;
          if ( ! std::binary_search(begin(G[v]), end(G[v]), u) ) {
            Q.push(u);
            groups[groups_cnt].push_back(u);
            remove(t);
          }
        }
      }
    }

    const InputStorage* in;
    Find(const InputStorage* in): in(in) { init(); }
  };
  typedef std::unique_ptr<Find> FindPointer;

  struct Solver: SolverInterface {
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      init_groups(out); 
      auto find = FindPointer(new Find(in));
      find->find();
      out->groups_cnt = find->groups_cnt;
      std::copy(begin(find->groups), begin(find->groups) + find->groups_cnt, begin(out->groups));
      return out;
    }
    static void init_groups( OutputStorage* out ) {
      out->groups_cnt = 0;
      for ( auto& g : out->groups ) g.clear();
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->M ) )
        return false;
      for ( auto i = 0; i < in->M; ++ i )
        if ( ! ( std::cin >> in->A[i] >> in->B[i] ) )
          return false;
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << out->groups_cnt << std::endl;
      for ( auto i = 0; i < out->groups_cnt; ++ i ) {
        std::cout << out->groups[i].size() << " ";
        for ( auto v : out->groups[i] ) {
          std::cout << v + 1 << " ";
        }
        std::cout << std::endl;
      }
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  using namespace solution;
  std::cin.sync_with_stdio(false);
  static InputStorage in;
  static OutputStorage out;
  static Storages storages;
  static Solution solution;
  static Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif

