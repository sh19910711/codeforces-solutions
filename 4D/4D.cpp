
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
    const std::string OUTPUT_VECTOR_DELIMITER = " ";
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

    const int SIZE = 5011;
    int n, h, w;

    struct Info {
        int h;
        int w;
        int i;
        bool operator <( const Info& right ) const {
            return h * w < right.h * right.h;
        }
    };

    Info D[SIZE];

    int to_i( const int& k ) {
        return D[k].i + 1;
    }

    class Solution: public ISolution {
    public:
        bool input() {
            if ( ! ( cin >> n >> w >> h ) )
                return false;
            for ( int i = 0; i < n; ++ i ) {
                cin >> D[i].w >> D[i].h;
                D[i].i = i + 1;
            }
            return true;
        }

        void cut() {
            for ( int i = n - 1; i >= 0; -- i ) {
                if ( D[i].w < w || D[i].h < h ) {
                    copy( D+i+1, D+n, D );
                    n -= n - i + 1;
                    return;
                }
            }
        }

        void solve() {
            sort( D, D+n );
            cut();

            int dp[SIZE];
            fill( dp, dp+SIZE, 0 );

            int prev[SIZE];
            fill( prev, prev+SIZE, -1 );

            dp[0] = 1;
            for ( int i = 1; i < n; ++ i ) {
                for ( int j = 0; j < i; ++ j ) {
                    cout << D[i].w << ", " << D[i].h << " / " << D[j].w << ", " << D[j].h << endl; 
                    if ( D[i].w >= D[j].w || D[i].h >= D[j].h )
                        continue;
                    if ( dp[i] < dp[j] + 1 ) {
                        dp[i] = dp[j] + 1;
                        prev[i] = j;
                    }
                }
            }

            int k = max_element( dp, dp+n ) - dp;
            int O[SIZE];
            int OC = 0;
            while ( k != -1 ) {
                O[OC++] = k;
                k = prev[k];
            }
            transform( O, O+OC, O, to_i );
            reverse( O, O+OC );
            cout << OC << endl;
            cout << VI( O, O+OC ) << endl;
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



