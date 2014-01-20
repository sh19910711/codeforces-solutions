
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
  struct InputStorage;
  struct OutputStorage;
  struct DataStorage;
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
    virtual bool action() = 0;
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
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
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

namespace setlib {
  // TODO: update
  class DisjointSets {
  public:
    std::vector<int> data;
    DisjointSets() {}
    DisjointSets( int size ): data(size, -1) {};
    void init( int size ) { data.resize(size); std::fill( data.begin(), data.end(), -1 ); }
    bool merge( int x, int y ) {
      x = root(x), y = root(y);
      if ( x != y ) {
        if ( data[y] < data[x] ) std::swap( x, y );
        data[x] += data[y], data[y] = x;
      }
      return x != y;
    }
    bool same( int x, int y ) { return root(x) == root(y); }
    int root( int x ) { return data[x] < 0 ? x : data[x] = root(data[x]); }
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const Int SIZE = 100000 + 11;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef setlib::DisjointSets UnionFind;
  typedef std::vector<int> Indexes;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  enum EdgeType {
    SANTA,
    ELF
  };

  struct Edge {
    Int from;
    Int to;
    EdgeType type;
  };

  struct InputStorage {
    Int N;
    Int M;
    Edge edges[SIZE];
  };
  
  struct OutputStorage {
    bool result;
    Indexes indexes;
  };
  
  struct DataStorage {
    UnionFind uf;
    bool used[SIZE];
  };
  
  struct Storages {
    InputStorage  in;
    OutputStorage out;
    DataStorage   data;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      out.result = generate_graph(in, out, data);
      return out;
    }
    
  protected:
    static bool generate_graph( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      if ( in.N % 2 == 0 ) {
        return false;
      }
      out.indexes.clear();
      std::fill(data.used, data.used + SIZE, false);

      Int needs = ( in.N - 1 ) / 2;

      data.uf.init(in.N);
      for ( int i = 0; i < in.M; ++ i ) {
        if ( in.edges[i].type == ELF ) {
          data.uf.merge(in.edges[i].from, in.edges[i].to);
        }
      }
      Indexes ret2 = generate_graph_2(in.M, in.edges, data.uf, data.used);

      data.uf.init(in.N);
      for ( int i = 0; i < ret2.size(); ++ i ) {
        data.uf.merge(in.edges[ret2[i]].from, in.edges[ret2[i]].to);
      }
      if ( ret2.size() > needs ) {
        return false;
      }

      Int remains = needs - ret2.size();
      data.uf.init(in.N);
      Indexes ret3 = generate_graph_3(in.M, in.edges, data.uf, data.used, remains);
      Indexes ret1 = generate_graph_1(in.M, in.edges, data.uf, data.used);
      out.indexes.insert(out.indexes.end(), ret1.begin(), ret1.end());
      out.indexes.insert(out.indexes.end(), ret2.begin(), ret2.end());
      out.indexes.insert(out.indexes.end(), ret3.begin(), ret3.end());

      if ( ret1.size() != needs ) {
        return false;
      }

      return out.indexes.size() == in.N - 1;
    }

    static Indexes generate_graph_3( const Int& m, const Edge edges[SIZE], UnionFind& uf, bool used[SIZE], int remains ) {
      Indexes res;
      for ( int i = 0; i < m; ++ i ) {
        if ( remains <= 0 ) {
          continue;
        }
        if ( used[i] ) {
          continue;
        }
        if ( edges[i].type != SANTA ) {
          continue;
        }
        if ( ! uf.same(edges[i].from, edges[i].to) ) {
          uf.merge(edges[i].from, edges[i].to);
          used[i] = true;
          res.push_back(i);
          remains --;
        }
      }
      return res;
    }

    static Indexes generate_graph_2( const Int& m, const Edge edges[SIZE], UnionFind& uf, bool used[SIZE] ) {
      Indexes res;
      for ( int i = 0; i < m; ++ i ) {
        if ( used[i] ) {
          continue;
        }
        if ( edges[i].type != SANTA ) {
          continue;
        }
        if ( ! uf.same(edges[i].from, edges[i].to) ) {
          uf.merge(edges[i].from, edges[i].to);
          used[i] = true;
          res.push_back(i);
        }
      }
      return res;
    }

    static Indexes generate_graph_1( const Int& m, const Edge edges[SIZE], UnionFind& uf, bool used[SIZE] ) {
      Indexes res;
      for ( int i = 0; i < m; ++ i ) {
        if ( used[i] ) {
          continue;
        }
        if ( edges[i].type != ELF ) {
          continue;
        }
        if ( ! uf.same(edges[i].from, edges[i].to) ) {
          uf.merge(edges[i].from, edges[i].to);
          used[i] = true;
          res.push_back(i);
        }
      }
      return res;
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
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      if ( ! ( std::cin >> in.N >> in.M ) ) {
        return false;
      }
      for ( int i = 0; i < in.M; ++ i ) {
        input_edge(in.edges[i]);
      }
      return true;
    }

    void output( const OutputStorage& out ) const {
      if ( out.result ) {
        std::cout << out.indexes.size() << std::endl;
        if ( ! out.indexes.empty() ) {
          for ( Indexes::const_iterator it_i = out.indexes.begin(); it_i != out.indexes.end(); ++ it_i ) {
            std::cout << ( *it_i + 1 ) << " ";
          }
          std::cout << std::endl;
        }
      } else {
        std::cout << -1 << std::endl;
      }
    }
    
  private:
    Solver solver;
    Storages* storages;

    bool input_edge( Edge& edge ) {
      Int from;
      Int to;
      string type;
      std::cin >> from >> to >> type;
      edge.from = from - 1;
      edge.to = to - 1;
      if ( type == "S" ) {
        edge.type = ELF;
      } else {
        edge.type = SANTA;
      }
      return true;
    }

  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif


