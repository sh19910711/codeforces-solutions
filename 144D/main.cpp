
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
  typedef std::pair <int, int> Node;
  typedef std::priority_queue<Node, std::vector<Node>, std::greater<Node> > Queue;
  typedef std::pair <int, int> Edge;
  typedef std::vector <Edge> Edges;

  typedef std::map <Edge, int> EdgeID;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int INF = std::numeric_limits<int>::max();

  // storages
  int n, m, s;
  int A[SIZE];
  int B[SIZE];
  int W[SIZE];
  int L;

  Queue Q;
  int min_dist[SIZE];
  Edges G[SIZE];
  EdgeID edge_id;

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      generate_graph();
      calc_minimum_dist();
      result = get_numbers();
    }

    void generate_graph() {
      for ( int i = 0; i < m; ++ i ) {
        int a = A[i], b = B[i];
        G[a].push_back(II(b, W[i]));
        G[b].push_back(II(a, W[i]));
      }
    }

    void calc_minimum_dist() {
      Q = Queue();
      std::fill(min_dist, min_dist + SIZE, INF);
      Q.push(Node(0, s));
      min_dist[s] = 0;

      while ( ! Q.empty() ) {
        Node node = Q.top();
        Q.pop();

        int dist = node.first;
        int cur = node.second;

        int num_vertices = G[cur].size();
        for ( int i = 0; i < num_vertices; ++ i ) {
          int to = G[cur][i].first;
          int next_dist = dist + G[cur][i].second;
          if ( next_dist >= min_dist[to] ) {
            continue;
          }
          min_dist[to] = next_dist;
          Q.push(Node(next_dist, to));
        }
      }
    }

    int get_numbers() {
      int res = 0;
      for ( int i = 0; i < n; ++ i ) {
        if ( min_dist[i] == L ) {
          res ++;
        }

        int num_vertices = G[i].size();
        for ( int j = 0; j < num_vertices; ++ j ) {
          int to = G[i][j].first;
          int len = G[i][j].second;
          if ( i < to ) {
            continue;
          }

          int low = std::min(min_dist[i], min_dist[to]);
          int high = std::max(min_dist[i], min_dist[to]);
          if ( L <= low ) {
            continue;
          }

          if ( L < high ) {
            res ++;
            continue;
          }

          if ( L == high ) {
            if ( low + len != high ) {
              res ++;
            }
            continue;
          }

          if ( low + high + len == 2 * L ) {
            res ++;
          } else if ( low + high + len > 2 * L ) {
            res += 2;
          }
        }
      }
      return res;
    }

    void normalize() {
      s --;
      for ( int i = 0; i < m; ++ i ) {
        A[i] --;
        B[i] --;
      }
      for ( int i = 0; i < m; ++ i ) {
        if ( A[i] > B[i] ) {
          std::swap(A[i], B[i]);
        }
      }
      for ( int i = 0; i < m; ++ i ) {
        edge_id[Edge(A[i], B[i])] = i;
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
      std::fill(G, G + SIZE, Edges());
      edge_id.clear();
    }

    bool input() {
      if ( ! ( cin >> n >> m >> s ) )
        return false;
      for ( int i = 0; i < m; ++ i ) {
        cin >> A[i] >> B[i] >> W[i];
      }
      cin >> L;
      return true;
    }

    void output() {
      cout << result << endl;
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

