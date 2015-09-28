#include <bits/stdc++.h>
using namespace std;

typedef tuple<int, int> pos_t;

pos_t p[3];
int ind[3];
int s;
const int A = 0;
const int B = 0;
const int C = 0;
char t[200][200];

bool input() {
  if (cin >> get<0>(p[0]) >> get<1>(p[0])) {
    for (int i = 1; i < 3; ++i)
      cin >> get<0>(p[i]) >> get<1>(p[i]);
    return true;
  }
  return false;
}

inline int x(const pos_t& p) {
  return get<0>(p);
}

inline int y(const pos_t& p) {
  return get<1>(p);
}

void put1() {
  auto pa = p[ind[A]];
  auto pb = p[ind[B]];
  auto pc = p[ind[C]];
  for (int i = 0; i < y(pa); ++i) {
    for (int j = 0; j < x(pa); ++j) {
      t[i][j] = 'A';
    }
  }
}

bool ok() {
  auto pa = p[ind[A]];
  auto pb = p[ind[B]];
  auto pc = p[ind[C]];
  if (x(pa) == s &&
      y(pa) + y(pb) == s &&
      x(pa) == x(pb) + x(pc) &&
      y(pa) + y(pb) == y(pa) + y(pc) ) {
    put1();
    return true;
  }
  return false;
}

bool solve() {
  for (s = 1; s <= 200; ++s) {
    cout << "hello" << endl;
    for (int i = 0; i < 3; ++i) ind[i] = i;
    do {
      if (ok()) {
        return true;
      }
    } while(next_permutation(ind, ind + 3));
  }
  return false;
}

void output() {
  cout << s << endl;
  for (int i = 0; i < s; ++i) {
    for (int j = 0; j < s; ++j) {
      cout << t[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  for (int i = 0; i < 200; ++i) fill(t[i], t[i] + 200, 'X');
  while (input()) {
    if (solve()) {
      output();
    } else {
      cout << "none" << endl;
    }
  }
  return 0;
}
