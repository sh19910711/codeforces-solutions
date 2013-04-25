
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

    const int SIZE = 100011;
    const LL MOD = 7340033;

    int Q;
    int N[SIZE];
    int K[SIZE];
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> Q ) )
                return false;
            for ( int i = 0; i < Q; ++ i )
                cin >> N[i] >> K[i];
            return true;
        }

        LL calc( int n, int k ) {
            if ( k <= 0 )
                return 1;
            if ( n < 3 || n % 2 == 0 )
                return 0;
            if ( n == 3 )
                return k == 1 ? 1 : 0;
            return ( 4LL * calc( ( n - 1 ) / 2, k - 1 ) ) % MOD;
        }
        
        void solve() {
            for ( int i = 0; i < Q; ++ i )
                cout << calc(N[i], K[i]) << endl;
        }
        
        int run() {
            while ( init(), input() ) {
                solve();
                output();
            }
            return 0;
        }
        
    };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
    return solution::Solution().run();
}

