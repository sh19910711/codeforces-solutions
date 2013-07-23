
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
#include <deque>
#include <list>
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

// @snippet<sh19910711/contest:io/config.cpp>
namespace io {
  const std::string OUTPUT_VECTOR_DELIMITER = ",";
}

// @snippet<sh19910711/contest:io/pair.cpp>
namespace io {
  template <class A, class B> std::ostream& operator<<( std::ostream& os, const std::pair<A,B>& p ) {
    return os << "(" << p.first << "," << p.second << ")";
  }
  template <class A, class B> std::istream& operator>>( std::istream& is, std::pair<A,B>& p ) {
    return is >> p.first >> p.second;
  }
}

// @snippet<sh19910711/contest:io/vector.cpp>
namespace io {
  template <typename T> std::ostream& operator <<( std::ostream& os, const std::vector<T>& v ) {
    typedef typename std::vector<T>::const_iterator Iterator;
    for ( Iterator it_i = v.begin(); it_i != v.end(); ++ it_i ) {
      os << *it_i;
      if ( it_i + 1 != v.end() )
        os << OUTPUT_VECTOR_DELIMITER;
    }
    return os;
  }
  template <typename T> std::istream& operator >>( std::istream& is, std::vector<T>& v ) {
    int n = v.size();
    for ( int i = 0; i < n; ++ i ) {
      is >> v[i];
    }
    return is;
  }
}

namespace io {
  template <typename T> std::ostream& operator <<( std::ostream& os, const std::deque<T>& v ) {
    typedef typename std::deque<T>::const_iterator Iterator;
    for ( Iterator it_i = v.begin(); it_i != v.end(); ++ it_i ) {
      os << *it_i;
      if ( it_i + 1 != v.end() )
        os << OUTPUT_VECTOR_DELIMITER;
    }
    return os;
  }
  template <typename T> std::istream& operator >>( std::istream& is, std::deque<T>& v ) {
    int n = v.size();
    for ( int i = 0; i < n; ++ i ) {
      is >> v[i];
    }
    return is;
  }
}

namespace io {
  template <typename T> std::ostream& operator <<( std::ostream& os, const std::list<T>& v ) {
    typedef typename std::list<T>::const_iterator Iterator;
    for ( Iterator it_i = v.begin(); it_i != v.end(); ++ it_i ) {
      os << *it_i;
      os << OUTPUT_VECTOR_DELIMITER << " ";
    }
    return os;
  }
  template <typename T> std::istream& operator >>( std::istream& is, std::list<T>& v ) {
    int n = v.size();
    for ( int i = 0; i < n; ++ i ) {
      is >> v[i];
    }
    return is;
  }
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
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  using namespace io;

  typedef std::list<II> VII;
  typedef std::set<II> SII;
  
  // typedef std::pair<II, VII> State;
  // typedef std::pair<int, State> Node;
  // typedef std::queue<Node> Queue;
  typedef std::set<VII> Visited;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE        = 15;
  const int NONE        = std::numeric_limits<int>::max();
  const char CHAR_APPLE = '@';
  const char CHAR_EMPTY = '.';
  const char CHAR_WALL  = '#';
  const VII INVALID_SNAKE(1, II(-1, -1));

  const int dr[4] = {1, -1, 0, 0};
  const int dc[4] = {0, 0, 1, -1};
  
  // storages
  int H, W;
  string S[SIZE];
  
  VII start_snake;
  int gr, gc;

  std::queue <int> Q_steps;
  std::queue <int> Q_r;
  std::queue <int> Q_c;
  std::queue <VII> Q_snake;
  Visited visited;

  int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      result = get_minimum_steps();
    }
    
    void normalize() {
      int snake_len = 0;
      II snake_segments[SIZE];
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          char c = S[i][j];
          if ( is_digit(c) ) {
            int ind = c - '1';
            snake_segments[ind] = II(i, j);
            snake_len ++;
            S[i][j] = CHAR_EMPTY;
          }
        }
      }

      start_snake.clear();
      for ( int i = 0; i + 1 < snake_len; ++ i ) {
        start_snake.push_back(snake_segments[i]);
      }

      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( S[i][j] == CHAR_APPLE ) {
            gr = i;
            gc = j;
            S[i][j] = CHAR_EMPTY;
          }
        }
      }
    }
    
    bool is_digit( char c ) {
      return '0' <= c && c <= '9';
    }
    
    int get_minimum_steps() {
      int res = NONE;

      Q_steps = std::queue <int>();
      Q_r = std::queue <int>();
      Q_c = std::queue <int>();
      Q_snake = std::queue <VII>();
      visited.clear();

      const II& start_snake_head = *start_snake.begin();
      Q_steps.push(0);
      Q_r.push(start_snake_head.first);
      Q_c.push(start_snake_head.second);
      Q_snake.push(start_snake);
      visited.insert(start_snake);

      while ( ! Q_steps.empty() ) {
        int steps = Q_steps.front();
        Q_steps.pop();
        int r = Q_r.front();
        Q_r.pop();
        int c = Q_c.front();
        Q_c.pop();
        VII snake = Q_snake.front();
        Q_snake.pop();

        if ( r == gr && c == gc )
          return steps;

        SII segments(snake.begin(), snake.end());

        for ( int k = 0; k < 4; ++ k ) {
          int nr = r + dr[k];
          int nc = c + dc[k];
          II next_head(nr, nc);
          if ( is_invalid_pos(nr, nc) )
            continue;
          if ( segments.count(next_head) )
            continue;

          VII next_snake = snake;
          next_snake.push_front(next_head);
          next_snake.pop_back();
          int next_steps = steps + 1;

          if ( visited.count(next_snake) )
            continue;
          visited.insert(next_snake);

          Q_steps.push(next_steps);
          Q_r.push(nr);
          Q_c.push(nc);
          Q_snake.push(next_snake);
        }
      }

      return res;
    }

    void get_next_snake( VII& current, const int& dir ) {
      int& sr = (*current.begin()).first;
      int& sc = (*current.begin()).second;

    }

    bool is_invalid_pos( const int& r, const int& c ) {
      if ( r < 0 || r >= H || c < 0 || c >= W )
        return true;
      if ( S[r][c] == CHAR_WALL )
        return true;
      return false;
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
      if ( ! ( cin >> H >> W ) )
        return false;
      for ( int i = 0; i < H; ++ i ) {
        cin >> S[i];
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


