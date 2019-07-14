#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	vector<int> sequence = {4, 8, 15, 16, 23, 42};
	unordered_map<int, int> position = {{4, 0}, {8, 1}, {15, 2}, {16, 3}, {23, 4}, {42, 5}};
	unordered_map<int, int> available = {{4, 0}, {8, 0}, {15, 0}, {16, 0}, {23, 0}, {42, 0}};
	cin >> n;
	int number;
	for (int i = 0; i < n; i++) {
		cin >> number;
		if (number == 4) {
			available[number]++;
		} else {
			if (available[sequence[position[number] - 1]] > 0) { // previous element
				available[sequence[position[number] - 1]]--;
				available[number]++;
			}
		}
	}
	cout << n - (available[42] * 6) << endl;

	return 0;
}