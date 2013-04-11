
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
    int n, m, k;
    LL A[SIZE];
    int L[SIZE], R[SIZE];
    LL D[SIZE];
    int X[SIZE], Y[SIZE];

    class BIT {
    public:
        LL bit0[SIZE + 1], bit1[SIZE + 1];

        void init() {
            for ( int i = 0; i < SIZE + 1; ++ i ) {
                bit0[i] = 0;
                bit1[i] = 0;
            }
        }

        LL sum( LL *b, LL i ) {
            LL s = 0;
            while ( i > 0 ) {
                s += b[i];
                i -= i & -i;
            }
            return s;
        }

        void add( LL *b, LL i, LL v ) {
            while ( i <= n ) {
                b[i] += v;
                i += i & -i;
            }
        }

        void range_add( LL l, LL r, LL x ) {
            add(bit0, l, -x * (l - 1));
            add(bit1, l, x);
            add(bit0, r + 1, x * r);
            add(bit1, r + 1, -x);
        }

        LL get( LL k ) {
            LL l = k, r = k;
            LL res = 0;
            res += sum(bit0, r) + sum(bit1, r) * r;
            res -= sum(bit0, l - 1) + sum(bit1, l - 1) * ( l - 1 );
            return res;
        }
    };

    BIT B1, B2;
    
    class Solution: public ISolution {
    public:

        void init() {
            B1.init();
            B2.init();
        }
        
        bool input() {
            if ( ! ( cin >> n >> m >> k ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
            for ( int i = 0; i < m; ++ i ) {
                cin >> L[i] >> R[i] >> D[i];
            }
            for ( int i = 0; i < k; ++ i )
                cin >> X[i] >> Y[i];
            return true;
        }
        
        void solve() {
            for ( int i = 0; i < k; ++ i ) {
                B1.range_add( X[i], Y[i], 1LL );
            }
            for ( int i = 0; i < n; ++ i ) {
                B2.range_add( i+1, i+1, A[i] );
            }
            for ( int i = 1; i <= m; ++ i ) {
                LL t = B1.get(i);
                B2.range_add( L[i-1], R[i-1], D[i-1] * t );
            }
            for ( int i = 1; i <= n; ++ i ) {
                cout << B2.get(i);
                if ( i + 1 <= n )
                    cout << " ";
            }
            cout << endl;
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

