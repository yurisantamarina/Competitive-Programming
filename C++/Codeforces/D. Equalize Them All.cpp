#include <bits/stdc++.h>

using namespace std;
#define MAXN 201000

vector<vector<int> > process(int most_frequent, vector<int>& a) {
  vector<vector<int> > ans;
  int op = 0;

  for (int i = most_frequent + 1; i < (int)a.size(); i++) {
    if (a[i] == a[most_frequent]) continue;

    if (a[i] > a[most_frequent]) {
      op = 2;
    } else if (a[i] < a[most_frequent]) {
      op = 1;
    }
    ans.push_back({op, i, i - 1});
  }

  for (int i = most_frequent - 1; i >= 0; i--) {
    if (a[i] == a[most_frequent]) continue;
    if (a[i] > a[most_frequent]) {
      op = 2;
    } else if (a[i] < a[most_frequent]) {
      op = 1;
    }
    ans.push_back({op, i, i + 1});
  }

  return ans;
}

int main(){
  int n;
	cin >> n;
	vector<int> a(n), freq(MAXN, 0);

	for (int i = 0; i < n; i++) {
	  cin >> a[i];
		freq[a[i]]++;
	}

	int most_frequent = 0;
	for (int i = 1; i < n; i++) {
		if (freq[a[i]] > freq[a[most_frequent]]) {
			most_frequent = i;
		}
	}

  vector<vector<int> > ans = process(most_frequent, a);

  cout << (int)ans.size() << "\n";
  for (auto i : ans) {
    cout << i[0] << " " << i[1] + 1 << " " << i[2] + 1 << "\n";
  }

	return 0;
}