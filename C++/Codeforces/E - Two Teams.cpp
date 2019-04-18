#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 201010
#define F first
#define S second
typedef long long int ll;

int main() {
  fast;
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  vector<int> ans(n, 0);
  priority_queue<pair<int, int> > pq;
  set<int> positions;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    pq.push({v[i], i});
    positions.insert(i);
  }

  int turn = 1;
  while(!pq.empty()) {
    int elem = pq.top().first;
    int pos = pq.top().second;
    pq.pop();
    
    if (positions.count(pos) == 0) continue;
    vector<int> to_erase;
    auto it = positions.find(pos);
    for (int i = 0; it != positions.end() && i < k + 1; i++) {
      to_erase.push_back(*it);
      it++;
    }

    auto it2 = positions.find(pos);
    if (it2 != positions.begin()) {
      it2 = prev(it2);
      for (int i = 0; i < k; i++) {
        to_erase.push_back(*it2);
        if (it2 == positions.begin()) break;
        it2--;
      }
    }
    
    for (int &x : to_erase) {
      positions.erase(x);
      ans[x] = turn;
    }

    turn = (turn == 1) ? 2 : 1;
  }

  for (int &x : ans) {
    cout << x;
  }
  cout << "\n";

  return 0;
}
