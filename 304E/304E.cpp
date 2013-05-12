
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

    typedef map <int, int> Map;

    const int SIZE = 5001;
    const int CANDS = SIZE * 200 + 11 + 200000;
    const int INF = std::numeric_limits<int>::max();

    int n, k;
    int A[SIZE];
    Map C[CANDS];
    int O[CANDS];
    int X[CANDS];
    int XC;

    void get_cands() {
        for ( int i = 0; i < n; ++ i ) {
            for ( int j = -100; j <= 100; ++ j ) {
                if ( A[i] + j > 0 )
                    X[XC ++] = A[i] + j;
            }
        }
    }

    int solve() {
        if ( n == 1 )
            return 1;
        get_cands();
        for ( int i = 0; i < XC; ++ i ) {
            for ( int j = 0; j < n; ++ j ) {
                int& cnt = C[i][A[j] % X[i]];
                cnt ++;
                if ( cnt >= 2 )
                    O[i] ++;
            }
        }
        int res = INF;
        for ( int i = 0; i < XC; ++ i ) {
            if ( O[i] <= k )
                res = min(res, X[i]);
        }
        return res;
    }

    class Solution: public ISolution {
    public:

        void init() {
            XC = 0;
            for ( int i = 0; i < CANDS; ++ i )
                C[i].clear();
            fill(O, O + CANDS, 0);
        }
        
        bool input() {
            if ( ! ( cin >> n >> k ) )
                return false;
            for ( int i = 0; i < n; ++ i )
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

