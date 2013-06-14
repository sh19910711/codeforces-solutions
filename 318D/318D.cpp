
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

    const int dr[4] = {0, 0, 1, -1};
    const int dc[4] = {1, -1, 0, 0};
    int n, t;
    int M[1000][1000];

    int query(int x, int y) {
        return M[x][y];
    }

    void rec( int x, int y ) {
        if ( x < 0 || y < 0 || x >= 1000 || y >= 1000 )
            return;
        if ( M[x][y] < 3 ) {
            M[x][y] ++;
            return;
        }
        M[x][y] = 0;
        for ( int i = 0; i < 4; ++ i ) {
            rec(x + dr[i], y + dc[i]);
        }
    }

    void solve() {
        for ( int i = 0; i < n; ++ i )
            rec(500, 500);
        for ( int i = 0; i < t; ++ i ) {
            int x, y;
            cin >> x >> y;
            x += 500;
            y += 500;
            if ( x < 0 || y < 0 || x >= 1000 || y >= 1000 )
                cout << query(x, y) << endl;
            else
                cout << 0 << endl;
        }
    }
    
    class Solution: public ISolution {
    public:
        void init() {
            for ( int i = 0; i < 1000; ++ i )
                for ( int j = 0; j < 1000; ++ j )
                    M[i][j] = 0;
        }
        
        bool input() {
            return cin >> n >> t;
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

