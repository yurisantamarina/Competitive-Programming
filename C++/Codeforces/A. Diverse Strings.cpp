#include <bits/stdc++.h>

using namespace std;

bool diverse(string& s) {
  vector<bool> seen(27, false);
  char min_letter = 'z', max_letter = 'a';
  for (char i : s) {
    int c = i - 'a';
    if (seen[c]) return false;
    seen[c] = true;
    min_letter = min(min_letter, i);
    max_letter = max(max_letter, i);
  }

  return (max_letter - min_letter + 1) == (int)s.size();
}

int main(){
  int n;
  cin >> n;
  
  string s;
  for (int i = 0; i < n; i++) {
    cin >> s;
    cout << (diverse(s) ? "Yes" : "No") << "\n";
  }

	return 0;
}