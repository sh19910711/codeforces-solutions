
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

    typedef set<LL> Set;
    const int SIZE = 100011;
    int n, k;
    string S[SIZE];
    LL A[SIZE];

    LL convert_address( string s ) {
        replace(s.begin(), s.end(), '.', ' ');
        ISS iss(s);
        LL T[4];
        iss >> T[0] >> T[1] >> T[2] >> T[3];
        return ( T[0] << 8*3 ) + ( T[1] << 8*2 ) + ( T[2] << 8*1 ) + T[3];
    }

    string convert_address( LL a ) {
        LL T[4];
        T[0] = ( a >> 8*3LL ) & 0xFF;
        T[1] = ( a >> 8*2LL ) & 0xFF;
        T[2] = ( a >> 8*1LL ) & 0xFF;
        T[3] = a & 0xFF;
        OSS oss;
        oss << T[0] << "." << T[1] << "." << T[2] << "." << T[3];
        return oss.str();
    }

    bool check_mask( LL mask ) {
        Set S;
        for ( int i = 0; i < n; ++ i ) {
            S.insert(A[i]&mask);
        }
        return (int)S.size() == k;
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n >> k ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> S[i];
            return true;
        }
        
        string solve() {
            for ( int i = 0; i < n; ++ i ) {
                A[i] = convert_address(S[i]);
            }
            string res = "-1";
            LL mask = ( 1LL << 32 ) - 1;
            if ( check_mask(mask) ) {
                res = convert_address(mask);
            }
            for ( int i = 0; i < 31; ++ i ) {
                LL bi = 1LL << i;
                mask ^= bi;
                if ( check_mask(mask) ) {
                    res = convert_address(mask);
                }
            }
            return res;
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

