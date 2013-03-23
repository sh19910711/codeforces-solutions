
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
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
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
// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    LL n, k;

    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> n >> k;
        }
        LL s( LL k ) {
            return k * ( k + 1 ) / 2;
        }
        // 大きい方からx個を使う
        LL g( LL k, LL x ) {
            x = min( k, x );
            return s(k-1) - s(k-1-x) + 1;
        }
        LL f( LL n, LL k ) {
            LL lb = -1, ub = min( n, k );
            while ( ub - lb > 1 ) {
                LL mid = ( lb + ub ) / 2;
                if ( g(k, mid) >= n )
                    ub = mid;
                else
                    lb = mid;
            }
            return ub;
        }
        LL solve() {
            if ( n == 1 )
                return 0;
            if ( g( k, k ) < n )
                return -1;
            return f( n, k );
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

