
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
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 2 * 100000 + 11;
  const int INF  = std::numeric_limits<int>::max();
  const int NONE = -1;

  const int DIR_NORMAL = 0;
  const int DIR_INV = 1;

  // storages
  int n;
  int A[SIZE];
  int B[SIZE];

  VII G[SIZE];
  int flips[SIZE];
  int dist[SIZE];
  int needs[SIZE];
  int inv_cnt;

  int min_flips;
  int min_flips_vertices[SIZE];
  int min_flips_vertices_num;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      generate_graph();
      calc_dist(0, 0);
      calc_invcnt(0);
      flip_to_root(0, 0);
      calc_needs();

      min_flips = find_min_flips();
    }

    int find_min_flips() {
      int res = *std::min_element(needs, needs + n);
      for ( int i = 0; i < n; ++ i ) {
        if ( res == needs[i] ) {
          min_flips_vertices[min_flips_vertices_num ++] = i;
        }
      }
      return res;
    }

    void calc_needs() {
      for ( int i = 0; i < n; ++ i ) {
        needs[i] = inv_cnt - 2 * flips[i] + dist[i];
      }
    }

    void generate_graph() {
      for ( int i = 0; i < n - 1; ++ i ) {
        int a = A[i];
        int b = B[i];
        G[a].push_back(II(b, DIR_NORMAL));
        G[b].push_back(II(a, DIR_INV));
      }
    }

    void normalize() {
      for ( int i = 0; i < n - 1; ++ i ) {
        A[i] --;
        B[i] --;
      }
    }

    void flip_to_root( int cur, int cur_flips, int from = NONE ) {
      int num_vertices = G[cur].size();
      flips[cur] = cur_flips;
      for ( int i = 0; i < num_vertices; ++ i ) {
        II entry = G[cur][i];
        int to = entry.first;
        if ( to == from ) {
          continue;
        }
        flip_to_root(to, cur_flips + ( entry.second == DIR_INV ? 1 : 0 ), cur);
      }
    }

    void calc_dist( int cur, int cur_dist, int from = NONE ) {
      int num_vertices = G[cur].size();
      dist[cur] = cur_dist;
      for ( int i = 0; i < num_vertices; ++ i ) {
        II entry = G[cur][i];
        int to = entry.first;
        if ( to == from ) {
          continue;
        }
        calc_dist(to, cur_dist + 1, cur);
      }
    }

    void calc_invcnt( int cur, int from = NONE ) {
      int num_vertices = G[cur].size();
      for ( int i = 0; i < num_vertices; ++ i ) {
        II entry = G[cur][i];
        int to = entry.first;
        if ( to == from ) {
          continue;
        }
        if ( entry.second == DIR_INV ) {
          inv_cnt ++;
        }
        calc_invcnt(to, cur);
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
      min_flips = INF;
      min_flips_vertices_num = 0;
      for ( int i = 0; i < SIZE; ++ i ) {
        G[i].clear();
      }
      inv_cnt = 0;
    }

    bool input() {
      if ( ! ( cin >> n ) )
        return false;
      for ( int i = 0; i < n - 1; ++ i ) {
        cin >> A[i] >> B[i];
      }
      return true;
    }

    void output() {
      cout << min_flips << endl;
      for ( int i = 0; i < min_flips_vertices_num; ++ i ) {
        cout << min_flips_vertices[i] + 1 << " ";
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

