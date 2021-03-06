
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

    const int SIZE = 10011;
    int n, k;
    int A[SIZE];
    int B[SIZE];
    int R[30][SIZE];
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> n >> k;
        }

        bool check( int x, int k ) {
            return x != k && A[x] + A[k] <= x;
        }

        int search( int x ) {
            int lb = 0, ub = n;
            while ( ub - lb > 1 ) {
                int mid = ( lb + ub ) / 2;
                if ( check(x, mid) ) {
                    lb = mid;
                } else {
                    ub = mid;
                }
            }
            return lb;
        }

        void calc( int t ) {
            for ( int i = 0; i < n; ++ i ) {
                int need = i;
                if ( need == A[i] ) {
                    R[t][i] = 0;
                    B[i] = A[i];
                } else {
                    int ret = search(i);
                    R[t][i] = ret;
                    B[i] = A[i] + A[ret];
                }
            }
            for ( int i = 0; i < n; ++ i )
                A[i] = B[i];
        }
        
        void solve() {
            A[0] = 0;
            for ( int i = 1; i < n; ++ i ) {
                A[i] = 1;
            }

            for ( int t = 0; t < k; ++ t ) {
                calc(t);
            }
        }

        void output() {
            for ( int i = 0; i < k; ++ i ) {
                for ( int j = n-1; j >= 0; -- j ) {
                    cout << n - R[i][j] << " ";
                }
                cout << endl;
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

