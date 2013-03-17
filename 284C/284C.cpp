
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

// @snippet<sh19910711/contest:io/config.cpp>
namespace io {
    const std::string OUTPUT_VECTOR_DELIMITER = ",";
}

// @snippet<sh19910711/contest:io/vector.cpp>
namespace io {
    template <typename T> std::ostream& operator <<( std::ostream& os, const std::vector<T>& v ) {
        typedef typename std::vector<T>::const_iterator Iterator;
        for ( Iterator it_i = v.begin(); it_i != v.end(); ++ it_i ) {
            os << *it_i;
            if ( it_i + 1 != v.end() )
                os << OUTPUT_VECTOR_DELIMITER;
        }
        return os;
    }
    template <typename T> std::istream& operator >>( std::istream& is, std::vector<T>& v ) {
        int n = v.size();
        for ( int i = 0; i < n; ++ i ) {
            is >> v[i];
        }
        return is;
    }
}


// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;
    using namespace io;
    
    const int SIZE = 200011;
    int n;
    LL B[SIZE];
    LL BS;
    LL S[SIZE];
    int SC;
    LL SS;
    
    LL sum( int k ) {
        LL sum = 0;
        while ( k > 0 ) {
            sum += B[k];
            k -= k & -k;
        }
        return sum;
    }
    
    void add( int k, int x ) {
        while ( k <= n ) {
            B[k] += x;
            k += k & -k;
        }
    }
    
    class Solution: public ISolution {
    public:
        void init() {
            SC = 1;
            SS = 0;
            BS = 0;
            fill( B, B+SIZE, 0 );
        }
        bool input() {
            return cin >> n;
        }
        long double query() {
            int t;
            cin >> t;
            if ( t == 1 ) {
                int a, x;
                cin >> a >> x;
                add( a, x );
                BS += x * a;
            } else if ( t == 2 ) { // 追加
                int k;
                cin >> k;
                B[SC] = 0;
                S[SC++] = k;
                SS += k;
            } else if ( t == 3 ) { // 削除
                SS -= S[SC-1];
                LL tmp = sum(SC-1) - sum(SC-2);
                BS -= tmp;
                add( SC - 1, -tmp );
                B[SC-1] = 0;
                SC --;
            }
            
            LL a = SS + BS;
            LL b = SC - 1;
            return (long double)a / (long double)b;
        }
        void solve() {
            B[0] = 0;
            B[1] = 0;
            S[SC++] = 0;
            for ( int i = 0; i < n; ++ i ) {
                cout << setprecision(9) << query() << endl;
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



