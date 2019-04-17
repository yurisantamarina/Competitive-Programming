#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010
typedef long long int ll;

string s;
int n;
bool memo_pal[MAXN][MAXN], dp_pal[MAXN][MAXN];
ll dp[MAXN][MAXN];
int acc_begin[MAXN][MAXN], acc_end[MAXN][MAXN];

bool pal(int i, int j) {
  if (i >= j) return true;
  if (memo_pal[i][j]) return dp_pal[i][j];
  memo_pal[i][j] = true;
  bool ans = false;
  if (s[i] == s[j]) {
    ans = pal(i + 1, j - 1);
  }
  return dp_pal[i][j] = ans;
}

void buildAcc() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j > 0) {
        acc_begin[i][j] += acc_begin[i][j - 1];
      }

      if (i > 0) {
        acc_end[j][i] += acc_end[j][i - 1];
      }
    }
  }
}

int main() {
  cin >> s;

  n = (int)s.size();
  
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (pal(i, j)) {
        acc_begin[i][j] = 1;
        acc_end[j][i] = 1;
      }
    }
  }

  buildAcc();

  ll ans = 0;
  for (int len = 1; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      if (len == 1) {
        dp[l][r] = 0;
      } else if (len == 2) {
        dp[l][r] = (s[l] == s[r]);
      } else {
        if (s[l] == s[r]) {
          dp[l][r] = dp[l + 1][r - 1] + 1 + (acc_end[r - 1][n - 1] - acc_end[r - 1][l]) + acc_begin[l + 1][r - 1];
        }
      }

      ans += dp[l][r];
    }
  }

  cout << ans << "\n";

  return 0;
}