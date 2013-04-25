
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

    const int SIZE = 1000011;
    int k;
    int n;
    LL A[SIZE];
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> k ) )
                return false;
            n = 0;
            for ( int i = 0; i < k; ++ i ) {
                LL x;
                cin >> x;
                if ( x > 1 )
                    A[n ++] = x;
            }
            return true;
        }
        
        LL solve() {
            if ( n == 0 )
                return 1;
            sort(A, A + n);
            LL res = 0;
            for ( int i = 0; i < n; ++ i ) {
                LL num = n - i;
                res = max(res, A[i] * num);
            }
            return res;
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

