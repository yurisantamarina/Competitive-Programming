#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
int p[MAXN];

int kmp(string &s){
	int idx;
	int n = (int)s.size();
	p[0] = 0;
	
	for (int i = 1; i < n; i++)
	{
		idx = p[i-1];
		while(s[idx] != s[i] && idx > 0)
			idx = p[idx-1];
		
		if(s[idx] == s[i])
			idx++;
		
		p[i] = idx;
	}
	
	
	if(n % (n - p[n-1]) == 0) 
		return n / (n - p[n-1]);
		
	return 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	string a, b;
	set<int> tmp;
	vector<int> div;
	
	cin >> a >> b;
	int szA = (int)a.size();
	int szB = (int)b.size();
	
	int pA = kmp(a);
	int pB = kmp(b);
	
	for (int i = 1; i*i <= pA; i++)
	{
		if(pA % i == 0){
			tmp.insert(szA / i);
			tmp.insert(szA / (pA / i));
		}
	}
	
	for (int i = 1; i*i <= pB; i++)
	{
		if(pB % i == 0){
			if(tmp.count(szB / i))
				div.push_back(szB / i);
				
			if(szB / i != szB / (pB / i) && tmp.count(szB / (pB / i)))
				div.push_back(szB / (pB / i));
		}
	}
	
	if((int)div.size() == 0){
		cout << "0\n";
		return 0;
	}
	
	sort(div.begin(), div.end());
	
	int sz = div[(int)div.size()-1];
	int idx = 0;
	
	while (a[idx] == b[idx] && idx < sz)
		idx++;
	
	int ans = 0;
	for (int i = 0; i < (int)div.size(); i++)
	{
		if(div[i] <= idx) 
			ans++;
		else
			break;
	}
	
	cout << ans << "\n";
	
	
	return 0;
}
