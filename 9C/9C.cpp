
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

// @snippet<sh19910711/contest:misc/get_binary_string.cpp>
namespace misc {
    template <class T> std::string GetBinaryString( const T& v ) {
        std::ostringstream oss;
        for ( int i = 0; i < static_cast<int>(sizeof v) * 8; ++ i ) {
            int bi = ( v >> i ) & 1;
            oss << bi;
        }
        std::string res = oss.str();
        std::reverse( res.begin(), res.end() );
        return res;
    }
}


// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    
    int n;

    int to_int( const string& s ) {
        ISS iss(s);
        int res;
        iss >> res;
        return res;
    }
    
    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> n;
        }
        int solve() {
            int res = 0;
            for ( int i = 0; i <= (1<<10); ++ i ) {
                string bs = misc::GetBinaryString(i);
                int k = to_int(bs);
                if ( k > 0 && k <= n ) {
                    res ++;
                }
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



