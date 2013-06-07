
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

    const int SIZE = 2 * 100000 + 11;
    int n, k;
    LL A[SIZE];

    void solve() {
        LL l_sum = 0;
        for ( int i = 1, ri = 1; i <= n; ++ i ) {
            LL r_sum = ( ri - 1 ) * ( n - i ) * A[i - 1];
            LL sum = l_sum - r_sum;
            if ( sum < k ) {
                cout << i << endl;
            } else {
                l_sum += A[i - 1] * ( ri - 1 );
                ri ++;
            }
        }
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n >> k ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
            return true;
        }
        
        int run() {
            while ( init(), input() ) {
                solve();
            }
            return 0;
        }
        
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}

