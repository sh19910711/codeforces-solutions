
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

// @snippet<sh19910711/contest:solution/define_classes.cpp>
namespace solution {
  class Solution;
  class Solver;
  struct InputStorage;
  struct OutputStorage;
  struct DataStorage;
  class Storages;
}

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    
  protected:
    SolutionInterface() {}
    virtual bool action() = 0;
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) const {}
    virtual void after_action( const int& test_no ) const {}
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}
    virtual int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 2000 + 11;
  const int NONE = -1;
  const char BLOCK = '#';

  const int DR[4] = {0, 0, 1, -1};
  const int DC[4] = {1, -1, 0, 0};
  const char DT[4] = {'>', '<', 'v', '^'};
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int H;
    Int W;
    String M[SIZE];
  };
  
  struct OutputStorage {
    Int result;
  };
  
  struct DataStorage {
    int visited[SIZE][SIZE];
  };
  
  struct Storages {
    InputStorage  in;
    OutputStorage out;
    DataStorage   data;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      out.result = find_maximum(in.H, in.W, in.M, data);
      return out;
    }
    
  protected:
    static Int find_maximum( const Int& H, const Int& W, const String M[SIZE], DataStorage& data ) {
      if ( has_cycle(H, W, M, data) ) {
        return NONE;
      }
      for ( int r = 0; r < H; ++ r ) {
        for ( int c = 0; c < W; ++ c ) {
          if ( M[r][c] == BLOCK ) {
            continue;
          }
          int d;
          for ( d = 0; d < 4; ++ d ) {
            if ( M[r][c] == DT[d] ) {
              break;
            }
          }
          int nr = r + DR[d];
          int nc = c + DC[d];
          if ( M[nr][nc] == BLOCK ) {
          }
        }
      }
      return -2;
    }

    static bool has_cycle( const Int& H, const Int& W, const String M[SIZE], DataStorage& data ) {
      std::fill((int*)data.visited, (int*)data.visited + SIZE * SIZE, NONE);
      for ( int r = 0; r < H; ++ r ) {
        for ( int c = 0; c < W; ++ c ) {
          if ( data.visited[r][c] != NONE ) {
            continue;
          }
          if ( M[r][c] == BLOCK ) {
            continue;
          }
          if ( has_cycle(r, c, r, c, H, W, M, data) ) {
            return true;
          }
        }
      }
      return false;
    }

    static bool has_cycle( int sr, int sc, int r, int c, const Int& H, const Int& W, const String M[SIZE], DataStorage& data ) {
      if ( M[r][c] == BLOCK ) {
        return false;
      }
      if ( data.visited[r][c] == sr * H + sc ) {
        return true;
      }
      data.visited[r][c] = sr * H + sc;

      int k = 0;
      for ( k = 0; k < 4; ++ k ) {
        if ( DT[k] == M[r][c] ) {
          break;
        }
      }
      int nr = r + DR[k];
      int nc = c + DC[k];
      if ( has_cycle(sr, sc, nr, nc, H, W, M, data) ) {
        return true;
      }

      return false;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {}
    Solution(Storages* p): storages(p) {}
    
  protected:
    virtual bool action() {
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      if ( ! ( std::cin >> in.H >> in.W ) ) {
        return false;
      }
      for ( int i = 0; i < in.H; ++ i ) {
        std::cin >> in.M[i];
      }
      return true;
    }

    void output( const OutputStorage& out ) const {
      std::cout << out.result << std::endl;
    }
    
  private:
    Solver solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif

