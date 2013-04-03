
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
    int n;
    bool used[SIZE];
    int A[SIZE];

    int get_digits( int x ) {
        if ( x == 0 )
            return 0;
        return log2(x) + 1;
    }

    class Solution: public ISolution {
    public:
        
        void init() {
            fill( used, used+SIZE, false );
            fill( A, A+SIZE, 0 );
        }

        bool input() {
            return cin >> n;
        }

        int solve() {
            int res = 0;
            for ( int i = n; i >= 0; -- i ) {
                if ( used[i] )
                    continue;
                int d = get_digits(i);
                int bd = 1 << d;
                int inv = ( bd - 1 ) ^ i;
                A[i] = inv;
                A[inv] = i;
                res += 2 * ( i ^ inv );
                used[i] = used[inv] = true;
            }
            return res;
        }

        void output( int result ) {
            cout << result << endl;
            for ( int i = 0; i < n+1; ++ i ) {
                cout << A[i] << " ";
            }
            cout << endl;
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

