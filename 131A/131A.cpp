
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
    string s;

    bool is_upper( const char& c ) {
        return 'A' <= c && c <= 'Z';
    }

    bool has_only_uppers( const string& s ) {
        int n = s.size();
        for ( int i = 0; i < n; ++ i )
            if ( ! is_upper(s[i]) )
                return false;
        return true;
    }

    bool has_first_lowers( const string& s ) {
        int n = s.size();
        if ( is_upper(s[0]) )
            return false;
        for ( int i = 1; i < n; ++ i )
            if ( ! is_upper(s[i]) )
                return false;
        return true;
    }

    bool check( const string& s ) {
        return has_only_uppers(s) || has_first_lowers(s);
    }

    char convert( const char& c ) {
        if ( is_upper(c) )
            return ::tolower(c);
        return ::toupper(c);
    }

    string convert( const string& s ) {
        string res = s;
        int n = s.size();
        for ( int i = 0; i < n; ++ i )
            res[i] = convert(s[i]);
        return res;
    }

    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> s;
        }
        string solve() {
            if ( check(s) )
                s = convert(s);
            return s;
        }
        void output( const string& result ) {
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

