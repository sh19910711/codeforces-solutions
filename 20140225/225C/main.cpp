
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cmath>

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif

// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int SIZE = 1000 + 11;
  const Int CNT_SIZE = SIZE * 2 + 11;
  const char CELL_BLACK = '#';
  const char CELL_WHITE = '.';
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int X;
    Int Y;
    String S[SIZE];
  };
  struct Output {
    Int result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //

    Input in;
    Output out;

    const Int INF = std::numeric_limits<Int>::max();

    Int n;
    Int cnt[CNT_SIZE][2];

    Int changes[CNT_SIZE][2];
    Int sum[CNT_SIZE][2];
    
    Solution() {}
    
    bool solve() {
      n = in.M;
      for ( auto i = 0; i < CNT_SIZE; ++ i ) {
        for ( auto j = 0; j < 2; ++ j ) {
          cnt[i][j] = INF;
          sum[i][j] = INF;
        }
      }
      init_changes();
      init_sum();
      out.result = get_min();
      return true;
    }

    void init_sum() {
      sum[0][0] = 0;
      sum[0][1] = 0;
      for ( auto i = 1; i <= n; ++ i ) {
        for ( auto j = 0; j < 2; ++ j ) {
          sum[i][j] = sum[i - 1][j] + changes[i][j];
        }
      }
    }

    Int get_min() {
      cnt[0][0] = cnt[0][1] = 0;
      for ( auto i = 1; i <= n; ++ i ) {
        for ( auto j = 0; j < 2; ++ j ) {
          cnt[i][j] = INF;
          for ( auto d = in.X; d <= in.Y; ++ d ) {
            if ( i - d < 0 )
              continue;
            Int& cur = cnt[i - d][j ^ 1];
            if ( cur == INF )
              continue;
            Int& next = cnt[i][j];
            next = std::min(next, cur + get_sum(j ^ 1, i - d + 1, i));
          }
        }
      }
      return std::min(cnt[n][0], cnt[n][1]);
    }

    Int get_sum( const Int& t, const Int& id ) {
      if ( id < 0 )
        return 0;
      return sum[id][t];
    }

    Int get_sum( const Int& t, const Int& l, const Int& r ) {
      return get_sum(t, r) - get_sum(t, l - 1);
    }

    void init_changes() {
      for ( auto i = 0; i < n; ++ i ) {
        changes[i + 1][0] = count_changes(i, CELL_WHITE);
        changes[i + 1][1] = count_changes(i, CELL_BLACK);
      }
    }

    Int count_changes( const Int& pos, const char& to_be ) {
      Int res = 0;
      for ( auto i = 0; i < in.N; ++ i ) {
        if ( in.S[i][pos] != to_be )
          res ++;
      }
      return res;
    }
    
    template <class Stream> bool input( Stream& s ) {
      if ( ! ( s >> in.N >> in.M >> in.X >> in.Y ) )
        return false;
      for ( auto i = 0; i < in.N; ++ i )
        if ( ! ( s >> in.S[i] ) )
          return false;
      return s;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.result << std::endl;
    }
    
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    //
    //
    //
    bool action( const int& t_id = -1 ) {
      before_action(t_id);
      bool res = input(std::cin) && solve() && output(std::cout);
      after_action(t_id);
      return res;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/runner-normal.cpp>
namespace solution {
  struct Runner {
    static int run() {
      bool f = false;
      while ( ! f ) {
        Solution* sol = new Solution;
        f = ! sol->action();
        delete sol;
      };
      return 0;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  return solution::Runner::run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

