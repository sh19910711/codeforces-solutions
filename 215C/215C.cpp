
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

    LL H, W, S;
    
    LL solve() {
        LL res = 0;
        for ( LL h = 1; h <= H; h += 2 ) {
            for ( LL w = 1; w <= W; w += 2 ) {
                LL area = h * w;
                if ( area < S ) {
                    continue;
                } else if ( area == S ) {
                    LL pat = 2 * ( w + 1 ) * ( h + 1 ) / 4 - 1;
                    res += pat * ( W - w + 1 ) * ( H - h + 1 );
                    continue;
                } else {
                    area -= S;
                    if ( area % 4 )
                        continue;
                    area /= 4;
                    for ( LL k = 1; k * k <= area; ++ k ) {
                        if ( area % k )
                            continue;
                        LL pat = 0;
                        LL l = area / k;
                        if ( k < ( h + 1 ) / 2 && l < ( w + 1 ) / 2 ) {
                            pat ++;
                        }
                        if ( k != l && l < ( h + 1 ) / 2 && k < ( w + 1 ) / 2 ) {
                            pat ++;
                        }
                        res += pat * 2 * ( W - w + 1 ) * ( H - h + 1 );
                    }
                }
            }
        }
        return res;
    }

    class Solution: public ISolution {
    public:

        bool input() {
            return cin >> H >> W >> S;
        }

        void output( LL result ) {
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

