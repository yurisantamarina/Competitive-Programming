#include <bits/stdc++.h>

using namespace std;

#define MAXN 1010101
#define gc getchar_unlocked // ou usar só getchar

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}


int s[MAXN];
char text[MAXN];
int k, SIZE = 0;
int lst[27];
int p[MAXN];

int kmp(){
	p[0] = 0;
	int idx, n = SIZE, ans = 0;
	
	//~ cout << n << endl;
	for (int i = 1; i < n; i++)
	{
		idx = p[i-1];
		
		while(!(s[idx] == s[i] || (s[i] > idx && s[idx] == 0)) && idx > 0)
			idx = p[idx-1];
			
		
		if(s[idx] == s[i] || (s[i] > idx && s[idx] == 0))
			idx++;
		
		p[i] = idx;
		if(p[i] == k)
			ans++;
			
		//~ cout << p[i] << " ";
	}
	//~ cout << endl;
	return ans;
}

int main(){
	
	scanf("%s", text);
	scanint(k);
	memset(lst, -1, sizeof lst);
	
	int x;
	
	for (int i = 0; i < k; i++)
	{
		scanint(x);
		
		if(lst[x] == -1)
			s[SIZE++] = 0;
		else
			s[SIZE++] = i - lst[x];
		
		lst[x] = i;
	}
	s[SIZE++] = -1e9;

	memset(lst, -1, sizeof lst);
	int c, sz = strlen(text);
	for (int i = 0; i < sz; i++)
	{
		c = text[i] - 'a';
		if(lst[c] == -1)
			s[SIZE++] = 0;
		else
			s[SIZE++] = i - lst[c];
		
		lst[c] = i;
	}
	
	printf("%d\n", kmp());
	
	
	
	
	return 0;
}
