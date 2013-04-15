
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

    typedef set<string> Set;

    const int SIZE = 10;
    int n;
    int A[SIZE];
    Set S;
    bool ok[256];

    int to_int( string& n ) {
        ISS iss(n);
        int res;
        iss >> res;
        return res;
    }

    string to_string( int n ) {
        OSS oss;
        oss << n;
        return oss.str();
    }

    bool check_reverse( string s ) {
        cout << s << " => ";
        reverse(s.begin(), s.end());
        ISS iss(s);
        int a, b;
        iss >> a >> b;
        cout << a << ", " << b << endl;
        return a <= 255 && b <= 255;
    }

    void check( string a_, string b_ ) {
        int na = to_int(a_);
        int nb = to_int(b_);
        if ( na > 255 || nb > 255 )
            return;
        string sa = to_string(na);
        string sb = to_string(nb);
        if ( sa.size() > 3 || sb.size() > 3 )
            return;
        if ( sa[sa.size()-1] == '0' ) {
            if ( sa != "0" )
                return;
        }
        if ( sb[sb.size()-1] == '0' ) {
            if ( sb != "0" )
                return;
        }

        {
            string s = sa + '.' + sb;
            if ( check_reverse(sa + ' ' + sb) ) {
                string rs = s;
                reverse(rs.begin(), rs.end());
                cout << s << "." << rs << endl;
            }
        }
    }
    
    class Solution: public ISolution {
    public:

        void init() {
            S.clear();
            fill( ok, ok+256, false );
        }
        
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
            return true;
        }
        
        void solve() {
            for ( int i = 0; i < n; ++ i )
                ok[A[i]+'0'] = true;
            for ( char c1 = '0'; c1 <= '9'; ++ c1 ) {
                for ( char c2 = '0'; c2 <= '9'; ++ c2 ) {
                    for ( char c3 = '0'; c3 <= '9'; ++ c3 ) {
                        for ( char c4 = '0'; c4 <= '9'; ++ c4 ) {
                            for ( char c5 = '0'; c5 <= '9'; ++ c5 ) {
                                for ( char c6 = '0'; c6 <= '9'; ++ c6 ) {
                                    if ( ok[(int)c1] && ok[(int)c2] && ok[(int)c3] && ok[(int)c4] && ok[(int)c5] && ok[(int)c6] ) {
                                        string s;
                                        s += c1;
                                        s += c2;
                                        s += c3;
                                        s += c4;
                                        s += c5;
                                        s += c6;
                                        set <char> ss(s.begin(), s.end());
                                        if ( (int)ss.size() == n ) {
                                            for ( int i = 1; i <= 6; ++ i ) {
                                                string a1 = s.substr(0, i);
                                                string a2 = s.substr(i);
                                                check(a1, a2);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
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

