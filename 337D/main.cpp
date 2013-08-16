
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
    SolutionInterface() {}
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() const {};
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      this->pre_calc();
      while ( this->action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef ValueType Type;
    VectorClass() { data.resize(SIZE); }
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }

    void fill( const Type& value ) { std::fill(data.begin(), data.end(), value); }

  private:
    std::vector<Type> data;
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
  const Int SIZE = 100000 + 11;
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storage types
  typedef storage::Vector<Int, SIZE>::Type Vertices;
  typedef storage::Vector<Int, SIZE>::Type IsSettlements;
  typedef storage::Vector<Int, SIZE>::Type Dist;
  typedef std::vector<int> Edges;
  typedef storage::Vector<Edges, SIZE>::Type Graph;
    
  // storages
  Int N;
  Int M;
  Int D;
  Vertices P;
  Vertices A;
  Vertices B;

  Graph G;
  IsSettlements S;
  Dist dist;

  Int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      A = normalize(A, N - 1);
      B = normalize(B, N - 1);
      G = generate_graph(A, B, N - 1);
      P = normalize(P, M);
      S = check_settlements(P, M);
      calc_dist(0, 0);
      result = find_good_vertices(N, S, M, A, B, N - 1);
    }

    const Graph generate_graph( const Vertices& A, const Vertices& B, const Int& num_edges ) {
      Graph res;
      for ( int i = 0; i < num_edges; ++ i ) {
        int a = A[i], b = B[i];
        res[a].push_back(b);
        res[b].push_back(a);
      }
      return res;
    }

    void calc_dist( const Int& cur, const Int& cur_dist, const Int& from = -1 ) {
      int num_vertices = G[cur].size();
      dist[cur] = cur_dist;
      for ( int i = 0; i < num_vertices; ++ i ) {
        int to = G[cur][i];
        if ( to == from )
          continue;
        calc_dist(to, cur_dist + 1, cur);
      }
    }

    const IsSettlements check_settlements( const Vertices& P, const Int& M ) {
      IsSettlements res;
      res.fill(false);
      for ( int i = 0; i < M; ++ i ) {
        res[P[i]] = 1;
      }
      return res;
    }

    const Vertices normalize( const Vertices& vertices, const Int& num_vertices ) {
      Vertices res;
      for ( int i = 0; i < num_vertices; ++ i ) {
        res[i] = vertices[i] - 1;
      }
      return res;
    }

    const Int find_good_vertices( const Int& num_vertices, const IsSettlements& S, const Int& M, const Vertices& A, const Vertices& B, const Int& num_edges ) {
      Int res = N - M;
      return res;
    }

  protected:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input() )
        return false;
      solver.solve();
      this->output();
      return true;
    }

    bool input() {
      if ( ! ( std::cin >> N >> M >> D ) )
        return false;
      for ( int i = 0; i < M; ++ i ) {
        std::cin >> P[i];
      }
      for ( int i = 0; i < N - 1; ++ i ) {
        std::cin >> A[i] >> B[i];
      }
      return true;
    }

    void output() {
      std::cout << result << std::endl;
    }
    
    Solver solver;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution().run();
}
#endif


