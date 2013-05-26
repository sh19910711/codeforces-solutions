
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

    const string NONE = "no solution";
    const int SIZE = 2000 + 11;
    const int LIMIT = 1000000000;

    int n, k;

    int X[SIZE];
    int Y[SIZE];
    int C;
    LL tot;
    
    bool solve() {
        for ( int i = 0; i <= LIMIT && C < n; ++ i ) {
            X[C] = 0;
            Y[C] = i;
            C ++;
            tot += i;
        }
        return tot > k;
    }

    class Solution: public ISolution {
    public:

        void init() {
            C = 0;
            tot = 0;
        }
        
        bool input() {
            return cin >> n >> k;
        }

        void output( bool result ) {
            if ( result ) {
                for ( int i = 0; i < C; ++ i )
                    cout << X[i] << " " << Y[i] << endl;
            } else {
                cout << NONE << endl;
            }
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

