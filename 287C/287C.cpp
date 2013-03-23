
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
    const int MOD = 4;
    const int SIZE = 100011;
    int n;
    int A[SIZE];
    int AC;
    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> n;
        }
        bool check_no_solution() {
            if ( ( n % MOD == 0 ) || ( n % MOD == 1 ) )
                return false;
            return true;
        }
        void solve() {
            if ( check_no_solution() ) {
                AC = 1;
                A[0] = -1;
                return;
            }
            fill( A, A+n, 0 );
            AC = n;
            if ( n % 2 == 0 ) {
                for ( int i = 0; i < n/2; i += 2 ) {
                    A[i] = i + 2;
                }
                for ( int i = 0; i < n/2; i += 2 ) {
                    A[i+1] = n - i;
                }
                for ( int i = 0; i < n/2; i += 2 ) {
                    A[n/2+i] = n/2 - (i/2)*2 - 1;
                }
                for ( int i = 0; i < n/2; i += 2 ) {
                    A[n/2+i+1] = n/2 + (i/2)*2 + 1;
                }
            } else {
                for ( int i = 0; i < n/2; i += 2 ) {
                    A[i] = i + 2;
                }
                for ( int i = 0; i < n/2; i += 2 ) {
                    A[i+1] = n - i;
                }
                for ( int i = 0; i < n/2; i += 2 ) {
                    A[n/2+i+1] = n/2 - (i/2)*2 - 1;
                }
                for ( int i = 0; i < n/2; i += 2 ) {
                    A[n/2+i+1+1] = n/2 + (i/2)*2 + 1 + 1;
                }
                A[n/2] = n/2 + 1;
            }
        }
        void output() {
            for ( int i = 0; i < AC; ++ i ) {
                cout << A[i] << " ";
            }
            cout << endl;
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

