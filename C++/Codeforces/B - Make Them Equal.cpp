#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 201010
#define F first
#define S second
typedef long long int ll;

int main() {
  vector<int> v;
  int n, x;
  cin >> n;
  set<int> s;
  for (int i = 0; i < n; i++) {
    cin >> x;
    s.insert(x);
  }

  int sz = (int)s.size();
  if (sz == 1) {
    cout << "0\n";
  } else if (sz == 2) {
    int dif = *s.rbegin() - *s.begin();
    if (dif & 1) {
      cout << dif << "\n";
    } else {
      cout << (dif / 2) << "\n";
    }
  } else if (sz == 3) {
    int dif1 = *next(s.begin()) - *s.begin();
    int dif2 = *s.rbegin() - *prev(prev(s.end()));
    if (dif1 == dif2) {
      cout << dif1 << "\n";
    } else {
      cout << "-1\n";
    }
  } else {
    cout << "-1\n";
  }

  return 0;
}
