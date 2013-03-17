
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

    typedef pair<LL, LL> State;
    const int SIZE = 200011;
    int n;
    int A[SIZE];

    map <State, LL> memo;
    set <State> visited;

    LL rec( LL x, LL px ) {
        if ( x <= 0 || x > n )
            return 0;
        State s( x, px );
        px = x;
        if ( memo.count(s) )
            return memo[s];
        LL a1 = A[x];
        x += A[x];
        if ( x <= 0 || x > n )
            return a1;
        if ( visited.count(s) )
            return -1;
        visited.insert(s);
        LL a2 = A[x];
        x -= A[x];
        LL ret = rec( x, px );
        if ( ret == -1 )
            return -1;
        return memo[s] = a1 + a2 + ret;
    }

    class Solution: public ISolution {
    public:
        void init() {
            memo.clear();
            visited.clear();
        }
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 2; i <= n; ++ i ) {
                cin >> A[i];
            }
            return true;
        }
        void solve() {
            for ( int i = 1; i <= n-1; ++ i ) {
                visited.clear();
                A[1] = i;
                cout << rec( 1, -i ) << endl;
            }
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


