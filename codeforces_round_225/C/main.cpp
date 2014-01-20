
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

// @snippet<sh19910711/contest:tree/binary_indexed_tree.cpp>
namespace tree {
  template <class T> class BinaryIndexedTree {
  public:
    int n;
    std::vector<T> data;
    
    BinaryIndexedTree() {}
    BinaryIndexedTree( const int& n ): n(n) {
      init(n);
    }

    void init( const int& n ) {
      data = std::vector<T>(n + 1, 0);
    }
    
    T sum( int i ) {
      if ( i < 0 ) {
        return 0;
      }
      i ++;
      T res = 0;
      while ( i > 0 ) { res += data[i]; i -= i & -i; }
      return res;
    }
    
    void add( int i, const T& x ) {
      i ++;
      while ( i <= n ) { data[i] += x; i += i & -i; }
    }
    
    T get( const int& x ) {
      return sum(x) - sum(x - 1);
    }
    
    void set( const int& x, const T& new_value ) {
      add(x, new_value - get(x));
    }
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
  const int SIZE = 200000 + 11;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::pair <Int, Int> II;
  typedef std::set <int> Set;
  typedef tree::BinaryIndexedTree<int> BIT;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int A[SIZE];
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
  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      out.result = find_minimum_milks(in.N, in.A);
      return out;
    }
    
  protected:
    static Int find_minimum_milks( const Int& N, const Int A[SIZE] ) {
      II list[SIZE];
      for ( int i = 0; i < N; ++ i ) {
        if ( A[i] == 0 ) {
          // L
          list[i] = II(N - i, i);
        } else {
          // R
          list[i] = II(i, i);
        }
      }
      std::sort(list, list + N);
      
      BIT tree_left(SIZE);
      BIT tree_right(SIZE);
      for ( int i = 0; i < N; ++ i ) {
        if ( A[i] == 0 ) {
          tree_left.add(i, 1);
        } else {
          tree_right.add(i, 1);
        }
      }

      Int res = 0;
      for ( int i = 0; i < N; ++ i ) {
        const Int& id = list[i].second;
        const Int& dist = list[i].first;
        const Int& dir = A[id];
        // L R[0, i)
        Int cnt_left = tree_right.sum(id - 1);
        // R L(i, N - 1]
        Int cnt_right = tree_left.sum(N - 1) - tree_left.sum(id);
        res += cnt_left + cnt_right;
        tree_left.set(id, 0);
        tree_right.set(id, 0);
      }
      return res;
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
      if ( ! ( std::cin >> in.N ) ) {
        return false;
      }
      for ( int i = 0; i < in.N; ++ i ) {
        std::cin >> in.A[i];
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


