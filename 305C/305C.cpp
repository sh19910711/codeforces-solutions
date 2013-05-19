
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

    typedef map <LL, LL> Map;
    const int SIZE = 100000 + 11;

    int n;
    LL A[SIZE];
    Map C;
    LL K;
    
    bool update() {
        for ( Map::iterator it_i = C.begin(); it_i != C.end(); ++ it_i ) {
            LL x = (*it_i).first;
            LL y = (*it_i).second;
            if ( y >= 2 ) {
                C[x] -= 2;
                if ( C[x] == 0 )
                    C.erase(x);
                C[x + 1] += 1;
                K = max(K, x + 1);
                return true;
            }
        }
        return false;
    }

    int solve() {
        K = *max_element(A, A + n);
        for ( int i = 0; i < n; ++ i )
            C[A[i]] ++;
        while ( update() );
        return ( K + 1 ) - C.size();
    }

    class Solution: public ISolution {
    public:

        void init() {
            C.clear();
        }
        
        bool input() {
            if ( ! ( cin >> n ) )
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

