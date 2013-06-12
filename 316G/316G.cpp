
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

    typedef unsigned long long ULL;

    const int SIZE = 2000 + 11;
    const int HASH_BASE_1 = 131;
    const int HASH_BASE_2 = 149;
    string s;
    int n;
    string P[SIZE];
    int L[SIZE], R[SIZE];

    ULL base_1[SIZE];
    ULL base_2[SIZE];
    ULL hash_1[SIZE];
    ULL hash_2[SIZE];

    void calc_base() {
        base_1[0] = 1;
        for ( int i = 0; i + 1 < (int)s.size(); ++ i ) {
            base_1[i+1] = base_1[i] * HASH_BASE_1;
        }
        base_2[0] = 1;
        for ( int i = 0; i + 1 < (int)s.size(); ++ i ) {
            base_2[i+1] = base_2[i] * HASH_BASE_2;
        }
    }

    void calc_hash_s() {
        hash_1[0] = 0;
        for ( int i = 0; i < (int)s.size(); ++ i ) {
            hash_1[i+1] = hash_1[i] + ( ( s[i] - 'a' + 1 ) * base_1[i] );
        }
        hash_2[0] = 0;
        for ( int i = 0; i < (int)s.size(); ++ i ) {
            hash_2[i+1] = hash_2[i] + ( ( s[i] - 'a' + 1 ) * base_2[i] );
        }
    }

    void calc_hash_w() {
        hash_1[0] = 0;
        for ( int i = 0; i < (int)s.size(); ++ i ) {
            hash_1[i+1] = hash_1[i] + ( ( s[i] - 'a' + 1 ) * base_1[i] );
        }
        hash_2[0] = 0;
        for ( int i = 0; i < (int)s.size(); ++ i ) {
            hash_2[i+1] = hash_2[i] + ( ( s[i] - 'a' + 1 ) * base_2[i] );
        }
    }
    
    int search( const string& t ) {
        int slen = s.size();
        int tlen = t.size();
        int cnt = 0;
        for ( int i = 0; i + tlen - 1 < slen; ++ i ) {
            if ( s[i] == t[0] ) {
                if ( hash_1[i + tlen - 1] - hash_1[i] == hash_1[NW-1] * base_1[i] ) {
                    if ( hash_2[i + tlen - 1] - hash_2[i] == hash_2[NW-1] * base_2[i] ) {
                        cnt ++;
                    }
                }
            }
        }
        return cnt;
    }

    bool check( const string& t, int k ) {
        return L[k] <= search() && search() <= R[k];
    }

    bool check( const string& t ) {
        for ( int i = 0; i < n; ++ i )
            if ( ! check(t, i) )
                return false;
        return true;
    }

    int solve() {
        set<string> res;
        int len = s.size();
        for ( int i = 0; i < len; ++ i ) {
            for ( int j = i; j < len; ++ j ) {
                int sublen = j - i + 1;
                string t = s.substr(i, sublen);
                if ( check(t) )
                    res.insert(t);
            }
        }
        return res.size();
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> s >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> P[i] >> L[i] >> R[i];
            return true;
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

