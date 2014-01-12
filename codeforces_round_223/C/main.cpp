
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
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int m;
    Int Q[SIZE];
    Int X[SIZE];
    Int Y[SIZE];
    Int n;
    Int A[SIZE];
  };
  
  struct OutputStorage {
    Int n;
    Int seq[SIZE];
  };
  
  struct DataStorage {
    Int sub[SIZE];
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
      out.n = in.n;
      generate_sub(in, data);
      for_each_query(in, out, data);
      return out;
    }
    
  protected:
    static void for_each_query( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      Int cnt = 0;      // 生成済みの個数
      Int seq_cnt = 0;  // 次に格納する要素
      Int A_next = 0;
      Int next_index = in.A[A_next ++];
      for ( int i = 0; i < in.m; ++ i ) {
        const Int type = in.Q[i];
        if ( type == 1 ) {
          cnt += 1;
          const Int x = in.X[i];
          if ( cnt == next_index ) {
            out.seq[seq_cnt ++] = x;
            next_index = in.A[A_next ++];
          }
        } else {
          const Int l = in.X[i];
          const Int c = in.Y[i];
          cout << "2: generated = " << cnt << ", next = " << next_index << endl;
          // 範囲に含まれるかどうか
          if ( cnt < next_index && next_index <= cnt + l * c ) {
            Int offset = next_index - cnt;
            out.seq[seq_cnt ++] = data.sub[offset];
            next_index = in.A[A_next ++];
          }
          cnt += l * c;
        }
      }
    }

    static void generate_sub( const InputStorage& in, DataStorage& data ) {
      Int cnt = 0;
      for ( int i = 0; i < in.m; ++ i ) {
        const Int type = in.Q[i];
        if ( type == 1 ) {
          const Int x = in.X[i];
          data.sub[cnt ++] = x;
          if ( cnt >= SIZE ) {
            return;
          }
        } else {
          const Int l = in.X[i];
          const Int c = in.Y[i];
          for ( int i = 0; i < c; ++ i ) {
            for ( int j = 0; j < l; ++ j ) {
              data.sub[cnt ++] = data.sub[j];
              if ( cnt >= SIZE )
                return;
            }
          }
        }
      }
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
      if ( ! ( std::cin >> in.m ) )
        return false;
      for ( int i = 0; i < in.m; ++ i ) {
        std::cin >> in.Q[i];
        if ( in.Q[i] == 1 ) {
          std::cin >> in.X[i];
        } else {
          std::cin >> in.X[i] >> in.Y[i];
        }
      }
      std::cin >> in.n;
      for ( int i = 0; i < in.n; ++ i ) {
        std::cin >> in.A[i];
      }
      return true;
    }

    void output( const OutputStorage& out ) const {
      for ( int i = 0; i < out.n; ++ i ) {
        std::cout << out.seq[i] << " ";
      }
      std::cout << endl;
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

