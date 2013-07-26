
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

// @snippet<sh19910711/contest:setlib/disjoints_set.cpp>
namespace setlib {
  // @desc 素集合データ構造
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

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  using setlib::DisjointSets;
  typedef std::map<II, int> VerticesToEdgeID;
  typedef std::map<int, int> Map;
  typedef std::set<int> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int QUERIES = 3 * 100000 + 11;
  const int EDGE_COLOR_BLACK = 0;
  const int EDGE_COLOR_WHITE = 1;
  const int VERTEX_NONE = -1;
  const int INF = std::numeric_limits<int>::max();
  const int DIST_NONE = -3;
  
  // storages
  int n;
  int A[SIZE];
  int B[SIZE];
  int m;
  int T[QUERIES];
  int X[QUERIES];
  int Y[QUERIES];
  
  DisjointSets uf;
  VerticesToEdgeID v2e;
  Map edge_group;
  int edge_dist[SIZE];
  Set white_edges[SIZE];
  VI G[SIZE];
  int root;
  int degree[SIZE];
  int dist[SIZE];
  
  int query_results[QUERIES];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      calc_degree();
      root = find_root();
      calc_dist(root, 0);
      calc_edge_dist();
      find_group();
      find_edge_group();


      proc_queries();
    }

    int get_edge_id_from_vertices( int a, int b ) {
      return v2e[II(std::min(a, b), std::max(a, b))];
    }

    void proc_queries() {
      for ( int i = 0; i < m; ++ i ) {
        if ( T[i] == 3 ) {
          query_results[i] = query_minimum_dist(std::min(X[i], Y[i]), std::max(X[i], Y[i]));
        } else {
          query_set_color(X[i], T[i] == 1 ? EDGE_COLOR_BLACK : EDGE_COLOR_WHITE);
        }
      }
    }

    void find_group() {
      int num_vertices = G[root].size();
      for ( int i = 0; i < num_vertices; ++ i ) {
        int to = G[root][i];
        find_group(to, root);
      }
    }

    void find_group( int cur, int from = VERTEX_NONE ) {
      int num_vertices = G[cur].size();
      for ( int i = 0; i < num_vertices; ++ i ) {
        int to = G[cur][i];
        if ( to == from ) {
          continue;
        }

        uf.merge(cur, to);
        find_group(to, cur);
      }
    }

    void find_edge_group() {
      for ( int i = 0; i < n - 1; ++ i ) {
        int vertex = A[i];
        if ( vertex == root )
          vertex = B[i];
        edge_group[i] = uf.root(vertex);
      }
    }
    
    int query_minimum_dist( int x, int y ) {
      if ( x == y ) {
        return 0;
      }
      if ( uf.same(x, y) ) {
        int dx = dist[x];
        int dy = dist[y];
        int g = uf.root(x);
        int ld = std::min(dx, dy);
        int ud = std::max(dx, dy);
        if ( white_edges[g].size() ) {
          Set::iterator it_lb = white_edges[g].lower_bound(ld);
          if ( it_lb != white_edges[g].end() ) {
            int wd = *it_lb;
            if ( ld <= wd && wd < ud ) {
              return DIST_NONE;
            }
          }
        }
        return std::max(dx, dy) - std::min(dx, dy);
      } else {
        int dx = dist[x];
        int dy = dist[y];
        int gx = uf.root(x);
        int gy = uf.root(y);
        int wx_dist = white_edges[gx].size() ? *white_edges[gx].rbegin() : INF;
        int wy_dist = white_edges[gy].size() ? *white_edges[gy].rbegin() : INF;
        if ( dx > wx_dist || dy > wy_dist ) {
          return DIST_NONE;
        }
        return dx + dy;
      }
      return DIST_NONE;
    }
    
    void query_set_color( int edge_id, int color ) {
      int gid = edge_group[edge_id];
      int dist = edge_dist[edge_id];
      if ( color == EDGE_COLOR_WHITE ) {
        white_edges[gid].insert(dist);
      } else if ( color == EDGE_COLOR_BLACK ) {
        white_edges[gid].erase(dist);
      }
    }

    void calc_edge_dist() {
      for ( int i = 0; i < n - 1; ++ i ) {
        int a = A[i];
        int b = B[i];
        edge_dist[i] = std::min(dist[a], dist[b]);
      }
    }
    
    void calc_dist( int cur, int current_dist, int from = VERTEX_NONE ) {
      dist[cur] = current_dist;
      int num_vertices = G[cur].size();
      for ( int i = 0; i < num_vertices; ++ i ) {
        int to = G[cur][i];
        if ( from == to ) {
          continue;
        }
        calc_dist(to, current_dist + 1, cur);
      }
    }
    
    int find_root() {
      int res = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( degree[i] > degree[res] ) {
          res = i;
        }
      }
      return res;
    }
    
    void calc_degree() {
      for ( int i = 0; i < n - 1; ++ i ) {
        degree[A[i]] ++;
        degree[B[i]] ++;
      }
    }
    
    void normalize() {
      for ( int i = 0; i < n - 1; ++ i ) {
        A[i] --;
        B[i] --;
      }
      for ( int i = 0; i < m; ++ i ) {
        X[i] --;
        Y[i] --;
      }
      for ( int i = 0; i < n - 1; ++ i ) {
        if ( A[i] > B[i] ) {
          std::swap(A[i], B[i]);
        }
      }
      for ( int i = 0; i < n - 1; ++ i ) {
        int a = A[i];
        int b = B[i];
        G[a].push_back(b);
        G[b].push_back(a);
      }
      for ( int i = 0; i < n - 1; ++ i ) {
        int a = A[i];
        int b = B[i];
        v2e[II(a, b)] = i;
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
      std::fill(degree, degree + SIZE, 0);
      std::fill(G, G + SIZE, VI());
      std::fill(white_edges, white_edges + SIZE, Set());
      uf.init(SIZE);
      v2e.clear();
      edge_group.clear();
    }
    
    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n - 1; ++ i ) {
        cin >> A[i] >> B[i];
      }
      cin >> m;
      for ( int i = 0; i < m; ++ i ) {
        input_query(i);
      }
      return true;
    }
    
    void input_query( int k ) {
      cin >> T[k];
      if ( T[k] == 3 ) {
        cin >> X[k] >> Y[k];
      } else {
        cin >> X[k];
      }
    }
    
    void output() {
      for ( int i = 0; i < m; ++ i ) {
        if ( T[i] == 3 ) {
          if ( query_results[i] == DIST_NONE ) {
            cout << -1 << endl;
          } else {
            cout << query_results[i] << endl;
          }
        }
      }
      cout << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif


