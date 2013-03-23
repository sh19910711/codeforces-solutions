#include <iostream>
#include <algorithm>
using namespace std;

bool gen( int n ) {
    int P[n];
    for ( int i = 0; i < n; ++ i )
        P[i] = i;
    sort( P, P+n );
    do {
        bool ok = true;
        for ( int i = 0; i < n; ++ i ) {
            if ( P[P[i]] != n - i - 1 )
                ok = false;
        }
        if ( ok ) {
            for ( int i = 0; i < n; ++ i )
                cout << P[i]+1 << ", ";
            cout << endl;
            return true;
        }
    } while ( next_permutation( P, P+n ) );
    return false;
}

int main() {
    for ( int i = 1; i <= 8; ++ i ) {
        // cout << "n = " << i << endl;
        cout << "n = " << i << ": " << ( gen(i) ? "OK" : "NG" ) << endl;
    }
    return 0;
}

