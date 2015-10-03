#include <bits/stdc++.h>
using namespace std;

const int N_MAX = 500 + 11;
int n;
int g[N_MAX * N_MAX];

bool input() {
  if (cin >> n) {
    for (int i = 0; i < n * n; ++i) cin >> g[i];
    return true;
  }
  return false;
}

typedef tuple<int, int> node_t; // x, n
typedef map<int, int, greater<int>> cnt_t;

int t[N_MAX][N_MAX];

int x(const node_t& n) {
  return get<0>(n);
}

int num(const node_t& n) {
  return get<1>(n);
}

int gcd(int a, int b)
{
  if (a == 0) return b;
  return gcd(b % a, a);
}

void solve() {
  for (int i = 0; i < n; ++i) fill(t[i], t[i] + n, -1);
  cnt_t cnt;
  for (int i = 0; i < n * n; ++i) ++cnt[g[i]];
  for (int i = 0; i < n; ++i) {
    auto& cur = t[i][i];
    cur = x(*cnt.begin());
    --cnt[cur];
    if (!cnt[cur]) cnt.erase(cur);
    for (int j = 0; j < i; ++j) {
      int gc = gcd(cur, t[j][j]);
      if (cnt[gc] >= 2) {
        cnt[gc] -= 2;
        if (!cnt[gc]) cnt.erase(cur);
      } else {
        assert(true);
      }
    }
  }
}

void output() {
  for (int i = 0; i < n; ++i) cout << t[i][i] << " ";
  cout << endl;
}

int main() {
  while (input()) {
    solve();
    output();
  }
  return 0;
}
