
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
  using namespace io;

  typedef std::vector<II> VII;
  
  typedef std::pair<int, VII> Node;
  typedef std::queue<Node> Queue;
  typedef std::map<VII, int> Map;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE        = 15 + 11;
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
  II apple_pos;

  Queue Q;
  Map MC;

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
      int len = get_snake_length();
      start_snake = VII(len);
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          char c = S[i][j];
          if ( is_digit(c) ) {
            int ind = c - '1';
            start_snake[ind] = II(i, j);
            S[i][j] = CHAR_EMPTY;
          }
        }
      }
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( S[i][j] == CHAR_APPLE ) {
            apple_pos = II(i, j);
            S[i][j] = CHAR_EMPTY;
          }
        }
      }
    }
    
    bool is_digit( char c ) {
      return '0' <= c && c <= '9';
    }
    
    int get_snake_length() {
      int res = 0;
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          if ( is_digit(S[i][j]) ) {
            res ++;
          }
        }
      }
      return res;
    }

    int get_min_cost( const VII& key ) {
      return MC.count(key) ? MC[key] : NONE;
    }
    
    int get_minimum_steps() {
      int res = NONE;
      Q = Queue();
      MC.clear();

      Node start_node(0, start_snake);
      Q.push(start_node);
      MC[start_snake] = 0;

      while ( ! Q.empty() ) {
        Node node = Q.front();
        Q.pop();

        int steps = node.first;
        VII snake = node.second;

        if ( snake[0] == apple_pos )
          return steps;

        for ( int k = 0; k < 4; ++ k ) {
          VII next_snake = get_next_snake(snake, k);
          int next_steps = steps + 1;

          if ( next_steps >= get_min_cost(next_snake) )
            continue;
          MC[next_snake] = next_steps;

          Q.push(Node(next_steps, next_snake));
        }
      }

      return res;
    }

    VII get_next_snake( VII current, const int& dir ) {
      VII res;

      int& sr = (*current.begin()).first;
      int& sc = (*current.begin()).second;
      res.push_back(II(sr + dr[dir], sc + dc[dir]));
      for ( VII::iterator it_i = current.begin(); it_i + 1 != current.end(); ++ it_i ) {
        res.push_back(*it_i);
      }

      for ( VII::iterator it_i = res.begin(); it_i != res.end(); ++ it_i ) {
        if ( is_invalid_pos(*it_i) )
          return INVALID_SNAKE;
      }

      for ( VII::iterator it_i = res.begin(); it_i != res.end(); ++ it_i ) {
        for ( VII::iterator it_j = it_i + 1; it_j != res.end(); ++ it_j ) {
          if ( *it_i == *it_j )
            return INVALID_SNAKE;
        }
      }

      return res;
    }

    bool is_invalid_pos( const II& pos ) {
      if ( pos.first < 0 || pos.first >= H || pos.second < 0 || pos.second >= W )
        return true;
      if ( S[pos.first][pos.second] == CHAR_WALL )
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


