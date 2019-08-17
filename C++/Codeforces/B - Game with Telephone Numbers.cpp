#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 301010
#define F first
#define S second
typedef long long int ll;

int main(){
  int n;
  string s;
  vector<int> eight;
  cin >> n;
  cin >> s;
  for (int i = 0; i < n; i++) {
    if (s[i] == '8') {
      eight.push_back(i);
    }
  }
  int e = (int)eight.size();
  int k = (n - 11) / 2;
  
  if (k >= e) {
    cout << "NO\n";
  } else {
    int me = eight[k] - k;
    if (me > k) {
      cout << "NO\n";
    } else {
      cout << "YES\n";
    }
  }

  return 0;
}