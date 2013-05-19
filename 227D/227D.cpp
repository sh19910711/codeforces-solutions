
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

    const int A_SIZE = 100000 + 11;
    const int B_SIZE = 100000 + 11;

    int n;
    int A[A_SIZE];
    int q;
    int B[B_SIZE];
    LL S[A_SIZE];

    LL one_res;
    LL query_one() {
        return one_res;
    }

    LL query( int k ) {
        if ( k == 1 ) {
            return query_one();
        }
        LL res = 0;
        LL p = k;
        LL d = 1;
        LL rem = n;
        int offset = 0;

        while ( rem > 0 ) {
            int l = min(rem, p);
            LL sum = S[offset + l - 1] - ( offset == 0 ? 0 : S[offset - 1] );
            res += d * sum;
            rem -= l;
            p *= k;
            d += 1;
            offset += l;
        }
        return res;
    }

    void solve() {
        sort(A, A + n, greater<int>());
        copy(A + 1, A + n, A);
        n --;

        one_res = 0;
        for ( int i = 0; i < n; ++ i )
            one_res += (LL)( i + 1 ) * A[i];

        S[0] = A[0];
        for ( int i = 1; i < n; ++ i )
            S[i] = S[i - 1] + A[i];
        
        for ( int i = 0; i < q; ++ i ) {
            cout << query(B[i]) << " ";
        }
        cout << endl;
    }
    
    class Solution: public ISolution {
    public:
        
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i];
            cin >> q;
            for ( int i = 0; i < q; ++ i )
                cin >> B[i];
            return true;
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

