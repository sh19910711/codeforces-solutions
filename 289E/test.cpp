#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;


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


// @snippet<sh19910711/contest:misc/get_binary_string.cpp>
namespace misc {
    // @desc 2進表記した文字列を求める
    template <class T> std::string GetBinaryString( const T& v ) {
        std::ostringstream oss;
        for ( int i = 0; i < static_cast<int>(sizeof v) * 8; ++ i ) {
            int bi = ( v >> i ) & 1;
            oss << bi;
        }
        std::string res = oss.str();
        std::reverse( res.begin(), res.end() );
        return res;
    }
}

using namespace io;
using namespace misc;
typedef vector<int> VI;

VI P;
int n;

int f( VI P ) {
    int res = 0;
    for ( int i = 0; i < n; ++ i )
        res += i ^ P[i];
    return res;
}

void calc( int n__ ) {
    n = n__ + 1;
    P.resize(n);
    for ( int i = 0; i < n; ++ i )
        P[i] = i;
    sort(P.begin(), P.end());
    int maxf = 0;
    VI maxp;
    do {
        int ret = f(P);
        if ( ret > maxf ) {
            maxf = ret;
            maxp = P;
        }
    } while ( next_permutation(P.begin(), P.end()) );
    cout << maxf << endl;
    for ( int i = 0; i < n; ++ i ) {
        cout << GetBinaryString<int>(i) << " ^ " << GetBinaryString<int>(maxp[i]) << " = " << ( i ^ maxp[i] ) << endl;
    }
}

int main() {
    int a[20];
    a[0] = 0;
    for ( int i = 1; i < 11; ++ i ) {
        a[i] = a[i-1] + 2 * i;
        cout << "n = " << n << endl;
        calc(i);
    }
    return 0;
}



