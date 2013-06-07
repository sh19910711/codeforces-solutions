
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
    
    const int SIZE = 100 + 11;
    const int NONE = -1;

    int b, d;
    string a, c;

    LL solve() {
        LL matches[SIZE];
        int next[SIZE];
        int na = a.size(), nc = c.size();
        for ( int i = 0; i < nc; ++ i ) {
            int k = i, cnt = 0;
            for ( int j = 0; j < na; ++ j ) {
                if ( a[j] == c[k] ) {
                    k ++;
                }
                if ( k >= nc ) {
                    cnt ++;
                    k = 0;
                }
            }
            matches[i] = cnt;
            next[i] = k;
        }

        LL sum = 0;
        int k = 0;
        for ( int i = 0; i < b; ++ i ) {
            sum += matches[k];
            k = next[k];
        }

        return sum / d;
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> b >> d >> a >> c;
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

