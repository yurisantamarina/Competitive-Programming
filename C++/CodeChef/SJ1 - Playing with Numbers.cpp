#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
vector<int> g[MAXN];
ll ans[MAXN], w[MAXN], m[MAXN];
stack<ll> stack_gcd;
int n;

bool leaf(int u) {
  return (int)g[u].size() == 1 && u != 1;
}

void dfs(int u, int parent) {
  stack_gcd.push(stack_gcd.empty() ? w[u] : __gcd(stack_gcd.top(), w[u]));
  if (leaf(u)) {
    ll gcd = __gcd(stack_gcd.top(), m[u]);
    ans[u] = (m[u] - 1) / gcd;
    ans[u] *= gcd;
  }

  for (int &v : g[u]) {
    if (v != parent) {
      dfs(v, u);
    }
  }

  stack_gcd.pop();
}

void reset() {
  for (int i = 0; i <= n; i++) {
    g[i].clear();
    ans[i] = 0;
  }
}

int main() {
  int tc, u, v;
  scanf("%d", &tc);
  while (tc--) {
    scanf("%d", &n);
    reset();
    for (int i = 0; i < n - 1; i++) {
      scanf("%d %d", &u, &v);
      g[u].push_back(v);
      g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
      scanf("%lld", &w[i]);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%lld", &m[i]);
    }

    dfs(1, 1);

    bool first = true;
    for (int i = 1; i <= n; i++) {
      if (leaf(i)) {
        if (!first) printf(" ");
        first = false;
        printf("%lld", ans[i]);
      }
    }
    printf("\n");
  }


  return 0;
}