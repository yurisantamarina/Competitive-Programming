#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 301010
#define F first
#define S second
typedef long long int ll;

int n;
vector<int> v;
long long dp[MAXN][3], x;

long long maxBeauty() {
  long long ans = 0LL;
  dp[0][0] = max((long long)v[0], 0LL);
  dp[0][1] = max((long long)v[0] * x, 0LL);
  dp[0][2] = LLONG_MIN;
  ans = max({dp[0][0], dp[0][1], dp[0][2]});
  for (int i = 1; i < n; i++) {
    long long at = v[i];
    dp[i][0] = max(dp[i - 1][0] + at, 0LL);
    dp[i][1] = max(max(dp[i - 1][0], dp[i - 1][1]) + at * x, 0LL);
    dp[i][2] = max(max(dp[i - 1][2], dp[i - 1][1]) + at, 0LL);
    ans = max({ans, dp[i][0], dp[i][1], dp[i][2]});
  }

  return ans;
}

int main(){
  fast;
  cin >> n >> x;
  v.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }

  cout << maxBeauty() << endl;

  return 0;
}