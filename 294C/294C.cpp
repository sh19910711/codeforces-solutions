
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
    
    const int MOD = 1000000000 + 7;
    const int SIZE = 1001;
    int n, m;
    int A[SIZE];

    typedef queue <string> Queue;

    int bfs(string start) {
        string goal(n, 'o');
        int res = 0;
        Queue Q;
        Q.push(start);
        while ( ! Q.empty() ) {
            string s = Q.front();
            Q.pop();
            if ( s == goal ) {
                res ++;
            }
            for ( int i = 0; i < n; ++ i ) {
                if ( s[i] == 'x' ) {
                    if ( i - 1 >= 0 && s[i-1] == 'o' ) {
                        s[i] = 'o';
                        Q.push(s);
                        s[i] = 'x';
                    } else if ( i + 1 < n && s[i+1] == 'o' ) {
                        s[i] = 'o';
                        Q.push(s);
                        s[i] = 'x';
                    }
                }
            }
        }
        return res;
    }

    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n >> m ) )
                return false;
            for ( int i = 0; i < m; ++ i )
                cin >> A[i];
            return true;
        }
        
        int solve() {
            string s(n,'x');
            for ( int i = 0; i < m; ++ i )
                s[A[i]-1] = 'o';
            cout << "s = " << s << endl;
            return bfs(s);
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

