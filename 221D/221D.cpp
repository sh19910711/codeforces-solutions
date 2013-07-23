
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
  typedef std::map<int, int> Map;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100000 + 11;
  const int MAX_VALUES = 500 + 11;
  // storages
  int n;
  int m;
  int A[SIZE];
  int L[SIZE];
  int R[SIZE];

  Map id_map;
  Map value_cnt;
  int values[SIZE];
  int id_list[SIZE];
  int id_num;

  int good_values[MAX_VALUES];
  int good_values_num;
  int good_value_id[MAX_VALUES];

  int cnt_sum[MAX_VALUES][SIZE];

  int query_result[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      compress_a(A, n);
      find_good_values();
      calc_cnt_sum();

      for ( int i = 0; i < m; ++ i ) {
        query_result[i] = query(L[i], R[i]);
      }
    }

    int query( int l, int r ) {
      int res = 0;
      for ( int i = 0; i < good_values_num; ++ i ) {
        int good_value = good_values[i];
        int sum = cnt_sum[i][r] - cnt_sum[i][l - 1];
        if ( sum == good_value ) {
          res ++;
        }
      }
      return res;
    }

    void calc_cnt_sum() {
      for ( int i = 0; i < good_values_num; ++ i ) {
        int good_id = good_value_id[i];
        cnt_sum[i][0] = 0;
        for ( int j = 1; j <= n; ++ j ) {
          int id = id_list[j - 1];
          cnt_sum[i][j] = cnt_sum[i][j - 1] + ( good_id == id ? 1 : 0 );
        }
      }
    }

    void find_good_values() {
      for ( int i = 0; i < id_num; ++ i ) {
        int value = values[i];
        if ( value_cnt[value] < value )
          continue;
        if ( value > n )
          continue;
        good_values[good_values_num] = value;
        good_value_id[good_values_num] = i;
        good_values_num ++;
      }
    }

    void compress_a( const int* A, const int& num ) {
      for ( int i = 0; i < num; ++ i ) {
        const int a = A[i];
        if ( id_map.count(a) ) {
          value_cnt[a] ++;
          id_list[i] = id_map[a];
          continue;
        } else {
          id_map[a] = id_num;
          values[id_num] = a;
          value_cnt[a] ++;
          id_list[i] = id_num;
          id_num ++;
        }
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
      std::fill(query_result, query_result + SIZE, -1);
      id_num = 0;
      id_map.clear();
      good_values_num = 0;
      value_cnt.clear();
    }

    bool input() {
      if ( ! ( cin >> n >> m ) ) {
        return false;
      }
      for ( int i = 0; i < n; ++ i ) {
        cin >> A[i];
      }
      for ( int i = 0; i < m; ++ i ) {
        cin >> L[i] >> R[i];
      }
      return true;
    }

    void output() {
      for ( int i = 0; i < m; ++ i ) {
        cout << query_result[i] << endl;
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

