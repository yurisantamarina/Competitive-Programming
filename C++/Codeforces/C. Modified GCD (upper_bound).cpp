#include <bits/stdc++.h>

using namespace std;

int main(){
	int a, b, l, r, q;
	cin >> a >> b;
	set<int> s, div;
	set<int>::iterator it;
	
	int sz = (int)sqrt(a);
	for (int i = 1; i <= sz; i++)
	{
		if(a % i == 0){
			s.insert(i);
			s.insert(a/i);
		}
	}
	
	
	sz = (int)sqrt(b);
	for (int i = 1; i <= sz; i++)
	{
		if(b % i == 0){
			if(s.count(i)) div.insert(i);
			if(s.count(b/i)) div.insert(b/i);
		}
	}
	
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> l >> r;
		it = div.upper_bound(r);
		if(it == div.begin()){
			cout << "-1\n";
		}else{
			it--;
			if(*it >= l) cout << *it << "\n";
			else cout << "-1\n";
		}
	}
	
	
	return 0;
}
