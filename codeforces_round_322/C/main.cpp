#include <bits/stdc++.h>
using namespace std;

const int N_MAX = 100000 + 11;

int n;
int k;
int a[N_MAX];

bool input() {
  if (cin >> n >> k) {
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    return true;
  }
  return false;
}

typedef tuple<int, int> node_t;
const int REAL = 1;
typedef priority_queue<node_t, vector<node_t>> queue_t;
typedef priority_queue<int, vector<int>, greater<int>> set_t;

queue_t q;

void push(const int x) {
  q.emplace(x % 10, x);
}

int solve() {
  for (int i = 0; i < n; ++i) push(a[i]);

  while (k) {
    auto node = q.top();
    auto x = get<REAL>(node);
    if (x % 10 == 0) break;
    q.pop();
    push(x + 1);
    --k;
  }

  set_t s;
  while (!q.empty()) {
    s.push(get<REAL>(q.top()));
    q.pop();
  }

  while (k >= 10) {
    auto x = s.top();
    s.pop();
    s.push(x + 10);
    k -= 10;
  }

  int res = 0;
  while (!s.empty()) {
    res += min(100, s.top()) / 10;
    s.pop();
  }
  return res;
}

int main() {
  while (input()) cout << solve() << endl;
  return 0;
}
