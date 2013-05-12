
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
    typedef long double LD;
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

// @snippet<sh19910711/contest:math/gcd.cpp>
namespace math {
    template <class T> T gcd( T a, T b ) {
        T i, j;
        for ( i = 0; ! ( a & 1 ); ++ i ) a >>= 1;
        for ( j = 0; ! ( b & 1 ); ++ j ) b >>= 1;
        while ( b != a ) {
            b -= a;
            if ( b < 0 ) a += b, b = -b;
            while ( ! ( b & 1 ) ) b >>= 1;
        }
        return a << std::min( i, j );
    }
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    
    typedef pair <LL, LL> Pos;
    typedef pair <Pos, Pos> Rect;
    typedef pair <LD, Rect> Result;
    
    const LL INF = std::numeric_limits<LL>::max();
    
    LL n, m, x, y, a, b;
    LD s;
    
    bool is_number( LD x ) {
        return fabs(ceil(x) - floor(x)) < 1e-9;
    }
    
    LD get_offset() {
        LD scale = s + 1.0 / (LD)math::gcd(a, b);
        LD da = a, db = b;
        LD sa = da * scale, sb = db * scale;
        if ( is_number(sa) && is_number(sb) && sa <= n && sb <= m )
            return 0.5;
        return 0.0;
    }
    
    LD sq( LD x ) {
        return x * x;
    }
    
    LD get_dist( LD x1, LD y1, LD x2, LD y2 ) {
        return sq(x2 - x1) + sq(y2 - y1);
    }
    
    Result solve() {
        for ( s = 1; s <= max(n, m); ++ s ) {
            LL ns = s + 1;
            if ( a * ns > n || b * ns > m )
                break;
        }
        Result res(INF, Rect(Pos(INF, INF), Pos(INF, INF)));
        LD ds = s;
        LD scale = ds + get_offset();
        LL na = a * scale, nb = b * scale;
        for ( int i = -2500; i <= 2500; ++ i ) {
            for ( int j = -2500; j <= 2500; ++ j ) {
                LL x1 = x - i, y1 = y - j;
                LL x2 = x1 + na, y2 = y1 + nb;
                if ( x1 < 0 || x1 > n || y1 < 0 || y1 > m )
                    continue;
                if ( x2 < 0 || x2 > n || y2 < 0 || y2 > m )
                    continue;
                if ( ! ( x1 <= x && x <= x2 ) || ! ( y1 <= y && y <= y2 ) )
                    continue;
                Result tmp(get_dist(x, y, (LD)(x1 + x2) / 2.0, (LD)(y1 + y2) / 2.0), Rect(Pos(x1, y1), Pos(x1 + na, y1 + nb)));
                res = min(res, tmp);
            }
        }
        return res;
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> n >> m >> x >> y >> a >> b;
        }
        
        void output( Result result ) {
            cout << result.second.first.first << " " << result.second.first.second << " ";
            cout << result.second.second.first << " " << result.second.second.second << endl;
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


