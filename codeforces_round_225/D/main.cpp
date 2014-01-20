
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
  const int SIZE = 100000 + 11;
  const int NONE = -1;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int M;
    Int X[SIZE];
    Int Y[SIZE];
  };
  
  struct OutputStorage {
    Int result;
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
  typedef std::pair <Int, Int> Pos;
  typedef std::set <Pos> SetPos;
  typedef std::map <Pos, Int> MapPos;

  const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  class Checker {
  public:
    Int N;
    Int M;
    Int X[SIZE];
    Int Y[SIZE];
    Pos P_x[SIZE]; // (x, y) sorted
    Pos P_y[SIZE]; // (y, x)
    bool used[SIZE];
    SetPos S;
    MapPos I;

    void copy_to_x( const Int source[SIZE] ) {
      std::copy(source, source + SIZE, X);
    }

    void copy_to_y( const Int source[SIZE] ) {
      std::copy(source, source + SIZE, Y);
    }

    void init_pos() {
      S.clear();
      I.clear();
      for ( int i = 0; i < M; ++ i ) {
        Pos pos(X[i], Y[i]);
        S.insert(pos);
        I[pos] = i;
        P_x[i] = pos;
        P_y[i] = Pos(Y[i], X[i]);
      }
      std::sort(P_x, P_x + M);
      std::sort(P_y, P_y + M);
    }

    bool rec_top( const Int& sx, const Int& sy ) {
      bool& u = used[I[Pos(sx, sy)]];
      if ( u ) {
        return false;
      }
      used[I[Pos(sx, sy)]] = true;
      if ( sy <= 0 ) {
        return true;
      }
      for ( int k = 0; k < 8; ++ k ) {
        Int nx = sx + dx[k];
        Int ny = sy + dy[k];
        if ( ! S.count(Pos(nx, ny)) ) {
          continue;
        }
        if ( rec_top(nx, ny) ) {
          return false;
        }
      }
      return false;
    }

    bool rec_right( const Int& sx, const Int& sy ) {
      bool& u = used[I[Pos(sx, sy)]];
      if ( u ) {
        return false;
      }
      used[I[Pos(sx, sy)]] = true;
      if ( sx >= N ) {
        return true;
      }
      for ( int k = 0; k < 8; ++ k ) {
        Int nx = sx + dx[k];
        Int ny = sy + dy[k];
        if ( ! S.count(Pos(nx, ny)) ) {
          continue;
        }
        if ( rec_top(nx, ny) ) {
          return false;
        }
      }
      return false;
    }

    bool check_left_to_top() {
      std::fill(used, used + SIZE, false);
      for ( int i = 0; i < M; ++ i ) {
        // x == 0
        if ( P_x[i].first == 0 ) {
          if ( ! used[i] && rec_top(P_x[i].first, P_x[i].second) ) {
            return true;
          }
        } else {
          break;
        }
      }
      return false;
    }

    bool run() {
      init_pos();
      if ( check_left_to_top() ) {
        return true;
      }
      return false;
    }
  };

  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      out.result = find_minimum(in.N, in.M, in.X, in.Y);
      return out;
    }
    
  protected:
    static Int find_minimum( const Int& N, const Int& M, const Int X[SIZE], const Int Y[SIZE] ) {
      if ( N >= SIZE ) {
        return 2 * N - 2;
      }
      Checker checker;
      checker.N = N;
      checker.M = M;
      checker.copy_to_x(X);
      checker.copy_to_y(Y);
      if ( checker.run() ) {
        return NONE;
      }
      return -2;
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
      if ( ! ( std::cin >> in.N >> in.M ) ) {
        return false;
      }
      for ( int i = 0; i < in.M; ++ i ) {
        std::cin >> in.X[i] >> in.Y[i];
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

