
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

    const int SIZE = 101;
    const int NONE = -1;
    
    int n;
    string A[SIZE];
    string B[SIZE];

    int get_number() {
        string line;
        getline(cin, line);
        ISS iss(line);
        int res;
        if ( ! ( iss >> res ) )
            return NONE;
        return res;
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            n = get_number();
            if ( n == NONE )
                return false;
            for ( int i = 0; i < n; ++ i ) {
                string line;
                getline( cin, line );
                ISS iss(line);
                iss >> A[i] >> B[i];
            }
            return true;
        }

        void print_directory( VS D ) {
            cout << "/";
            for ( VS::iterator it_i = D.begin(); it_i != D.end(); ++ it_i ) {
                cout << *it_i;
                cout << "/";
            }
            cout << endl;
        }

        bool is_absolute_path( string s ) {
            return s[0] == '/';
        }

        VS get_path( string s ) {
            VS res;
            replace( s.begin(), s.end(), '/', ' ' );
            string token;
            ISS iss(s);
            while ( iss >> token )
                res.push_back(token);
            return res;
        }
        
        void solve() {
            VS D;
            for ( int i = 0; i < n; ++ i ) {
                if ( A[i] == "pwd" ) {
                    print_directory(D);
                } else {
                    if ( is_absolute_path(B[i]) ) {
                        D.clear();
                        VS path = get_path(B[i]);
                        for ( VS::iterator it_i = path.begin(); it_i != path.end(); ++ it_i ) {
                            string& s = *it_i;
                            if ( s == "." ) {
                            } else if ( s == ".." ) {
                                D.pop_back();
                            } else {
                                D.push_back(s);
                            }
                        }
                    } else {
                        VS path = get_path(B[i]);
                        for ( VS::iterator it_i = path.begin(); it_i != path.end(); ++ it_i ) {
                            string& s = *it_i;
                            if ( s == "." ) {
                            } else if ( s == ".." ) {
                                D.pop_back();
                            } else {
                                D.push_back(s);
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

