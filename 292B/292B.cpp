
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
    const string TYPE_BUS = "bus topology";
    const string TYPE_RING = "ring topology";
    const string TYPE_STAR = "star topology";
    const string TYPE_NONE = "unknown topology";
    
    int n, m;
    int X[SIZE];
    int Y[SIZE];
    VI G[SIZE];
    int D[SIZE];

    void generate_graph() {
        for ( int i = 0; i < m; ++ i ) {
            int x = X[i] - 1, y = Y[i] - 1;
            G[x].push_back(y);
            G[y].push_back(x);
            D[x] ++;
            D[y] ++;
        }
    }

    class Solution: public ISolution {
    public:
        void init() {
            for ( int i = 0; i < SIZE; ++ i )
                G[i].clear();
            for ( int i = 0; i < SIZE; ++ i )
                D[i] = 0;
        }
        
        bool input() {
            if ( ! ( cin >> n >> m ) )
                return false;
            for ( int i = 0; i < m; ++ i ) {
                cin >> X[i] >> Y[i];
            }
            return true;
        }
        
        void solve() {
            generate_graph();
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

