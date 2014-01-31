
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
  const Int SIZE = 200000 + 11;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  using namespace utils;
  typedef std::array<Int, SIZE> IntArray;
  typedef std::array<bool, SIZE> BoolArray;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    IntArray C;
    IntArray S;
    Int M;
    IntArray D;
    IntArray L;

    template <class Func> void for_each_customer( Func f ) const {
      for ( auto i = 0; i < this->M; ++ i ) {
        f(i);
      }
    }

    template <class Func> void for_each_shoe( Func f ) const {
      for ( auto i = 0; i < this->N; ++ i ) {
        f(i);
      }
    }
  };
  
  struct OutputStorage {
    Int max_cost;
    Int customers;
    IntArray A;
    IntArray B;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  enum EdgeIndex {EDGE_TO, EDGE_COST};
  typedef std::tuple <Int, Int> Edge; // (to, cost)

  struct Graph {
    static const Int MAX_V = SIZE;
    typedef std::vector<Edge> IndexList;
    typedef std::array<IndexList, MAX_V> AdjacentList;

    // adj_list[from][to]
    AdjacentList adj_list;

    void add_edge( const Int& from, const Int& to, const Int& cost ) {
      adj_list[from].push_back(Edge {to, cost});
    }
  };

  struct FindGraph {
    enum ShoeInfoIndex {SHOE_SIZE, SHOE_ID};
    typedef std::tuple <Int, Int> ShoeInfo; // (size, shoe_id)
    typedef std::set <ShoeInfo> ShoeSet;

    ShoeSet shoe_set;
    Graph graph;

    void init() {
      for ( auto i = 0; i < in->N; ++ i ) {
        shoe_set.insert(ShoeInfo {in->S[i], i});
      }
    }

    Int get_shoe_index( const Int& shoe_id ) {
      return shoe_id;
    }

    Int get_customer_index( const Int& customer_id ) {
      return in->N + customer_id;
    }

    void find_good_shoes( const Int& customer_id ) {
      auto money     = in->D[customer_id];
      auto need_size = in->L[customer_id];
      auto it_begin  = shoe_set.lower_bound(ShoeInfo {need_size, -1});
      for ( auto it_i = it_begin; it_i != shoe_set.end(); ++ it_i ) {
        auto shoe_id   = std::get<ShoeInfoIndex::SHOE_ID>(*it_i);
        auto shoe_size = in->S[shoe_id];
        auto shoe_cost = in->C[shoe_id];
        if ( shoe_size - need_size > 1 )
          break;
        if ( shoe_cost > money )
          continue;
        graph.add_edge(get_shoe_index(shoe_id), get_customer_index(customer_id), shoe_cost);
        // cout << "customer: " << customer_id << endl; cout << "need = " << need_size << " / shoe begin: id = " << shoe_id << ", size = " << shoe_size << endl; cout << "money: " << money << " >= cost: " << shoe_cost << endl;
      }
    }

    const Graph* find() {
      in->for_each_customer(
        [&]( const Int& id ){find_good_shoes(id);}
      );
      return &graph;
    }

    const InputStorage* in;
    FindGraph(const InputStorage* in): in(in) { init(); }
  };
  typedef std::unique_ptr<FindGraph> FindGraphPointer;


  struct Matching {
    const Int MATCH_NONE = -1;

    const Graph* G;
    Int v_num;
    IntArray match;
    BoolArray used;

    Int customers;
    IntArray A;
    IntArray B;

    void init() {
      v_num = in->N + in->M;
      std::cout << "@Matching#init 1" << std::endl;
      std::fill(begin(match), end(match), MATCH_NONE);
      // TODO: fill(match, MATCH_NONE);
    }

    bool dfs( const Int& v ) {
      used[v] = true;
      // TODO: G.get(v).size()
      for ( auto i = 0; i < G->adj_list[v].size(); ++ i ) {
        // TODO: G.get(v)[i]
        auto e = G->adj_list[v][i];
        auto u = std::get<EdgeIndex::EDGE_TO>(e);
        auto w = match[u];
        if ( w < 0 || ( ! used[w] && dfs(w) ) ) {
          match[v] = u;
          match[u] = v;
          return true;
        }
      }
      return false;
    }

    Int do_bipartite_matching() {
      Int res = 0;
      for ( auto v = 0; v < in->N; ++ v ) {
        if ( match[v] == MATCH_NONE ) {
          fill(used, false);
          if ( dfs(v) )
            res ++;
        }
      }
      return res;
    }

    Int calc_max_cost() {
      Int res = 0;
      customers = 0;
      for ( auto shoe_id = 0; shoe_id < in->N; ++ shoe_id ) {
        auto shoe_cost = in->C[shoe_id];
        auto customer_id = match[shoe_id];
        if ( customer_id != MATCH_NONE ) {
          res += shoe_cost;
          A[customers] = customer_id + 1 - in->N;
          B[customers] = shoe_id + 1;
          customers ++;
        }
      }
      return res;
    }

    const InputStorage* in;
    Matching(const InputStorage* in): in(in) { init(); }
  };
  typedef std::unique_ptr<Matching> MatchingPointer;


  struct Solver: SolverInterface {
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      auto find_graph = FindGraphPointer(new FindGraph(in));
      auto g = find_graph->find();

      auto matching = MatchingPointer(new Matching(in));
      matching->G = g;
      out->customers = matching->do_bipartite_matching();
      out->max_cost = matching->calc_max_cost();
      copy(matching->A, out->A);
      copy(matching->B, out->B);

      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        std::cin >> in->C[i] >> in->S[i];
      if ( ! ( std::cin >> in->M ) )
        return false;
      for ( auto i = 0; i < in->M; ++ i )
        std::cin >> in->D[i] >> in->L[i];
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << out->max_cost << std::endl;
      std::cout << out->customers << std::endl;
      for ( auto i = 0; i < out->customers; ++ i )
        std::cout << out->A[i] << " " << out->B[i] << std::endl;
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

