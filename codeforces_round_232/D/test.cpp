#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
  int cnt = 0;
  for ( int i = 0; i < 1000000000; ++ i ) {
    cnt += rand() % 1000000;
    cnt %= 10000000;
  }
  std::cout << cnt << std::endl;
  return 0;
}
