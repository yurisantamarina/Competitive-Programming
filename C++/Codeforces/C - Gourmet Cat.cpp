#include <bits/stdc++.h>

using namespace std;
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define MAXN 201010
#define F first
#define S second
typedef long long int ll;
deque<int> v{0, 0, 1, 2, 0, 2, 1};
vector<int> food;

long long calcDays() {
  vector<int> food_left = food;
  vector<int> has(3, 0);

  for (int i = 0; i < 7; i++) {
    if (food_left[v[i]] == 0) return i;
    food_left[v[i]]--;
    has[v[i]]++;
  }

  int min_cycle = INT_MAX;
  for (int i = 0; i < 3; i++) {
    min_cycle = min(min_cycle, food_left[i] / has[i]);
  }

  long long days = 7 + min_cycle * 7;
  for (int i = 0; i < 3; i++) {
    food_left[i] -= min_cycle * has[i];
  }

  for (int i = 0; i < 7; i++) {
    if (food_left[v[i]] == 0) return days;
    food_left[v[i]]--;
    days++;
  }
  for (int i = 0; i < 7; i++) {
    if (food_left[v[i]] == 0) return days;
    food_left[v[i]]--;
    days++;
  }
  return days;
}

int main() {
  food.resize(3);
  cin >> food[0] >> food[1] >> food[2];
  long long ans = 0;
  for (int i = 0; i < 7; i++) {
    int a = v[0];
    v.pop_front();
    v.push_back(a);

    ans = max(ans, calcDays());
  }
  cout << ans << "\n";


  return 0;
}
