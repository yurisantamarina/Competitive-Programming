#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 201010
#define F first
#define S second
typedef long long int ll;

int main() {
  vector<int> v(4);
  for (int i = 0; i < 4; i++) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());
  cout << v[3] - v[0] << " " << v[3] - v[1] << " " << v[3] - v[2] << endl;

  return 0;
}
