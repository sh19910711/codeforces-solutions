
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

    const int SIZE = 2 * 1000000 + 11;
    int n;
    LL A[SIZE];
    map <LL, int> P;
    
    LL solve() {
        sort(A, A + n, greater<int>());
        LL res = accumulate(A, A + n, 0LL);
        int p = 1;
        for ( int i = 0; i < P[n]; ++ i ) {
            LL sum = 0;
            for ( int j = 0; j < p; ++ j ) {
                sum += A[j];
            }
            p *= 4;
            res += sum;
        }
        return res;
    }

    void pre_calc() {
        P.clear();
        LL p = 1;
        for ( int i = 0; p < SIZE; ++ i, p *= 4 ) {
            P[p] = i;
        }
    }

    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
            return true;
        }

        void output( LL result ) {
            cout << result << endl;
        }
        
        int run() {
            pre_calc();
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

