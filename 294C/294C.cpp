
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
    bool U[SIZE];
    int dp[2][SIZE][2];
    enum LIGHT_STATE { ON, OFF };

    int get( int k ) {
        return k & 1;
    }

    int flip( int k ) {
        return ( k ^ 1 ) & 1;
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

        void dp_init( int k ) {
            for ( int i = 0; i < SIZE; ++ i ) {
                for ( int j = 0; j < 2; ++ j ) {
                    dp[k][i][j] = 0;
                }
            }
        }

        void dp_copy( int from ) {
            int to = flip(from);
            for ( int i = 0; i < SIZE; ++ i ) {
                for ( int j = 0; j < 2; ++ j ) {
                    dp[to][i][j] = dp[from][i][j];
                }
            }
        }

        void dp_print( int k ) {
            cout << "ON:  ";
            for ( int i = 0; i < n; ++ i )
                cout << dp[k][i][ON] << ", ";
            cout << endl;
            cout << "OFF: ";
            for ( int i = 0; i < n; ++ i )
                cout << dp[k][i][OFF] << ", ";
            cout << endl;
            cout << endl;
        }
        
        int solve() {
            for ( int i = 0; i < 2; ++ i )
                dp_init(i);

            for ( int i = 0; i < n; ++ i ) {
                dp[0][i][OFF] = 1;
            }
            for ( int i = 0; i < m; ++ i ) {
                int a = A[i] - 1;
                dp[0][a][OFF] = 0;
                dp[0][a][ON] = 1;
            }

            for ( int i = 0; i < n - m; ++ i ) {
                int cur = get(i);
                int next = flip(cur);

                cout << "cur: i = " << i << endl;
                dp_print(cur);

                dp_init(next);
                for ( int j = 0; j < n; ++ j ) {
                    dp[next][j][OFF] = dp[cur][j][OFF];
                }
                for ( int j = 0; j < n; ++ j ) {
                    if ( j - 1 >= 0 )
                        dp[next][j-1][ON] += dp[cur][j][ON];
                    if ( j + 1 < n )
                        dp[next][j+1][ON] += dp[cur][j][ON];
                }
                dp_copy(next);
            }

            int sum = 0;
            for ( int i = 0; i < n; ++ i ) {
                cout << dp[get(m)][i][ON] << ", ";
                sum += dp[get(m)][i][ON];
            }
            cout << endl;
            cout << "sum = " << sum << endl;
            return -1;
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

