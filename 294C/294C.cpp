
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

namespace math {
    template<class T> T mod_pow( T x, T n, T mod ) {
        if ( n == 0 ) return 1;
        T res = mod_pow( x * x % mod, n / 2, mod );
        if ( n & 1 ) res = res * x % mod;
        return res;
    }
}

namespace math {
    namespace comb {
        const int MOD = 1000000000 + 7;
        const int SIZE = 1001;
        long long C[SIZE][SIZE];
        void init() {
            for ( int i = 0; i < SIZE; ++ i ) {
                for ( int j = 0; j <= i; ++ j ) {
                    if ( j == 0 || j == i )
                        C[i][j] = 1;
                    else
                        C[i][j] = ( C[i-1][j-1] + C[i-1][j] ) % MOD;
                }
            }
        }
        long long calc( int n, int r ) {
            return C[n][r];
        }
    }
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    using namespace math;
    
    const int MOD = 1000000000 + 7;
    const int SIZE = 1001;
    int n, m;
    int A[SIZE];
    int D[SIZE];
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n >> m ) )
                return false;
            for ( int i = 0; i < m; ++ i )
                cin >> A[i];
            return true;
        }
        
        int solve() {
            sort(A, A+m);
            int dc = 0;
            D[dc++] = A[0] - 1;
            D[dc++] = n - A[m-1];
            for ( int i = 0; i + 1 < m; ++ i ) {
                if ( A[i+1] - A[i] > 1 )
                    D[dc++] = A[i+1] - A[i] - 1;
            }
            LL res = 1;
            int remains = n - m;
            for ( int i = 0; i < dc; ++ i ) {
                res = ( res * comb::calc(remains, D[i]) ) % MOD;
                remains -= D[i];
            }
            for ( int i = 2; i < dc; ++ i ) {
                res = ( res * mod_pow(2LL, D[i] - 1LL, (LL)MOD) ) % MOD;
            }
            return res;
        }
        
        void output( int result ) {
            cout << result << endl;
        }
        
        int run() {
            comb::init();
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


