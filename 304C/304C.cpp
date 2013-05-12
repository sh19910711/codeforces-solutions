
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

    const int SIZE = 100000 + 11;
    int n;
    int A[SIZE], B[SIZE], C[SIZE];

    bool check() {
        for ( int i = 0; i < n; ++ i )
            if ( ( A[i] + B[i] ) % n != C[i] )
                return false;
        return true;
    }

    void solve() {
        cout << "n = " << n << endl;
        for ( int i = 0; i < n; ++ i )
            A[i] = B[i] = C[i] = i;
        do {
            do {
                do {
                    if ( check() ) {
                        for ( int i = 0; i < n; ++ i ) {
                            cout << A[i] << ", ";
                        }
                        cout << endl;
                        for ( int i = 0; i < n; ++ i ) {
                            cout << B[i] << ", ";
                        }
                        cout << endl;
                        for ( int i = 0; i < n; ++ i ) {
                            cout << C[i] << ", ";
                        }
                        cout << endl;
                        return;
                    }
                } while (next_permutation(C, C + n));
            } while (next_permutation(B, B + n));
        } while(next_permutation(A, A + n));
    }

    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> n;
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

