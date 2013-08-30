#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  for ( int SIZE = 1; SIZE < 10; ++ SIZE ) {
    std::cout << "SIZE = " << SIZE << std::endl;
    int A[SIZE];
    for ( int i = 0; i < SIZE; ++ i )
      A[i] = i + 1;
    int cnt = 0;
    do {
      for ( int i = 0; i + 1 < SIZE; ++ i ) {
        if ( A[i] == 2 && A[i+1] == 3 )
          cnt ++;
        if ( A[i] == 3 && A[i+1] == 2 )
          cnt ++;
      }
    } while ( std::next_permutation(A, A + SIZE) );
    std::cout << "SIZE = " << SIZE << " / " << "cnt = " << cnt << std::endl;
  } 
  return 0;
}

