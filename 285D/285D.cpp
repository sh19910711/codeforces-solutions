
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
    
    const LL MOD = 1000000000 + 7;
    const int SIZE = 16;
    int n;
    map<int,LL> dp[1<<SIZE];

    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> n;
        }
        LL calc() {
            int m = 1 << n;
            for ( int i = 0; i <= n; ++ i )
                for ( int j = 0; j < m; ++ j )
                    dp[i][j] = 0;
            dp[0][0] = 1;
            for ( int i = m-1; i >= 0; -- i ) {
                for ( int s = m-1; s >= 0; -- s ) {
                    LL prev = dp[i][s];
                    if ( prev == 0 )
                        continue;
                    for ( int k = 0; k < n; ++ k ) {
                        int c = ( i + k ) % n;
                        int b = 1 << c;
                        if ( ( i & b ) == 0 && ( s & b ) == 0 ) {
                            int ni = i | b;
                            int ns = s | b;
                            // cout << "(" << i << ", " << s << "), (" << ni << ", " << ns << ")" << endl;
                            dp[ni][ns] = ( dp[ni][ns] + prev ) % MOD;
                        }
                    }
                }
            }
            LL whole = 1;
            for ( int i = n; i > 1; -- i ) {
                whole = ( whole * i ) % MOD;
            }
            cout << "whole = " << whole << " / " << m-1 << ": " << dp[m-1][m-1] << endl;
            return ( whole - dp[m-1][m-1] + MOD ) % MOD;
        }
        LL solve() {
            if ( n % 2 == 0 )
                return 0;
            LL res = 1;
            for ( int i = n; i > 1; -- i ) {
                res = ( res * i ) % MOD;
            }
            return ( res * calc() ) % MOD;
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

