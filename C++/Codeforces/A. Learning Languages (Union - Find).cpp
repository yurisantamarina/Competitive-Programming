#include <bits/stdc++.h>

using namespace std;

#define MAXN 1<<17 + 1
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define INF 1000000000
typedef long long int ll;

int tam;
int pai[200];
set<int> v[200];

bool tem(int i, int j){
	for(int x : v[i]){
		if(v[j].count(x)) return true;
	}
	return false;
}

int find(int i){
	if(i == pai[i]) return i;
	return pai[i] = find(pai[i]);
}

bool same(int i, int j){
	return find(i) == find(j);
}

void join(int i, int j){
	i = find(i);
	j = find(j);
	if(i==j) return;
	pai[i] = pai[j];
	tam--;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, m, x, a;
	cin >> n >> m;
	tam = n-1;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		pai[i] = i;
		while (x--)
		{
			cin >> a;
			v[i].insert(a);
		}
	}
	
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if((int)v[i].size() == 0) cnt++;
		for (int j = i+1; j < n; j++)
		{
			if(i==j) continue;
			if(tem(i, j) && !same(i, j)){
				join(i, j);
			}
		}
		
	}
	if(cnt == n) tam = n;
	cout << tam << "\n";
	
	
	
	
	return 0;
}
