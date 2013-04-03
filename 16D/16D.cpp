
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

    const int NONE = -1;

    int get_number( istream& is ) {
        int res;
        string line;
        getline( is, line );
        ISS iss(line);
        if ( ! ( iss >> res ) )
            return NONE;
        return res;
    }

    string get_line( istream& is ) {
        string res;
        getline( is, res );
        return res;
    }

    void replace( string& s, char src, char dst ) {
        std::replace( s.begin(), s.end(), src, dst );
    }

    const int SIZE = 101;
    int n;
    string logs[SIZE];

    class Solution: public ISolution {
    public:

        bool input() {
            n = get_number(cin);
            if ( n == NONE )
                return false;
            for ( int i = 0; i < n; ++ i )
                logs[i] = get_line(cin);
            return true;
        }

        int get_date( string log ) {
            string T = "[].:";
            for ( string::iterator it_i = T.begin(); it_i != T.end(); ++ it_i )
                replace( log, *it_i, ' ' );
            ISS iss(log);
            int hh, mm;
            string type;
            iss >> hh >> mm >> type;
            if ( type == "a" && hh == 12 ) {
                return mm;
            } 
            int res = hh * 60 + mm;
            if ( type == "p" && hh != 12 ) {
                res += 12 * 60;
            }
            return res;
        }

        int solve() {
            int res = 1;
            int D[n];
            for ( int i = 0; i < n; ++ i )
                D[i] = get_date(logs[i]);
            int cur = 0;
            for ( int i = 0; i < n; ++ i ) {
                if ( D[i] < cur ) {
                    res ++;
                }
                cur = D[i];
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

