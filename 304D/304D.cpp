
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

// @snippet<sh19910711/contest:io/pair.cpp>
namespace io {
  template <class A, class B> std::ostream& operator<<( std::ostream& os, const std::pair<A,B>& p ) {
    return os << p.first << " " << p.second;
  }
  template <class A, class B> std::istream& operator>>( std::istream& is, std::pair<A,B>& p ) {
    return is >> p.first >> p.second;
  }
}

// @snippet<sh19910711/contest:math/gcd.cpp>
namespace math {
  template <class T> T gcd( T a, T b ) {
    T i, j;
    for ( i = 0; ! ( a & 1 ); ++ i ) a >>= 1;
    for ( j = 0; ! ( b & 1 ); ++ j ) b >>= 1;
    while ( b != a ) {
      b -= a;
      if ( b < 0 ) a += b, b = -b;
      while ( ! ( b & 1 ) ) b >>= 1;
    }
    return a << std::min( i, j );
  }
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  using namespace io;
  typedef double Double;
  typedef pair <II, II> Rect;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const LL INF = std::numeric_limits<LL>::max();
  
  // storages
  LL n, m;
  LL x, y;
  LL a, b;
  
  Rect result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      LL cd = math::gcd(a, b);
      a /= cd;
      b /= cd;
      
      Double scale = floor(get_maximum_scale(a, b, n, m));
      
      LL w = a * scale;
      LL h = b * scale;
      LL x1 = max(0LL, x - (LL)ceil((Double)w / 2));
      LL y1 = max(0LL, y - (LL)ceil((Double)h / 2));
      LL x2 = x1 + w;
      LL y2 = y1 + h;
      while ( x2 > n ) {
        x1 --;
        x2 --;
      }
      while ( y2 > m ) {
        y1 --;
        y2 --;
      }
      result = Rect(II(x1, y1), II(x2, y2));
      Double min_diff = abs((Double)( x1 + x2 ) / 2.0 - x) + abs((Double)( y1 + y2 ) / 2.0 - y);
      
      for ( int offset_x = -1000; offset_x < 1000; ++ offset_x ) {
        for ( int offset_y = -1000; offset_y < 1000; ++ offset_y ) {
          LL nx1 = x1 + offset_x;
          LL ny1 = y1 + offset_y;
          LL nx2 = x2 + offset_x;
          LL ny2 = y2 + offset_y;
          if ( nx1 < 0 || ny1 < 0 || nx2 < 0 || ny2 < 0 )
            continue;
          if ( nx2 > n || ny2 > m )
            continue;
          if ( ! ( nx1 <= x && x <= nx2 && ny1 <= y && y <= ny2 ) )
            continue;
          Double diff = abs((Double)( nx1 + nx2 ) / 2.0 - x) + abs((Double)( ny1 + ny2 ) / 2.0 - y);
          if ( diff > min_diff )
            continue;
          Rect rect(II(nx1, ny1), II(nx2, ny2));
          result = min(result, rect);
        }
      }
    }
    
    Double get_maximum_scale( Double a, Double b, Double n, Double m ) {
      Double lb = 0.0;
      Double ub = 1000000000.0 + 11.0;
      for ( int i = 0; i < 100; ++ i ) {
        Double mid = ( lb + ub ) / 2.0;
        if ( a * mid <= n && b * mid <= m ) {
          lb = mid;
        } else {
          ub = mid;
        }
      }
      return lb;
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
      result = Rect(II(INF, INF), II(INF, INF));
    }
    
    bool input() {
      return cin >> n >> m >> x >> y >> a >> b;
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



