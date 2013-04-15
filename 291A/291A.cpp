
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

    const int SIZE = 1001;
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
            set <int> V;
            map <int, int> C;
            for ( int i = 0; i < n; ++ i ) {
                if ( A[i] == 0 )
                    continue;
                V.insert(A[i]);
                C[A[i]] ++;
            }
            int res = 0;
            for ( set<int>::iterator it_i = V.begin(); it_i != V.end(); ++ it_i ) {
                if ( C[*it_i] == 2 )
                    res ++;
                else if ( C[*it_i] > 2 )
                    return -1;
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

