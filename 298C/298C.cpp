
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

    const string YES = "YES";
    const string NO = "NO";
    string a, b;
    int na, nb;
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> a >> b;
        }
        
        bool solve() {
            na = a.size();
            nb = b.size();
            int cb_a = count(b.begin(), b.end(), '1');
            for ( int i = 1; i <= min(na, nb); ++ i ) {
                string sa = a.substr(na-i);
                string sb = b.substr(0, i);
                string rb = b.substr(i);
                int ca = count(sa.begin(), sa.end(), '1');
                int cb = count(rb.begin(), rb.end(), '1');
                if ( sa == sb && cb == 0 )
                    return true;
                else if ( ca + 1 == cb_a && ca % 2 == 1 && cb == 1 && rb[0] == '1' )
                    return true;
            }
            return false;
        }

        void output( bool result ) {
            cout << ( result ? YES : NO ) << endl;
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

