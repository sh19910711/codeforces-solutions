
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

    const LL MOD = 1000000000LL;
    const int SIZE = 2 * 100000 + 11;
    const int QUERY_SIZE = 2 * 100000 + 11;

    int n, m;
    LL A[SIZE];
    LL F[SIZE];

    void query_1() {
        int x, v;
        cin >> x >> v;
        A[x] = v;
    }

    void query_2() {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        LL sum = 0;
        for ( int i = 0; i < len; ++ i )
            sum = ( sum + F[i] * A[l + i] ) % MOD;
        cout << sum << endl;
    }
    
    void solve() {
        F[0] = F[1] = 1;
        for ( int i = 2; i < SIZE; ++ i )
            F[i] = ( F[i - 1] + F[i - 2] ) % MOD;
        for ( int i = 0; i < m; ++ i ) {
            int t;
            cin >> t;
            if ( t == 1 ) {
                query_1();
            } else if ( t == 2 ) {
                query_2();
            }
        }
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n >> m ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i + 1];
            return true;
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

