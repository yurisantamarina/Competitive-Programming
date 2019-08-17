#include <bits/stdc++.h>

using namespace std;
#define F first
#define S second
#define MAXN 1010
typedef pair<int, int> pii;
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

char grid[MAXN][MAXN];
int le[MAXN], ri[MAXN], mx[MAXN], hist[MAXN], n, m, k;

void update(int lin){
	for (int i = 1; i <= m; i++)
	{
		if(grid[lin][i] == '#') hist[i] = 0;
		else hist[i]++;
	}
	
	stack<int> p;
	for (int i = 1; i <= m; i++)
	{
		while(p.size() > 0 && hist[p.top()] >= hist[i])
			p.pop();
		le[i] = p.empty() ? 0 : p.top();
		p.push(i);
	}
	while(p.size() > 0)
		p.pop();
	
	for (int i = m; i >= 1; i--)
	{
		while(p.size() > 0 && hist[p.top()] >= hist[i])
			p.pop();
		ri[i] = p.empty() ? m + 1 : p.top();
		p.push(i);
		
		int len = ri[i] - le[i] - 1;
		mx[len] = max(mx[len], hist[i]);
	}
	
}

void solve(){
	for (int i = 1; i <= n; i++)
		update(i);
	
	for (int i = 1000; i >= 0; i--)
		mx[i] = max(mx[i+1], mx[i]);
}

bool cabe(int l, int w){
	return mx[l] >= w || mx[w] >= l;
}

int main(){
	//~ scanint(n);
	//~ scanint(m);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		getchar();
		for (int j = 1; j <= m; j++)
			scanf("%c", &grid[i][j]);
	}
	
	solve();
	
	scanint(k);
	int ans = -1, C = -1, L = -1, c, l;
	for (int i = 0; i < k; i++)
	{
		scanint(c);
		scanint(l);
		if(cabe(c, l)){
			if(c * l >= ans){
				if(c * l > ans){
					ans = c * l;
					C = c;
					L = l;
				}else{
					if(l > L){
						C = c;
						L = l;
					}
				}
			}
		}
	}
	
	printf("%d %d\n", C, L);
	
	return 0;
}
