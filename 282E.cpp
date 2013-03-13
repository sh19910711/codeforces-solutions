
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
    int n;
    LL A[SIZE];
    int B[SIZE];

    class Solution: public ISolution {
    public:
        bool input() {
            int k;
            if ( ! ( cin >> k ) )
                return false;
            n = 0;
            for ( int i = 0; i < k; ++ i ) {
                int a;
                cin >> a;
                if ( ! a )
                    continue;
                A[n++] = a;
            }
            return true;
        }
        LL solve() {
            if ( n == 0 )
                return 0;

            LL L[SIZE];
            LL R[SIZE];
            fill( L, L+SIZE, 0LL );
            fill( R, R+SIZE, 0LL );
            for ( int i = 0; i < n; ++ i ) {
                L[i] ^= A[i];
                R[i] ^= A[n-i-1];
                if ( i - 1 >= 0 ) {
                    L[i] ^= L[i-1];
                    R[i] ^= R[i-1];
                }
            }

            for ( int i = 0; i < n; ++ i )
                B[i] = log2(A[i]) + 1;
            int maxb = 0;
            for ( int i = 0; i < n; ++ i ) {
                maxb = max( maxb, B[i] );
            }
            // cout << "maxb: " << maxb << endl;
            LL res = 0;
            for ( int i = 0; i < n; ++ i ) {
                if ( A[i] & maxb ) {
                    // cout << i << ": " << A[i] << ", L = " << L[i] << ", R = " << R[n-i-1] << endl;
                    res = max( res, max( L[i], R[n-i-1] ) );
                }
            }
            return res;
        }
        int run() {
            while ( init(), input() ) {
                cout << solve() << endl;
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


