#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

typedef unsigned long long Hash;
const int SIZE = 3 * 100000 + 11;

Hash h(const string& s) {
  Hash res;
  for ( auto c : s ) {
    res = res * 257 + c;
  }
  return res;
}

int str_sum(const string& s) {
  int res;
  for ( auto c : s ) {
    res += c - 'a' + 1;
  }
  return res;
}

int n, m;
string q[SIZE];
string s[SIZE];
set<int> sum;

string solve(string query) {
}

int main() {
  cin >> n >> m;
  for ( int i = 0; i < n; ++ i ) {
    cin >> s[i];
  }
  for ( int i = 0; i < m; ++ i ) {
    cin >> q[i];
  }
  for ( int i = 0; i < n; ++ i ) {
    cout << s[i] << ": " << str_sum(s[i]) << endl;
    sum.insert(str_sum(s[i]));
  }
  for ( int i = 0; i < m; ++ i ) {
    int qsum = str_sum(q[i]);
    cout << q[i] << ": " << qsum << endl;
    if ( sum.count(qsum-1) || sum.count(qsum+1) ) {
      cout << "YES?" << endl;
    } else {
    }
  }
  return 0;
}
