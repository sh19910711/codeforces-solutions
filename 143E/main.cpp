
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
  typedef int Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 9;
  
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
  };
  
  struct OutputStorage {
    Int result;
    Int table[SIZE][SIZE];
    Int H;
    Int W;
  };
  
  struct DataStorage {
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

  const Int dr[4][5] = {
    {0, 0, 0, 1, 2},
    {0, 1, 1, 1, 2},
    {0, 1, 2, 2, 2},
    {0, 1, 1, 1, 2},
  };

  const Int dc[4][5] = {
    {0, 1, 2, 1, 1},
    {2, 0, 1, 2, 2},
    {1, 1, 0, 1, 2},
    {0, 0, 1 ,2, 0},
  };

  const int NONE = -1;

  class DFS {
  public:
    Int H;
    Int W;

    Int best;
    Int T_best[SIZE][SIZE];
    Int cur;
    Int T[SIZE][SIZE];

    void rec( const Int& r, const Int& c ) {
      if ( r >= H ) {
        if ( cur > best ) {
          best = cur;
          copy_to(T_best);
        }
        return;
      }
      if ( c >= W ) {
        return rec(r + 1, 0);
      }

      // TODO
      if ( 5 * cur + ( H - r + 1 ) * ( W - c + 1 ) <= best * 5 - 10 ) {
        return;
      }

      cur ++;
      for ( int k = 0; k < 4; ++ k ) {
        if ( can_put_t(k, r, c) ) {
          put_t(k, r, c);
          rec(r, c + 1);
          remove_t(k, r, c);
        }
      }
      cur --;
      rec(r, c + 1);
    }

    bool can_put_t( const Int& t, const Int& sr, const Int& sc ) {
      for ( int i = 0; i < 5; ++ i ) {
        const Int nr = sr + dr[t][i];
        const Int nc = sc + dc[t][i];
        if ( nr < 0 || nr >= H || nc < 0 || nc >= W ) {
          return false;
        }
        if ( T[nr][nc] != NONE ) {
          return false;
        }
      }
      return true;
    }

    void put_t( const Int& t, const Int& sr, const Int& sc ) {
      for ( int i = 0; i < 5; ++ i ) {
        const Int nr = sr + dr[t][i];
        const Int nc = sc + dc[t][i];
        T[nr][nc] = cur - 1;
      }
    }

    void remove_t( const Int& t, const Int& sr, const Int& sc ) {
      for ( int i = 0; i < 5; ++ i ) {
        Int nr = sr + dr[t][i];
        Int nc = sc + dc[t][i];
        T[nr][nc] = NONE;
      }
    }

    void copy_to( Int dest[SIZE][SIZE] ) {
      std::memcpy(dest, T, sizeof T);
      // std::copy((Int*)T, (Int*)T + SIZE * SIZE, (Int*)dest);
    }

    void copy_best_to( Int dest[SIZE][SIZE] ) {
      std::memcpy(dest, T_best, sizeof T_best);
      // std::copy((Int*)T_best, (Int*)T_best + SIZE * SIZE, (Int*)dest);
    }

    void init() {
      cur = 0;
      best = 0;
      init_table();
    }

    void init_table() {
      std::fill((Int*)T, (Int*)T + SIZE * SIZE, NONE);
      std::fill((Int*)T_best, (Int*)T_best + SIZE * SIZE, NONE);
    }

    void run() {
      init();
      rec(0, 0);
    }
  };

  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      DFS dfs;
      dfs.H = in.H;
      dfs.W = in.W;
      dfs.run();

      out.result = dfs.best;
      dfs.copy_best_to(out.table);
      out.H = in.H;
      out.W = in.W;
      return out;
    }
    
  protected:
    
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
      return std::cin >> in.H >> in.W;
    }

    void output( const OutputStorage& out ) const {
      std::cout << out.result << std::endl;
      for ( int i = 0; i < out.H; ++ i ) {
        for ( int j = 0; j < out.W; ++ j ) {
          if ( out.table[i][j] == NONE ) {
            std::cout << '.';
          } else {
            std::cout << (char)('A' + out.table[i][j]);
          }
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
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

