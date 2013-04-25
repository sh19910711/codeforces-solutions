
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


// @snippet<sh19910711/contest:math/extgcd.cpp>
namespace math {
    // 拡張ユークリッド互除法: a*x+b*y=gcd(x,y)
    template <class T> T extgcd( T a, T b, T& x, T& y ) {
        for ( T u = y = 1, v = x = 0; a; ) {
            T q = b / a;
            std::swap( x -= q * u, u );
            std::swap( y -= q * v, v );
            std::swap( b -= q * a, a );
        }
        return b;
    }
}

// @snippet<sh19910711/contest:math/mod_inverse.cpp>
namespace math {
    // @desc mod mでaの逆元を求める
    template <class T> T mod_inverse( T a, T m ) {
        T x, y;
        extgcd( a, m, x, y );
        x %= m;
        while ( x < 0 )
            x += m;
        return x;
    }
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    
    const LL MOD = 1000000000 + 7;
    const int SIZE = 1000011;
    
    int a, b, n;
    LL F[SIZE];
    LL I[SIZE];
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> a >> b >> n;
        }
        
        LL permutation( int n, int r ) {
            return ( ( F[n] * I[r] ) % MOD * I[n - r] ) % MOD;
        }

        bool is_good( int x ) {
            while ( x > 0 ) {
                if ( x % 10 != a && x % 10 != b )
                    return false;
                x /= 10;
            }
            return true;
        }
        
        LL calc( int x ) {
            int sum = a * x + b * ( n - x );
            if ( is_good(sum) )
                return permutation(n, x);
            return 0;
        }
        
        LL solve() {
            int res = 0;
            for ( int i = 0; i <= n; ++ i )
                res = ( res + calc(i) ) % MOD;
            return res % MOD;
        }
        
        void output( LL result ) {
            cout << result << endl;
        }
        
        void pre_calc() {
            F[0] = F[1] = 1;
            for ( int i = 2; i < SIZE; ++ i )
                F[i] = ( i * F[i - 1] ) % MOD;
            for ( int i = 0; i < SIZE; ++ i )
                I[i] = math::mod_inverse(F[i], MOD);
        }
        
        int run() {
            pre_calc();
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


