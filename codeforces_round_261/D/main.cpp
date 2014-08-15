#include <iostream>
#include <set>
#include <map>
using namespace std;

typedef long long Int;

const Int N_MAX = 1000000 + 11;

Int N;
Int A[N_MAX];

bool input() {
  if ( cin >> N && N ) {
    for ( int i = 0; i < N; ++ i ) cin >> A[i];
    return true;
  }
  return false;
}

typedef map<Int, Int> IntMap;
typedef multiset<Int, greater<Int>> IntSet;
IntMap L;
IntMap R;
IntSet S;

void init() {
  L.clear();
  R.clear();
  S.clear();
}

Int solve() {
  IntMap cnt;
  cnt.clear(); for ( int i = 0; i < N; ++ i ) L[i] = ++ cnt[A[i]];
  cnt.clear(); for ( int i = N - 1; i >= 0; -- i ) R[i] = ++ cnt[A[i]];
  // for ( int i = 0; i < N; ++ i ) cout << i << ", " << A[i] << ": " << L[i] << endl;
  // for ( int i = 0; i < N; ++ i ) cout << i << ", " << A[i] << ": " << R[i] << endl;
  
  Int res = 0;
  for ( int i = N - 1; i >= 0; -- i ) {
    const auto& it = S.lower_bound(L[i]);

    cout << "i = " << i << ": a = " << A[i] << " / l = " << L[i] << ", r = " << R[i];
    if ( it != S.end() ) cout << ": dist = " << distance(S.begin(), it);
    cout << endl;

    if ( it != S.end() ) {
      res += distance(S.begin(), it);
    }
    S.insert(R[i]);
  }
  return res;
}

int main() {
  while ( input() ) {
    init();
    cout << solve() << endl;
  }
  return 0;
}
