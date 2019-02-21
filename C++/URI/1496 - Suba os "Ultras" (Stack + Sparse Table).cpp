#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define LOG 19
#define F first
#define S second
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

int v[MAXN];
int proem[MAXN];
int l[MAXN];
int r[MAXN];
int st[MAXN][LOG];
int n;
int ans[MAXN];
int idx;

void buildST(){
	for (int i = 0; i < n; i++)
		st[i][0] = v[i];
	
	for (int j = 1; j < LOG; j++)
	{
		for (int i = 0; i+(1<<j)-1 < n; i++)
		{
			st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
		}
	}
}

void buildLR(){
	stack<pair<int, int> > p;
	for (int i = 0; i < n; i++)
	{
		while(!p.empty() && v[i] >= p.top().F) p.pop();
		if(p.empty()) l[i] = -1;
		else l[i] = p.top().S;
		p.push(make_pair(v[i], i));
	}
	while(!p.empty()) p.pop();
	
	for (int i = n-1; i >= 0; i--)
	{
		while(!p.empty() && v[i] >= p.top().F) p.pop();
		if(p.empty()) r[i] = -1;
		else r[i] = p.top().S;
		p.push(make_pair(v[i], i));
	}
}

int getMin(int l, int r){
	if(l > r) return 1e9;
	int k = 31 - __builtin_clz(r-l+1);
	return min(st[l][k], st[r - (1<<k) + 1][k]);
}

int main(){
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; i++)
			scanint(v[i]);
		
		idx = 0;
		buildST();
		buildLR();
		for (int i = 0; i < n; i++)
		{
			
			//~ cout << "i = " << i+1 << ": " << l[i]+1 << " " << r[i]+1 << endl;
			if(l[i] == -1 && r[i] == -1){
				proem[i] = v[i];
			}else if(l[i] == -1){
				proem[i] = v[i] - getMin(i+1, r[i]-1);
			}else if(r[i] == -1){
				proem[i] = v[i] - getMin(l[i]+1, i-1);
			}else{
				proem[i] = v[i] - max(getMin(l[i]+1, i-1), getMin(i+1, r[i]-1));
			}
			//~ cout << proem[i] << endl << endl;
			if(proem[i] >= 150000) ans[idx++] = i+1;
		}
		
		for (int i = 0; i < idx; i++)
		{
			if(i) printf(" ");
			printf("%d", ans[i]);
		}
		printf("\n");
	}
	
	
	return 0;
}
