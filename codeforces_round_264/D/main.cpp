#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

typedef long long Int;
const Int N_MAX = 1000 + 11;
const Int K_MAX = 5 + 1;

Int N, K;
Int A[K_MAX][N_MAX];

bool input() {
  if ( cin >> N >> K ) {
    for ( int i = 0; i < K; ++ i ) {
      for ( int j = 0; j < N; ++ j ) {
        cin >> A[i][j];
      }
    }
    return true;
  }
  return false;
}

typedef set<Int> IntSet;
Int pos[K_MAX][N_MAX];
Int dp[N_MAX];

void init() {
  fill(dp, dp + N_MAX, 0);
}

bool check_pos( const Int& x, const Int& y ) {
  for ( int i = 0; i < K; ++ i ) {
    if ( pos[i][x] < pos[i][y] ) return false;
  }
  return true;
}

Int solve() {
  for ( int i = 0; i < K; ++ i ) {
    for ( int j = 0; j < N; ++ j ) {
      const auto& x = A[i][j];
      pos[i][x] = j;
    }
  }

  Int res = 0;
  for ( int i = 0; i < N; ++ i ) {
    const auto& x = A[0][i];
    dp[x] = 1;
    for ( int j = 1; j <= N; ++ j ) {
      if ( x != j && check_pos(x, j) ) dp[x] = max(dp[x], dp[j] + 1);
    }
  }
  for ( int i = 1; i <= N; ++ i ) {
    // cout << i << ": " << dp[i] << endl;
  }
  return *max_element(dp + 1, dp + N + 1);
}

int main() {
  while ( input() ) {
    cout << solve() << endl;
  }
  return 0;
}
