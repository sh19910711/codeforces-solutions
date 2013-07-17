
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
  typedef pair <LL, LL> Node;
  typedef priority_queue <Node, vector<Node>, greater<Node> > Queue;
  typedef set <LL> Set;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  
  // storages
  LL n;
  LL result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      LL prev = 0;
      LL cnt = 0;
      for ( n = 0; n <= 1000; ++ n ) {
        result = get_minimum_operations();
        if ( prev != result ) {
          cout << cnt << ",";
        } else {
          cnt ++;
        }
        prev = result;
      }
    }

    LL get_minimum_operations() {
      Queue Q;
      Q.push(Node(0, n));
      Set V;
      V.insert(n);

      while ( ! Q.empty() ) {
        Node node = Q.top();
        Q.pop();

        LL steps = node.first;
        LL next_steps = steps + 1;
        LL x = node.second;
        LL sx = x;

        if ( x == 0 )
          return steps;

        while ( x > 9 ) {
          LL next_x = sx - x % 10;
          if ( V.count(next_x) ) {
            x /= 10;
            continue;
          }
          V.insert(next_x);
          Q.push(Node(next_steps, next_x));
        }
        {
          LL next_x = sx - x % 10;
          if ( V.count(next_x) ) {
            x /= 10;
            continue;
          }
          V.insert(next_x);
          Q.push(Node(next_steps, next_x));
        }
      }

      return -1;
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

    bool input() {
      return cin >> n;
    }

    void output() {
      cout << result << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

