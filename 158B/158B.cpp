
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
    int n;
    int A[SIZE];

    class Solution: public ISolution {
    public:
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
            return true;
        }
        int solve() {
            bool used[n];
            fill( used, used+n, false );
            sort( A, A+n );
            int res = 0;
            int begin = 0;
            for ( int i = n-1; i >= 0; -- i ) {
                if ( used[i] )
                    continue;
                int sum = A[i];
                used[i] = true;
                for ( int j = begin; j < n; ++ j ) {
                    if ( used[begin] )
                        continue;
                    if ( sum + A[j] > 4 )
                        break;
                    sum += A[j];
                    used[j] = true;
                    begin ++;
                }
                res ++;
            }
            return res;
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

