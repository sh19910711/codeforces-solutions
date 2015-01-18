// @snippet <contest-base-simple#0.0.5:header.cpp>
/* default headers {{{ */
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

#if __cplusplus >= 201103L
#include <memory>
#include <array>
#endif
/* }}} */
// @snippet <contest-base-simple#0.0.5:solution/template-typedef.cpp>
namespace solution {

  using namespace std;

  /* primitives {{{ */
  typedef long long Int;
  typedef long double Double;
  /* }}} */

}
// @snippet <contest-base-simple#0.0.5:solution/template-constants.cpp>
namespace solution {
  // const Int N = 1000000 + 11;
  const Int SIZE = 30000 + 11;
}
// @snippet <contest-base-simple#0.0.5:solution/template-storages.cpp>
namespace solution {

  struct Input {
    Int N;
    Int D;
    Int P[SIZE];
  };

  struct Output {
    Int res;
  };

}
// @snippet <contest-base-simple#0.0.5:solution/solution-io.cpp>
namespace solution {

  struct SolutionIO {

    Input in;
    Output out;

    template <class Stream> bool input( Stream& s ) {
      if ( s >> in.N >> in.D ) {
        for ( int i = 0; i < in.N; ++ i ) {
          s >> in.P[i];
        }
        return true;
      }
      return false;
    }

    template <class Stream> bool output( Stream& s ) {
      return s << out.res << endl;;
    }

  };

}
// @snippet <contest-base-simple#0.0.5:solution/solution.cpp>
namespace solution {

  struct Solution: SolutionIO {

    typedef tuple<Int, Int, Int> Node; // num, cur, prev
    typedef vector<Node> NodeVector;
    typedef priority_queue<Node, NodeVector, greater<Node>> Queue;

    const Int NONE = -1;
    Queue Q;
    Int M[SIZE];
    Int lim;
    Int E[SIZE];
    Int A[SIZE];

    Solution() {
    }

    void init() {
      Q = Queue();
      fill(M, M + SIZE, NONE);
      fill(E, E + SIZE, 0);
      for ( int i = 0; i < in.N; ++ i ) {
        E[in.P[i]] ++;
      }
      copy(in.P, in.P + SIZE, A);
      sort(A, A + in.N);
      lim = *max_element(A, A + in.N);
    }

    bool solve() {
      init();
      out.res = find_max();
      return true;
    }

    Int remains(const Int& x) {
      return in.N - (Int)(lower_bound(A, A + in.N, x) - A);
    }

    Int find_max() {
      Int res = 0;
      Q.emplace(0, in.D, 0);
      while ( ! Q.empty() ) {
        const Node& node = Q.top();
        Q.pop();

        const Int num = get<0>(node);
        const Int cur = get<1>(node);
        const Int prev = get<2>(node);
        const Int len = cur - prev;
        res = max(res, num);

        for ( int i = -1; i < 2; ++ i ) {
          Int nlen = len + i;
          if ( nlen <= 0 ) continue;
          Int ncur = cur + nlen;
          Int nnum = num + E[ncur];
          if ( nnum + remains(ncur) <= res ) continue;
          cout << "push: " << nnum << ", " << ncur << ", " << cur << endl;
          Q.emplace(nnum, ncur, cur);
        }
      }

      return res;
    }

    /* action methods {{{ */
    void before_action( const int& t_id ) {}

    void after_action( const int& t_id ) {}

    bool action( const int& t_id = -1 ) {
      before_action(t_id);
      bool res = input(std::cin) && solve() && output(std::cout);
      after_action(t_id);
      return res;
    }
    /* }}} */
  };

}
// @snippet <contest-base-simple#0.0.5:solution/runner-normal.cpp>
/* Runner Class {{{ */
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
/* }}} */
// @snippet <contest-base-simple#0.0.5:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  return solution::Runner::run();
}
// @snippet <contest-base-simple#0.0.5:main.cpp>

