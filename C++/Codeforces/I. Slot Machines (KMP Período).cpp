http://codeforces.com/gym/101667

#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000010
int p[MAXN], n, s[MAXN];

void kmp(){
	p[0] = 0;
	int idx = 0;
	
	for (int i = 1; i < n; i++)
	{
		while(s[idx] != s[i] && idx > 0) idx = p[idx-1];
		if(s[idx] == s[i]) idx++;
		p[i] = idx;
	}
}

int main(){
	scanf("%d", &n);
	int x;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		s[n - i - 1] = x;
	}
	kmp();
	
	int pAt, kAt, ans = 1000000000, pAns = 100000000, kAns;
	for (int i = 0; i < n; i++)
	{
		pAt = i + 1 - p[i];
		kAt = n - i - 1;
		if(pAt + kAt < ans){
			ans = pAt + kAt;
			pAns = pAt;
			kAns = kAt;
		}else if(pAt + kAt == ans){
			if(pAt < pAns){
				pAns = pAt;
				kAns = kAt;
			}
		}
	}
	printf("%d %d\n", kAns, pAns);
	
	return 0;
}
