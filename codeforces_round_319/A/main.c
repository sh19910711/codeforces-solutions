#include <stdio.h>

int main() {
  int n, x;
  scanf("%d%d", &n, &x);

  int i;
  int cnt = 0;

  for (i = 1; i <= n; ++i) {
    if (x % i == 0 && x / i <= n) {
      cnt ++;
    }
  }

  printf("%d\n", cnt);
  return 0;
}

