
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

    const int SIZE = 1011;
    const int MAX_TIME = 1000011;
    int n;
    int T[SIZE];
    int C[SIZE];
    LL X[MAX_TIME];
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> T[i] >> C[i];
            return true;
        }
        
        void solve() {
            fill( X, X+MAX_TIME, 0 );
            for ( int i = 0; i < n; ++ i )
                X[T[i]] += C[i];
            LL t = 0;
            LL res = 0;
            LL sum = 0;
            for ( LL i = 0; i < MAX_TIME; ++ i ) {
                if ( sum > 0 ) {
                    t = max( t, i );
                    sum --;
                }
                sum += X[i];
                res = max( res, sum );
            }
            if ( sum ) {
                t += sum;
            }
            cout << t << " " << res << endl;
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

