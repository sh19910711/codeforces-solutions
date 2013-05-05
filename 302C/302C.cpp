
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

    const int SIZE = 256;
    int n, m;
    int A[SIZE];

    int f() {
        int res = accumulate(A, A + m, 0);
        for ( int i = 0; i < 900; ++ i ) {
            random_shuffle(A, A + m);
            for ( int j = 0; j < n; ++ j ) {
                A[j] *= -1;
            }
            for ( int j = 0; j < 300; ++ j ) {
                sort(A, A + m);
                res = max(res, accumulate(A, A + m, 0));
                for ( int k = 0; k < n; ++ k )
                    A[k] *= -1;
                res = max(res, accumulate(A, A + m, 0));
            }
        }
        return res;
    }

    int solve() {
        m = 2 * n - 1;
        return f();
    }

    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < 2 * n - 1; ++ i )
                cin >> A[i];
            return true;
        }

        void output( int result ) {
            cout << result << endl;
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

