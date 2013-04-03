#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
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

using namespace io;
typedef vector<int> VI;

const int n = 5;
const int k = 2;
int P[n];

bool check() {
    bool ok = false;
    for ( int i = 0; i < k; ++ i ) {
        if ( P[i] == 0 )
            ok |= true;
    }
    if ( ! ok )
        return false;
    for ( int i = k; i < n; ++ i )
        if ( P[i] == 0 )
            return false;
    if ( P[0] == 0 )
        return false;
    // cout << "OK: " << VI( P, P+n ) << endl;
    return true;
}

int rec( int x ) {
    if ( x >= n ) {
        return check() ? 1 : 0;
        for ( int i = k; i < n; ++ i ) {
            if ( P[i] == 0 )
                return 0;
        }
        if ( P[0] == 0 )
            return 0;
        cout << "OK: " << VI( P, P+n ) << endl;
        return 1;
    }
    int res = 0;
    for ( int i = 0; i < n; ++ i ) {
        P[x] = i;
        res += rec(x+1);
    }
    return res;
}

int solve() {
    return rec(0);
}

int solve2() {
    int res = 0;
    for ( int i = 0; i < n; ++ i )
        P[i] = i;
    sort( P, P+n );
    do {
        if ( check() )
            res ++;
    } while ( next_permutation( P, P+n ) );
    return res;
}

int main() {
    printf("n = %d, k = %d, solve = %d\n", n, k, solve());
    return 0;
}


