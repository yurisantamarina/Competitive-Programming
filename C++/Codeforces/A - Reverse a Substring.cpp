#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 301010
#define F first
#define S second
typedef long long int ll;

int main(){
  int n;
  cin >> n;
  string s, a;
  cin >> s;
  a = s;
  sort(a.begin(), a.end());
  if (a == s) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    for (int i = 1; i < n; i++) {
      if (s[i - 1] > s[i]) {
        cout << i << " " << i + 1 << "\n";
        break;
      }
    }
  }

  return 0;
}