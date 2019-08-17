#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 201010
#define F first
#define S second
typedef long long int ll;

int main() {
  fast;
  int n, B, A;
  cin >> n >> B >> A;
  int b = B;
  int a = A;

  int x;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> x;
    if (x == 0) {
      if (a > 0) {
        a--;
      } else if (b > 0) {
        b--;
      } else {
        cout << ans << "\n";
        return 0;
      }
    } else {
      if (a < A) {
        if (b > 0) {
          b--;
          a++;
        } else if (a > 0) {
          a--;
        } else {
          cout << ans << "\n";
          return 0;
        }
      } else {
        a--;
      }
    }

    ans++;
  }

  cout << ans << "\n";


  return 0;
}
