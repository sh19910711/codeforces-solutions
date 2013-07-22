
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
  typedef set<int, std::greater<int> > Set;
  typedef vector<II> VII;

  typedef II Node; // (steps, weight, delay)
  typedef std::queue<Node> Queue;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int NONE = std::numeric_limits<int>::max();

  // storages
  int n;
  int m;
  int A[SIZE];
  int B[SIZE];
  int C[SIZE];
  int K[SIZE];
  Set T[SIZE];

  VII G[SIZE]; 
  int min_cost[SIZE]; 

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      generate_graph();
      result = get_minimum_steps();
    }

    void generate_graph() {
      for ( int i = 0; i < m; ++ i ) {
        int a = A[i];
        int b = B[i];
        int c = C[i];
        G[a].push_back(II(c, b));
        G[b].push_back(II(c, a));
      }
      for ( int i = 0; i < n; ++ i ) {
        sort(G[i].begin(), G[i].end());
      }
    }

    int get_minimum_steps() {
      int res = NONE;

      Queue Q;
      Q.push(Node(0, 0));
      fill(min_cost, min_cost + SIZE, NONE);
      min_cost[0] = 0;

      while ( ! Q.empty() ) {
        Node node = Q.front();
        Q.pop();

        int planet = node.first;
        int steps = node.second;

        while ( check_need_wait(planet, steps) ) {
          steps ++;
        }

        int connected_planets = G[planet].size();
        for ( int i = 0; i < connected_planets; ++ i ) {
          int next_planet = G[planet][i].second;
          int next_steps = steps + G[planet][i].first;
          if ( next_steps >= min_cost[next_planet] )
            continue;
          min_cost[next_planet] = next_steps;
          Q.push(Node(next_planet, next_steps));
        }
      }

      return min_cost[n - 1];
    }

    bool check_need_wait( int planet, int steps ) {
      return T[planet].find(steps) != T[planet].end();
    }

    void normalize() {
      for ( int i = 0; i < m; ++ i ) {
        A[i] --;
        B[i] --;
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
      for ( int i = 0; i < SIZE; ++ i )
        G[i].clear();
    }

    bool input() {
      if ( ! ( cin >> n >> m ) )
        return false;
      for ( int i = 0; i < m; ++ i ) {
        cin >> A[i] >> B[i] >> C[i];
      }
      for ( int i = 0; i < n; ++ i ) {
        cin >> K[i];
        for ( int j = 0; j < K[i]; ++ j ) {
          int t;
          cin >> t;
          T[i].insert(t);
        }
      }
      return true;
    }

    void output() {
      if ( result == NONE ) {
        cout << -1 << endl;
      } else {
        cout << result << endl;
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

