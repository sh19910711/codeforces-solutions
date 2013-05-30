
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

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
    };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    const int WIDTH = 300 + 11;
    const int SIZE = 100000 + 11;
    const int NONE = -1;
    const LL INF = std::numeric_limits<LL>::max();

    class Range {
    public:
        int l, r, c;
        Range() {}
        Range( int l, int r, int c ): l(l), r(r), c(c) {}
        friend istream& operator >>( istream& is, Range& r ) {
            return is >> r.l >> r.r >> r.c;
        }
        bool operator < ( const Range& range ) const {
            return l < range.l;
        }
    };

    int N, M, K;
    Range R[SIZE];
    LL dp[WIDTH][WIDTH];

    void sort_ranges() {
        sort(R, R + M);
    }

    LL solve() {
        sort_ranges();

        for ( int i = 0; i <= N; ++ i )
            dp[i][0] = 0;

        for ( int j = 0; j <= N; ++ j ) {
            for ( int i = 0; i <= N; ++ i ) {
                if ( dp[i][j] == INF )
                    continue;
                for ( int k = lower_bound(R, R + M, Range(i, -1, -1)) - R; k < M; ++ k ) {
                    int ni = max(i, R[k].r);
                    int nj = j;
                    if ( i > R[k].r )
                        continue;
                    else if ( R[k].l <= i && i <= R[k].r ) {
                        nj += R[k].r - i;
                    } else {
                        nj += R[k].r - R[k].l + 1;
                    }
                    dp[ni][nj] = min(dp[ni][nj], dp[i][j] + R[k].c);
                }
            }
        }

        LL res = INF;
        for ( int i = 0; i <= N; ++ i )
            for ( int j = K; j <= N; ++ j )
                res = min(res, dp[i][j]);
        return res == INF ? NONE : res;
    }

    class Solution: public ISolution {
    public:

        void init() {
            for ( int i = 0; i < WIDTH; ++ i )
                for ( int j = 0; j < WIDTH; ++ j )
                    dp[i][j] = INF;
        }

        bool input() {
            if ( ! ( cin >> N >> M >> K ) )
                return false;
            for ( int i = 0; i < M; ++ i )
                cin >> R[i];
            return true;
        }

        void output( LL result ) {
            cout << result << endl;
        }

        int run() {
            while ( init(), input() ) {
                output(solve());
            }
            return 0;
        }

    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}

