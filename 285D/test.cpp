#include <iostream>
#include <algorithm>
using namespace std;

int bruteforce( int n ) {
    int res = 0;
    int A[n];
    for ( int i = 0; i < n; ++ i )
        A[i] = i + 1;
    int B[n];
    for ( int i = 0; i < n; ++ i )
        B[i] = i + 1;
    sort( A, A+n );
    do {
        sort( B, B+n );
        do {
            int C[n];
            for ( int i = 0; i < n; ++ i ) {
                C[i] = ( A[i] - 1 + B[i] - 1 ) % n + 1;
            }
            sort( C, C+n );
            bool ok = true;
            for ( int i = 0; i < n; ++ i ) {
                if ( C[i] != i+1 )
                    ok = false;
            }
            if ( ok ) {
                res ++;
                for ( int i = 0; i < n; ++ i )
                    C[i] = ( A[i] - 1 + B[i] - 1 ) % n + 1;
                for ( int i = 0; i < n; ++ i )
                    cout << A[i] << ", ";
                cout << endl;
                for ( int i = 0; i < n; ++ i )
                    cout << B[i] << ", ";
                cout << endl;
                for ( int i = 0; i < n; ++ i )
                    cout << C[i] << ", ";
                cout << endl;
                cout << " -- " << endl;
            }
        } while ( next_permutation( B, B+n ) );
    } while ( next_permutation( A, A+n ) );
    return res;
}
int main() {
    bruteforce(5);
    return 0;
    for ( int i = 1; i <= 7; i += 1 )
        cout << i << ": " << bruteforce(i) << endl;
    return 0;
}
