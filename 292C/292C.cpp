
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
    bool rok[256];
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

    bool check( string a1, string a2, string a3, string a4 ) {
        int na1 = to_int(a1);
        if ( na1 > 255 )
            return false;
        int na2 = to_int(a2);
        if ( na2 > 255 )
            return false;
        int na3 = to_int(a3);
        if ( na3 > 255 )
            return false;
        int na4 = to_int(a4);
        if ( na4 > 255 )
            return false;
        string sa1 = to_string(na1);
        string sa2 = to_string(na2);
        string sa3 = to_string(na3);
        string sa4 = to_string(na4);
        if ( sa1.size() || sa2.size() || sa3.size() || sa4.size() )
            continue;
        string l = sa1 + sa2;
        string r = sa3 + sa4;
        cout << l << " / " << r << endl;
        reverse(r.begin(), r.end());
        cout << l << "." << r << endl;
        if ( l != r )
            return false;
        string s = l + r;
        int n = s.size();
        for ( int i = 0; i < n; ++ i )
            if ( ! rok[(int)s[i]] )
                return false;
        return true;
    }

    void check( string s ) {
        string rs = s;
        reverse( rs.begin(), rs.end() );
        int n = s.size(), m = rs.size();
        for ( int i = 1; i < n; ++ i ) {
            for ( int j = 1; j < m; ++ j ) {
                string a1 = s.substr(0, i);
                string a2 = s.substr(i);
                string a3 = rs.substr(0, j);
                string a4 = rs.substr(j);
                if ( check( a1, a2, a3, a4 ) ) {
                    string sa1 = to_string(to_int(a1));
                    string sa2 = to_string(to_int(a2));
                    string sa3 = to_string(to_int(a3));
                    string sa4 = to_string(to_int(a4));
                    S.insert(sa1+'.'+sa2+'.'+sa3+'.'+sa4);
                }
            }
        }
        string rs2 = s;
        reverse( rs2.begin(), rs2.end() );
        rs2 = rs2.substr(1);
        int n2 = s.size(), m2 = rs2.size();
        for ( int i = 1; i < n2; ++ i ) {
            for ( int j = 1; j < m2; ++ j ) {
                string a1 = s.substr(0, i);
                string a2 = s.substr(i);
                string a3 = rs2.substr(0, j);
                string a4 = rs2.substr(j);
                if ( check( a1, a2, a3, a4 ) ) {
                    string sa1 = to_string(to_int(a1));
                    string sa2 = to_string(to_int(a2));
                    string sa3 = to_string(to_int(a3));
                    string sa4 = to_string(to_int(a4));
                    S.insert(sa1+'.'+sa2+'.'+sa3+'.'+sa4);
                }
            }
        }
        string rs3 = s;
        reverse( rs3.begin(), rs3.end() );
        rs3 = "0" + rs3;
        for ( char c = '0'; c <= '9'; ++ c ) {
            if ( rok[(int)c] == false )
                continue;
            rs3[0] = c;
            int n3 = s.size(), m3 = rs3.size();
            for ( int i = 1; i < n3; ++ i ) {
                for ( int j = 1; j < m3; ++ j ) {
                    string a1 = s.substr(0, i);
                    string a2 = s.substr(i);
                    string a3 = rs3.substr(0, j);
                    string a4 = rs3.substr(j);
                    if ( check( a1, a2, a3, a4 ) ) {
                        string sa1 = to_string(to_int(a1));
                        string sa2 = to_string(to_int(a2));
                        string sa3 = to_string(to_int(a3));
                        string sa4 = to_string(to_int(a4));
                        S.insert(sa1+'.'+sa2+'.'+sa3+'.'+sa4);
                    }
                }
            }
        }
    }
    
    class Solution: public ISolution {
    public:

        void init() {
            S.clear();
            fill( ok, ok+256, false );
            fill( rok, rok+256, false );
        }
        
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
            return true;
        }
        
        void solve() {
            for ( int i = 0; i < n; ++ i ) {
                rok[A[i]+'0'] = true;
                ok[A[i]+'0'] = true;
            }
            if ( ok['0'] == false ) {
                ok['0'] = true;
                n ++;
            }
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
                                            check(s);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        void output() {
            cout << S.size() << endl;
            for ( Set::iterator it_i = S.begin(); it_i != S.end(); ++ it_i ) {
                cout << *it_i << endl;
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

