#include <bits/stdc++.h>

using namespace std;

int main(){
  int n;
  cin >> n;
  
  vector<int> even, odd;
  int x;
  for (int i = 0; i < n; i++) {
    cin >> x;
    if (x & 1) {
      odd.push_back(x);
    } else {
      even.push_back(x);
    }
  }

  if (abs((int)odd.size() - (int)even.size()) <= 1) {
    cout << "0\n";
  } else {
    sort(odd.rbegin(), odd.rend());
    sort(even.rbegin(), even.rend());

    int answer = 0;
    if ((int)odd.size() < (int)even.size()) {
      for (int i = (int)odd.size() + 1; i < (int)even.size(); i++) {
        answer += even[i];
      }
    } else {
      for (int i = (int)even.size() + 1; i < (int)odd.size(); i++) {
        answer += odd[i];
      }
    }
    cout << answer << "\n";
  }
  
  return 0;
}