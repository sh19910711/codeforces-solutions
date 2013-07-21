
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
#include <ctime>

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
  typedef std::set<int> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int NONE = -1;
  const int LIMIT = 200 + 1;
  const string YES = "YES";
  const string NO = "NO";

  // storages
  int n, m;
  int h;
  int t;
  int A[SIZE];
  int B[SIZE];

  VI G[SIZE];
  int u, v;
  int head_vertices[LIMIT];
  int head_vertices_num;
  int tail_vertices[LIMIT];
  int tail_vertices_num;

  int head_tmp[LIMIT];
  int head_tmp_num;
  int tail_tmp[LIMIT];
  int tail_tmp_num;
  int commons_tmp[LIMIT];
  int commons_tmp_num;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();

      for ( int i = 0; i < n; ++ i ) {
        if ( G[i].size() < h )
          continue;
        for ( int j = 0; j < (int)G[i].size(); ++ j ) {
          int a = i;
          int b = G[i][j];
          if ( check(a, b) ) {
            u = a;
            v = b;
            return;
          }
        }
      }
    }

    void init_head_tail() {
      head_vertices_num = 0;
      tail_vertices_num = 0;
      head_tmp_num = 0;
      tail_tmp_num = 0;
      commons_tmp_num = 0;
    }

    bool generate_head_tmp( int u, int v ) {
      int connected_vertices_num = G[u].size();
      for ( int i = 0; i < connected_vertices_num && head_tmp_num < LIMIT; ++ i ) {
        if ( G[u][i] == v )
          continue;
        head_tmp[head_tmp_num ++] = G[u][i];
      }
      if ( head_tmp_num < h )
        return false;
      return true;
    }

    bool generate_tail_tmp( int u, int v ) {
      int connected_vertices_num = G[v].size();
      for ( int i = 0; i < connected_vertices_num && tail_tmp_num < LIMIT; ++ i ) {
        if ( G[v][i] == u )
          continue;
        tail_tmp[tail_tmp_num ++] = G[v][i];
      }
      if ( tail_tmp_num < t )
        return false;
      return true;
    }

    bool check( int u, int v ) {
      init_head_tail();

      if ( ! generate_head_tmp(u, v) )
        return false;
      if ( ! generate_tail_tmp(u, v) )
        return false;

      if ( head_tmp_num < h )
        return false;
      if ( tail_tmp_num < t )
        return false;

      int commons_p = 0;
      int commons_tmp_num = std::set_intersection(head_tmp, head_tmp + head_tmp_num,
          tail_tmp, tail_tmp + tail_tmp_num, commons_tmp) - commons_tmp;

      if ( head_tmp_num + tail_tmp_num < h + t + commons_tmp_num )
        return false;

      Set commons_set(commons_tmp, commons_tmp + commons_tmp_num);

      for ( int i = 0; i < head_tmp_num && head_vertices_num < h; ++ i ) {
        if ( commons_set.count(head_tmp[i]) )
          continue;
        head_vertices[head_vertices_num ++] = head_tmp[i];
      }
      for ( int i = 0; i < tail_tmp_num && tail_vertices_num < t; ++ i ) {
        if ( commons_set.count(tail_tmp[i]) )
          continue;
        tail_vertices[tail_vertices_num ++] = tail_tmp[i];
      }

      while ( head_vertices_num < h ) {
        if ( commons_p >= commons_tmp_num )
          return false;
        int vertex = commons_tmp[commons_p];
        head_vertices[head_vertices_num ++] = vertex;
        commons_p ++;
      }
      while ( tail_vertices_num < t ) {
        if ( commons_p >= commons_tmp_num )
          return false;
        int vertex = commons_tmp[commons_p];
        tail_vertices[tail_vertices_num ++] = vertex;
        commons_p ++;
      }

      return true;
    }

    void normalize() {
      for ( int i = 0; i < m; ++ i ) {
        A[i] --;
        B[i] --;
        int a = A[i];
        int b = B[i];
        G[a].push_back(b);
        G[b].push_back(a);
      }
      for ( int i = 0; i < n; ++ i )
        sort(G[i].begin(), G[i].end());
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
      for ( int i = 0; i < n; ++ i )
        G[i].clear();

      u = NONE;
      v = NONE;
    }

    bool input() {
      if ( ! ( scanf("%d%d", &n, &m) != EOF ) )
        return false;
      scanf("%d%d", &h, &t);
      for ( int i = 0; i < m; ++ i )
        scanf("%d%d", A + i, B + i);
      return true;
    }

    void output() {
      if ( u == NONE ) {
        puts(NO.c_str());
      } else {
        puts(YES.c_str());
        printf("%d %d\n", u + 1, v + 1);

        for ( int i = 0; i < head_vertices_num; ++ i )
          printf("%d ", head_vertices[i] + 1);
        puts("");

        for ( int i = 0; i < tail_vertices_num; ++ i )
          printf("%d ", tail_vertices[i] + 1);
        puts("");
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

