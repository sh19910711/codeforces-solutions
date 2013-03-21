
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
    
    typedef set<int> Set;
    typedef map<int,int> Map;
    
    const int SIZE = 100011;
    int n;
    int A[SIZE];
    int B[SIZE];
    
    class Solution: public ISolution {
    public:
        bool input() {
            if ( ! ( cin >> n ) )
                return false;
            for ( int i = 0; i < n; ++ i )
                cin >> A[i] >> B[i];
            return true;
        }
        void solve() {
            int res = 0;
            Set SL( A, A+n );
            Set SR( B, B+n );
            VI L( SL.begin(), SL.end() );
            VI R( SR.begin(), SR.end() );
            Set used;
            Map L2R, R2L;
            for ( int i = 0; i < n; ++ i ) {
                L2R[A[i]] = B[i];
                R2L[B[i]] = A[i];
            }
            for ( VI::iterator it_i = L.begin(); it_i != L.end(); ++ it_i ) {
                if ( used.count(*it_i) )
                    continue;
                int l = *it_i, r = L2R[*it_i];
                VI::iterator begin = upper_bound( R.begin(), R.end(), l );
                int k = upper_bound( R.rbegin(), R.rend(), r, greater<int>() ) - R.rbegin();
                VI::iterator end = R.begin() + R.size() - k;
                for ( VI::iterator it_j = begin; it_j != end; ++ it_j ) {
                    if ( used.count(*it_j) )
                        continue;
                    int l2 = R2L[*it_j], r2 = *it_j;
                    if ( l < l2 && r2 < r ) {
                        res ++;
                        used.insert(l2);
                        used.insert(r2);
                    }
                }
            }
            cout << res << endl;
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


