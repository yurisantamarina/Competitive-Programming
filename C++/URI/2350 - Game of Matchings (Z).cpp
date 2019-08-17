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
int k, idx = 0;
int lst[27];
int z[MAXN];

int Z(){
	
	z[0] = 0;
	int l = 0, r = 0, n = idx, ans = 0;
	
	
	for (int i = 1; i < n; i++)
	{
		if(s[i] == -1e9){
			z[i] = 0;
			l = i;
			r = i;
			continue;
		}
		if(i <= r) z[i] = min(z[i-l], r-i+1);
		
		while(i + z[i] < n && (s[z[i]] == s[i+z[i]] || (s[z[i]]==0 && s[i+z[i]] > z[i])))//tem q checar se o s[i+z[i]] é maior do que o prefixo que estou formando. Se for, quer dizer que ele aponta para fora do range e deve ser considerado como 0
			z[i]++;
		
		if(i + z[i] - 1 >= r){
			l = i;
			r = i + z[i] - 1;
		}
		
		if(z[i] == k)
			ans++;
	}
	
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
			s[idx++] = 0;
		else
			s[idx++] = i - lst[x];
		
		lst[x] = i;
	}
	
	s[idx++] = -1e9;

	memset(lst, -1, sizeof lst);
	int c, sz = strlen(text);
	for (int i = 0; i < sz; i++)
	{
		c = text[i] - 'a';
		if(lst[c] == -1)
			s[idx++] = 0;
		else
			s[idx++] = i - lst[c];
		
		lst[c] = i;
	}
	
	printf("%d\n", Z());
	
	
	
	
	return 0;
}
