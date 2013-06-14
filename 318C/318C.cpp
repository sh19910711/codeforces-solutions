
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

    const LL INF = 1000000000000000000LL + 11LL;
    typedef vector<LL> VLL;
    typedef vector<VLL> Mat;
    LL x, y, m;

    Mat get_matrix() {
        Mat res(2, VLL(2, 0));
        return res;
    }

    void init_matrix( Mat& a ) {
        for ( LL i = 0; i < 2; ++ i ) {
            for ( LL j = 0; j < 2; ++ j ) {
                a[i][j] = 0;
            }
        }
    }

    Mat mul( Mat a, Mat b ) {
        Mat res = get_matrix();
        for ( LL i = 0; i < 2; ++ i ) {
            for ( LL k = 0; k < 2; ++ k ) {
                for ( LL j = 0; j < 2; ++ j ) {
                    if ( a[i][k] >= INF || b[k][j] >= INF || ( b[k][j] > 0 && a[i][k] >= INF / b[k][j] ) || res[i][j] + a[i][k] * b[k][j] >= INF )
                        res[i][j] = INF;
                    else
                        res[i][j] = res[i][j] + a[i][k] * b[k][j];
                }
            }
        }
        return res;
    }

    Mat pow( Mat a, LL n ) {
        if ( n == 0 ) return get_matrix();
        n --;
        Mat res = get_matrix();
        init_matrix(res);
        for ( LL i = 0; i < 2; ++ i ) {
            res[i][i] = 1;
        }
        while ( n > 0 ) {
            if ( n & 1 ) res = mul( a, res );
            a = mul( a, a );
            n >>= 1;
        }
        return res;
    }

    LL calc( LL f, LL s, LL n ) {
        if ( n <= 0 )
            return f;
        Mat a = get_matrix();
        a[0][0] = 1;
        a[0][1] = 1;
        a[1][0] = 1;
        a[1][1] = 0;
        a = pow( a, n );
        if ( f >= INF || s >= INF || a[1][0] >= INF || a[0][0] >= INF || ( f > 0 && a[1][0] >= INF / f ) || ( s > 0 && a[0][0] >= INF / s ) )
            return INF;
        if ( a[1][0] * f >= INF - a[0][0] * s )
            return INF;
        return a[1][0] * f + a[0][0] * s;
    }

    LL solve() {
        if ( x >= m || y >= m ) {
            return 0;
        }

        if ( x <= 0 && y <= 0 ) {
            return -1;
        }

        if ( x > y )
            swap(x, y);

        LL t = 0;
        if ( x < 0 ) {
            LL ax = abs(x);
            t = ceil((double)ax / y);
            x += y * t;
        }

        if ( x > y )
            swap(x, y);

        LL lb = 0, ub = INF;
        while ( ub - lb > 1 ) {
            LL mid = ( lb + ub ) / 2;
            if ( calc(x, y, mid) >= m ) {
                ub = mid;
            } else {
                lb = mid;
            }
        }

        LL res = ub - 1 + t;

        return res;
    }

    class Solution: public ISolution {
    public:

        bool input() {
            return cin >> x >> y >> m;
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

