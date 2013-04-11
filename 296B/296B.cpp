
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
    int n;
    string s, w;
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            cin >> s >> w;
            return true;
        }

        int count() {
            return std::count(s.begin(), s.end(), '?') + std::count(w.begin(), w.end(), '?');
        }

        bool check_no_question() {
            return count() == 0;
        }

        bool check_valid() {
            for ( int i = 0; i < n; ++ i ) {
                for ( int j = 0; j < n; ++ j ) {
                    if ( i == j )
                        continue;
                    if ( s[i] < w[i] && s[j] > w[j] )
                        return true;
                }
            }
            return false;
        }

        int find_all() {
            int cnt = count();
            LL res = 1;
            for ( int i = 0; i < cnt; ++ i )
                res = ( res * 10 ) % MOD;
            return res % MOD;
        }

        // s[i] <= w[i]
        int find_comb_1() {
            LL sum = 1;
            for ( int i = 0; i < n; ++ i ) {
                if ( s[i] == '?' && w[i] == '?' ) {
                    int cnt = 0;
                    for ( int x = 0; x <= 9; ++ x ) {
                        for ( int y = x; y <= 9; ++ y ) {
                            cnt ++;
                        }
                    }
                    sum = ( sum * cnt ) % MOD;
                } else if ( s[i] == '?' ) {
                    sum = ( sum * ( w[i] - '0' + 1 ) ) % MOD;
                } else if ( w[i] == '?' ) {
                    sum = ( sum * ( 10 - ( s[i] - '0' ) ) ) % MOD;
                } else if ( s[i] > w[i] ) {
                    return 0;
                }
            }
            return sum % MOD;
        }

        // s[i] >= w[i]
        int find_comb_2() {
            LL sum = 1;
            for ( int i = 0; i < n; ++ i ) {
                if ( s[i] == '?' && w[i] == '?' ) {
                    int cnt = 0;
                    for ( int x = 0; x <= 9; ++ x ) {
                        for ( int y = 0; y <= x; ++ y ) {
                            cnt ++;
                        }
                    }
                    sum = ( sum * cnt ) % MOD;
                } else if ( s[i] == '?' ) {
                    sum = ( sum * ( 10 - ( w[i] - '0' ) ) ) % MOD;
                } else if ( w[i] == '?' ) {
                    sum = ( sum * ( s[i] - '0' + 1 ) ) % MOD;
                } else if ( s[i] < w[i] ) {
                    return 0;
                }
            }
            return sum % MOD;
        }

        // s[i] == w[i]
        int find_comb_3() {
            LL sum = 1;
            for ( int i = 0; i < n; ++ i ) {
                if ( s[i] == '?' && w[i] == '?' ) {
                    sum = ( sum * 10 ) % MOD;
                }
            }
            return sum % MOD;
        }
        
        int solve() {
            if ( n == 1 )
                return 0;
            if ( check_no_question() ) {
                return check_valid() ? 1 : 0;
            }
            LL total = find_all();
            LL bad1 = find_comb_1();
            LL bad2 = find_comb_2();
            LL bad3 = find_comb_3();
            LL res = ( total - bad1 + MOD ) % MOD;
            res = ( res - bad2 + MOD ) % MOD;
            if ( bad1 > 0 && bad2 > 0 )
                res = ( res + bad3 ) % MOD;
            return res % MOD;
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

