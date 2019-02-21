#include <bits/stdc++.h>

using namespace std;


multiset<int> s;
int n, m, q, cnt;
int grid[510][510];

int get(){
	return (int)s.size() ? *(--s.end()) : 0;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> q;
	for (int i = 0; i < n; i++)
	{
		cnt = 0;
		for (int j = 0; j < m; j++)
		{
			cin >> grid[i][j];
			if(grid[i][j] == 1) cnt++;
			else{
				s.insert(cnt);
				cnt = 0;
			}
		}
		if(cnt) s.insert(cnt);
	}
	
	int x, y;
	while (q--)
	{
		cin >> x >> y;
		x--; y--;
		
		cnt = 0;
		for (int i = 0; i < m; i++)
		{
			if(grid[x][i] == 1) cnt++;
			else{
				s.erase(s.find(cnt));
				cnt = 0;
			}
		}
		if(cnt) s.erase(s.find(cnt));
		grid[x][y] ^= 1;
		
		cnt = 0;
		for (int i = 0; i < m; i++)
		{
			if(grid[x][i] == 1) cnt++;
			else{
				s.insert(cnt);
				cnt = 0;
			}
		}
		if(cnt) s.insert(cnt);
		
		cout << get() << "\n";
	}
	
	
	
	return 0;
}
