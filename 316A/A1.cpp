
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

    typedef long long LL;
    
    string s;
    
    bool is_alphabet( const char& c ) {
        return 'A' <= c && c <= 'Z';
    }
    
    LL get_permutations( int k ) {
        if ( k <= 0 )
            return 1;
        LL res = 1;
        LL tmp = 10;
        for ( int i = 0; i < k; ++ i ) {
            res *= tmp;
            tmp --;
        }
        return res;
    }
    
    LL get_permutations_leading_zero( int k ) {
        if ( k <= 0 )
            return 1;
        LL res = 1;
        LL tmp = 9;
        for ( int i = 0; i < k; ++ i ) {
            res *= tmp;
            tmp --;
        }
        return res;
    }
    
    bool has_leading_zero() {
        return s[0] == '0';
    }
    
    bool has_leading_alphabet() {
        return is_alphabet(s[0]);
    }
    
    bool has_leading_question() {
        return s[0] == '?';
    }
    
    LL get_pow( int n ) {
        if ( n <= 0 )
            return 1;
        LL res = 1;
        for ( int i = 0; i < n; ++ i )
            res *= 10;
        return res;
    }
    
    string solve() {
        bool used[26];
        fill(used, used + 26, false);
        for ( string::iterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
            if ( is_alphabet(*it_i) ) {
                int ind = *it_i - 'A';
                used[ind] = true;
            }
        }
        
        int alphabets = count(used, used + 26, true);
        int questions = count(s.begin(), s.end(), '?');
        
        if ( has_leading_zero() )
            return 0;
        LL a = get_permutations(alphabets);
        LL c = 1;
        if ( has_leading_alphabet() ) {
            a -= get_permutations_leading_zero(alphabets - 1);
        } else if ( has_leading_question() ) {
            c *= 9;
            questions --;
        }
        LL tmp =  a * c;
        OSS oss;
        oss << tmp;
        string res = oss.str();
        return res + string(questions, '0');
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            return cin >> s;
        }
        
        void output( string result ) {
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


