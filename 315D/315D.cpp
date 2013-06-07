
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

    const int NONE = -1;

    int b, d;
    string a, c;

    string get_repeated( const string& s, int k ) {
        VS v(k, s);
        return accumulate(v.begin(), v.end(), string());
    }

    int find_subseq( const string& a, const string& b ) {
        int na = a.size(), nb = b.size();
        for ( int i = 0, j = 0; i < na && j < nb; ++ i ) {
            if ( a[i] == b[j] ) {
                j ++;
                if ( j >= nb )
                    return i + 1;
            }
        }
        return NONE;
    }

    string cut( const string& a, const string& b ) {
        bool ok[26];
        fill(ok, ok + 26, false);
        for ( string::const_iterator it_i = b.begin(); it_i != b.end(); ++ it_i )
            ok[(*it_i) - 'a'] = true;
        string res;
        for ( string::const_iterator it_i = a.begin(); it_i != a.end(); ++ it_i ) {
            if ( ok[(*it_i) - 'a'] )
                res += *it_i;
        }
        return res;
    }

    LL solve() {
        a = cut(a, c);
        if ( a == "" )
            return 0;
        int min_len = NONE;
        for ( int i = 1; i <= 200; ++ i ) {
            string aa = get_repeated(a, i);
            int ret = find_subseq(aa, c);
            if ( ret != NONE ) {
                min_len = ret;
                break;
            }
        }
        if ( min_len == NONE || (LL)a.size() * b < min_len )
            return 0;
        LL ta = a.size() * b;
        return ta / d;
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> b >> d >> a >> c;
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

