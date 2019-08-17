#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define INF 1010101010

int n, LO, HI, acc[MAXN], v[MAXN], esp[MAXN], accEsp[MAXN], dq[MAXN], ini = 0, fim = 0;

void add(int val){
	while(ini < fim && dq[fim - 1] > val)
		fim--;
	dq[fim++] = val;
}

void del(int val){
	if(ini == fim) return;
	if(dq[ini] == val)
		ini++;
}

int query(){
	return ini < fim ? dq[ini] : INF;
}

int getEspecial(int l, int r){
	return accEsp[r] - accEsp[l-1];
}

int main(){
	scanf("%d %d %d", &n, &LO, &HI);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &v[i]);
		acc[i] = acc[i - 1] + v[i];
	}
	
	int L = 1, R = 1, ans = -INF;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &esp[i]);
		accEsp[i] = accEsp[i - 1] + esp[i];
		
		while(getEspecial(L, i) >= LO && L <= i){
			add(acc[L - 1]);
			L++;
		}
		
		while(getEspecial(R, i) > HI && R < i){
			del(acc[R - 1]);
			R++;
		}
		
		ans = max(ans, acc[i] - query());
	}
	
	printf("%d\n", ans);
	
	
	return 0;
}
