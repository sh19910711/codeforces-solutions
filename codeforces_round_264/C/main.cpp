#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

typedef long long Int;
const int N_MAX = 2000 + 11;

int N;
Int T[N_MAX][N_MAX];

bool input() {
  if ( cin >> N ) {
    for ( int i = 0; i < N; ++ i ) {
      for ( int j = 0; j < N; ++ j ) {
        cin >> T[i][j];
      }
    }
    return true;
  }
  return false;
}

typedef tuple<Int, Int, Int> Node;
typedef priority_queue<Node, vector<Node>, less<Node>> Queue;

Int S_up[2 * N_MAX];
Int L_up[N_MAX][N_MAX];
Int S_down[2 * N_MAX];
Int L_down[N_MAX][N_MAX];
Int res_s;
Int res_r[2], res_c[2];

void init() {
  res_s = -1;
  fill(S_up, S_up + 2 * N_MAX, 0);
  fill(S_down, S_down+ 2 * N_MAX, 0);
}

Int get_sum( int r, int c ) {
  // cout << "@get_sum: " << r << ", " << c << " / " << S_up[L_up[r][c]] << " + " << S_down[L_down[r][c]] << " - " << T[r][c] << " = " << S_up[L_up[r][c]] + S_down[L_down[r][c]] - T[r][c] << endl;
  return S_up[L_up[r][c]] + S_down[L_down[r][c]] - T[r][c];
}

void gen() {
  for ( int i = 0; i < N; ++ i ) {
    int r = i;
    int c = 0;
    for ( int j = 0; j < N && r >= 0 && c < N; ++ j ) {
      L_up[r][c] = i;
      S_up[i] += T[r][c];
      r --;
      c ++;
    }
  }
  for ( int i = 1; i < N; ++ i ) {
    int r = N - 1;
    int c = i;
    for ( int j = 0; j < N && r >= 0 && c < N; ++ j ) {
      // cout << N - 1 + i << ": " << r << ", " << c << endl;
      L_up[r][c] = N - 1 + i;
      S_up[N - 1 + i] += T[r][c];
      r --;
      c ++;
    }
  }
  for ( int i = 0; i < N; ++ i ) {
    int r = i;
    int c = 0;
    for ( int j = 0; j < N && r < N && c < N; ++ j ) {
      L_down[r][c] = i;
      S_down[i] += T[r][c];
      r ++;
      c ++;
    }
  }
  for ( int i = 1; i < N; ++ i ) {
    int r = 0;
    int c = i;
    for ( int j = 0; j < N && r < N && c < N; ++ j ) {
      L_down[r][c] = N - 1 + i;
      S_down[N - 1 + i] += T[r][c];
      r ++;
      c ++;
    }
  }
}

bool same( int r1, int c1, int r2, int c2 ) {
  return L_down[r1][c1] == L_down[r2][c2] || L_up[r1][c1] == L_up[r2][c2];
}

void solve() {
  gen();

  mt19937 mt(51234);
  for ( int i = 0; i < 50000000; ++ i ) {
    int r1 = mt() % N;
    int c1 = mt() % N;
    int r2 = mt() % N;
    int c2 = mt() % N;
    if ( same(r1, c1, r2, c2) ) continue;
    Int sum = get_sum(r1, c1) + get_sum(r2, c2);
    if ( sum > res_s ) {
      res_s = sum;
      res_r[0] = r1 + 1;
      res_c[0] = c1 + 1;
      res_r[1] = r2 + 1;
      res_c[1] = c2 + 1;
    }
  }

  return;
  Queue Q;
  for ( int i = 0; i < N; ++ i ) {
    for ( int j = 0; j < N; ++ j ) {
      // cout << get_sum(i, j) << " ";
      Q.emplace(get_sum(i, j), i, j);
    }
    // cout << endl;
  }
  for ( int i = 0; i < 15000 && i < N * N; ++ i ) {
    const auto& node = Q.top(); Q.pop();
    const auto& s = get<0>(node);
    const auto& r = get<1>(node);
    const auto& c = get<2>(node);
    // cout << r << ", " << c << ": " << s << endl;
    for ( int i = 0; i < N; ++ i ) {
      for ( int j = 0; j < N; ++ j ) {
        if ( L_down[r][c] == L_down[i][j] ) continue;
        if ( L_up[r][c] == L_up[i][j] ) continue;
        Int sum = s + get_sum(i, j);
        if ( sum > res_s ) {
          res_s = sum;
          res_r[0] = r + 1;
          res_c[0] = c + 1;
          res_r[1] = i + 1;
          res_c[1] = j + 1;
        }
      }
    }
  }
  // cout << endl;
}

void output() {
  cout << res_s << endl;
  for ( int i = 0; i < 2; ++ i ) {
    cout << res_r[i] << " " << res_c[i] << endl;
  }
}

int main() {
  while ( input() ) {
    init();
    solve();
    output();
  }
  return 0;
}
