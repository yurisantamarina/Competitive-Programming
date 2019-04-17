#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

set<ll> dp[55][55];

ll solve(vector<ll> &v, int k) {
  int len = (int)v.size();
  if (len - 1 < k) return 0LL;

/*
  for (int i = 0; i <= k; i++) {
    dp[0][i] = (1LL << 17) - 1LL;
  }
*/
  for (int i = 0; i <= len; i++) {
    for (int j = 0; j <= k; j++) {
      dp[i][j].clear();
    }
  }

  vector<ll> acc(len);
  acc[0] = 0;
  for (int i = 1; i < len; i++) {
    acc[i] = acc[i - 1] + v[i];
    dp[i][1].insert(acc[i]);
  }

  for (int cuts = 2; cuts <= k; cuts++) {
    for (int i = 1; i < len; i++) {
      for (int j = 0; j < i; j++) {
        ll sum = (acc[i] - acc[j]);
        for (ll elem : dp[j][cuts - 1]) {
          dp[i][cuts].insert(elem & sum);
        }
      }
    }
  }

  return *dp[len - 1][k].rbegin();
}

int main() {
  int n;
  scanf("%d", &n);
  vector<ll> a(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
  }

  int q;
  scanf("%d", &q);

  vector<ll> v;
  int k, top;
  while (q--) {
    scanf("%d", &k);
    v.clear();
    v.push_back(0);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &top);
      if (top > 0) {
        v.push_back(a[i] * (ll)top);
      }
    }

    printf("%lld\n", solve(v, k));
  }

  return 0;
}