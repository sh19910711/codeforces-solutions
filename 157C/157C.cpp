
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

    string s, u;

    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> s >> u;
        }
        string padding() {
            int n = u.size();
            string res = string(n, ' ');
            res += s;
            res += string(n, ' ');
            return res;
        }
        int solve() {
            s = padding();
            int n = s.size();
            int m = u.size();
            int res = m;
            for ( int i = 0; i + m - 1 < n; ++ i ) {
                int cnt = 0;
                for ( int j = 0; j < m; ++ j ) {
                    if ( s[i+j] != u[j] )
                        cnt ++;
                }
                res = min( res, cnt );
            }
            return res;
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

