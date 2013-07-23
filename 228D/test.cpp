#include <iostream>
using namespace std;

int calc_zigzag_seq( int z, int i ) {
  int mod = i % ( 2 * ( z - 1 ) );
  if ( mod == 0 )
    return 2;
  if ( mod <= z )
    return mod;
  return 2 * z - mod;
}

int main() {
  for ( int z = 2; z <= 6; ++ z ) {
    for ( int i = 1; i <= 20; ++ i ) {
      cout << "S[" << i << "]^" << z << " = " << calc_zigzag_seq(z, i) << endl;
    }
  }
  return 0;
}
