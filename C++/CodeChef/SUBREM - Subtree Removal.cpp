#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN 101010
ll dp[MAXN];
int n, X, w[MAXN];
vector<int> g[MAXN];

void reset() {
  for (int i = 0; i <= n; i++) {
    dp[i] = -1;
    g[i].clear();
  }
}

void dfs(int u, int parent) {
  ll sum = 0;
  for (int &v : g[u]) {
    if (v != parent) {
      dfs(v, u);
      sum += dp[v];
    }
  }
  dp[u] = max(ll(-X), w[u] + sum);
}

int main() {
  int tc, u, v;
  scanf("%d", &tc);
  while (tc--) {
    scanf("%d %d", &n, &X);
    reset();
    for (int i = 1; i <= n; i++) {
      scanf("%d", &w[i]);
    }
    for (int i = 0; i < n - 1; i++) {
      scanf("%d %d", &u, &v);
      g[u].push_back(v);
      g[v].push_back(u);
    }

    dfs(1, 1);
    printf("%lld\n", dp[1]);
  }

  return 0;
}