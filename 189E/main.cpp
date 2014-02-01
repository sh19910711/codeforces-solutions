
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


// @snippet<sh19910711/contest:search/search_interface.cpp>
namespace search {
  template <class Node> class SearchInterface {
  public:
    virtual Node search() = 0;
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search_interface.cpp>
namespace search {
  template <class Node> class BreadthFirstSearchInterface: public SearchInterface<Node> {
  public:
    virtual Node search()                            = 0;
  protected:
    virtual void init()                              = 0;
    virtual bool has_next_node()                     = 0;
    virtual void visit_next_node( const Node& node ) = 0;
    virtual void push_next_node( const Node& node )  = 0;
    virtual Node get_next_node()                     = 0;
    virtual Node get_none_node()                     = 0;
    virtual bool is_visited_node( const Node& node ) = 0;
    virtual void set_visited( const Node& node )     = 0;
    virtual bool is_goal_node( const Node& node )    = 0;
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search_base.cpp>
namespace search {
  template <class Node> class BreadthFirstSearchBase: public BreadthFirstSearchInterface<Node> {
  public:
    Node search() {
      Node res = this->get_none_node();
      this->init();
      while ( this->has_next_node() ) {
        Node node = this->get_next_node();
        if ( this->is_goal_node(node) )
          res = node;
        this->visit_next_node(node);
      }
      return res;
    }
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search.cpp>
namespace search {
  template <class Node> class BreadthFirstSearch: public BreadthFirstSearchBase<Node> {
  protected:
    virtual void init() {}
    
    bool has_next_node() {
      return ! Q.empty();
    }
    
    Node get_next_node() {
      Node res = Q.front();
      Q.pop();
      return res;
    }
    
    void push_next_node( const Node& node ) {
      if ( this->is_visited_node(node) )
        return;
      Q.push(node);
      this->set_visited(node);
    }
    
  protected:
    std::queue <Node> Q;
  };
}

// @snippet<sh19910711/contest:utils/debug.cpp>
namespace utils {
  namespace aux{
    template<std::size_t...> struct seq{};
    
    template<std::size_t N, std::size_t... Is>
    struct gen_seq : gen_seq<N-1, N-1, Is...>{};
    
    template<std::size_t... Is>
    struct gen_seq<0, Is...> : seq<Is...>{};
    
    template<class Ch, class Tr, class Tuple, std::size_t... Is>
    void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, seq<Is...>){
      using swallow = int[];
      (void)swallow{0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)...};
    }
  } // ::aux
  
  template<class Ch, class Tr, class... Args>
  auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) -> std::basic_ostream<Ch, Tr>& {
    os << "(";
    aux::print_tuple(os, t, aux::gen_seq<sizeof...(Args)>());
    return os << ")";
  }
  
}

// @snippet<sh19910711/contest-base:solution/template-primitive-types.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 100000 + 11;
  const Int NONE = -1;
  const Int INF = std::numeric_limits<Int>::max();
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  using namespace utils;
  typedef std::array<Int, SIZE> IntArray;
  typedef std::array<Int, 2 * SIZE> Edges;
  typedef std::array<bool, SIZE> BoolArray;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int M;
    Int K;
    IntArray volunteers;
    Edges U;
    Edges V;
    Int S;
    Int T;
  };
  
  struct OutputStorage {
    Int result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  typedef std::tuple<Int, Int> NodeBase;
  struct Node: NodeBase {
    Node() {}
    // Node(const NodeBase& node) {*this = node;}
    // using NodeBase::tuple;
    Int& get_steps() { return std::get<0>(*this); }
    const Int& get_steps() const { return std::get<0>(*this); }
    Int& get_id() { return std::get<1>(*this); }
    const Int& get_id() const { return std::get<1>(*this); }
  };
  typedef std::vector <Int> IndexList;
  typedef std::array<IndexList, SIZE> AdjacentList;
  
  
  struct Search: search::BreadthFirstSearch<Node> {
    Node NODE_NONE;
    AdjacentList G;
    BoolArray is_volunteers;
    IntArray dist;
    Int goal_id;
    Int limit;
    
    void init() {
      NODE_NONE.get_id() = NONE;
      NODE_NONE.get_steps() = NONE;
      init_volunteers();
      init_graph();
      goal_id = in->T - 1;
      Node start_node;
      start_node.get_steps() = 0;
      start_node.get_id() = in->S - 1;
      this->push_next_node(start_node);
    }

    void init_volunteers() {
      fill(is_volunteers, false);
      for ( auto i = 0; i < in->K; ++ i ) {
        is_volunteers[in->volunteers[i] - 1] = true;
      }
    }

    void init_graph() {
      for ( auto i = 0; i < in->M; ++ i ) {
        auto u = in->U[i] - 1;
        auto v = in->V[i] - 1;
        G[u].push_back(v);
        G[v].push_back(u);
      }
    }

    void init_dist() {
      fill(begin(dist), end(dist), std::numeric_limits<Int>::max());
    }
    
    void visit_next_node( const Node& node ) {
      const Int& from = node.get_id();
      for ( auto to : G[from] ) {
        Node next_node;
        next_node.get_steps() = node.get_steps() + 1;
        if ( next_node.get_steps() > limit )
          continue;
        if ( is_volunteers[to] )
          next_node.get_steps() = 0;
        next_node.get_id() = to;
        this->push_next_node(next_node);
      }
    }
    
    Node get_none_node() {
      return NODE_NONE;
    }
    
    bool is_visited_node( const Node& node ) {
      return node.get_steps() >= dist[node.get_id()];
    }
    
    void set_visited( const Node& node ) {
      dist[node.get_id()] = node.get_steps();
    }
    
    bool is_goal_node( const Node& node ) {
      return node.get_id() == goal_id;
    }
    
    const InputStorage* in;
    Search(const InputStorage* in): in(in) { init(); }
  };
  typedef std::unique_ptr<Search> SearchPointer;
  
  struct Solver: SolverInterface {
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      auto search = SearchPointer(new Search(in));
      Int res = INF;
      Int lb = -1;
      Int ub = in->N + 1;
      while ( ub - lb > 1 ) {
        Int mid = ( lb + ub ) * 0.5;
        search->limit = mid;
        search->init_dist();
        auto ret = search->search();
        if ( ret.get_steps() != NONE ) {
          res = std::min(res, mid);
          ub = mid;
        } else {
          lb = mid;
        }
      }
      out->result = res;
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->M >> in->K ) )
        return false;
      for ( auto i = 0; i < in->K; ++ i )
        if ( ! ( std::cin >> in->volunteers[i] ) )
          return false;
      for ( auto i = 0; i < in->M; ++ i )
        if ( ! ( std::cin >> in->U[i] >> in->V[i] ) )
          return false;
      if ( ! ( std::cin >> in->S >> in->T ) )
        return false;
      return true;
    }
    void output( const OutputStorage* out ) {
      if ( out->result == INF ) {
        std::cout << NONE << std::endl;
      } else {
        std::cout << out->result << std::endl;
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



