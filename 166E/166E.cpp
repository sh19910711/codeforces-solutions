
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

    const int MOD = 1000000000 + 7;
    int n;
    int dp[2][4];

    class Solution: public ISolution {
    public:

        bool input() {
            return cin >> n;
        }

        int solve() {
            enum LOCATE { A, B, C, D };
            fill( dp[0], dp[0]+4, 0 );
            dp[0][D] = 1;
            for ( int i = 0; i < n; ++ i ) {
                int cur = i & 1;
                int next = cur ^ 1;
                dp[next][A] = ( ( dp[cur][B] + dp[cur][C] ) % MOD + dp[cur][D] ) % MOD;
                dp[next][B] = ( ( dp[cur][A] + dp[cur][C] ) % MOD + dp[cur][D] ) % MOD;
                dp[next][C] = ( ( dp[cur][B] + dp[cur][A] ) % MOD + dp[cur][D] ) % MOD;
                dp[next][D] = ( ( dp[cur][B] + dp[cur][C] ) % MOD + dp[cur][A] ) % MOD;
            }
            return dp[n&1][D] % MOD;
        }

        void output( int result ) {
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

