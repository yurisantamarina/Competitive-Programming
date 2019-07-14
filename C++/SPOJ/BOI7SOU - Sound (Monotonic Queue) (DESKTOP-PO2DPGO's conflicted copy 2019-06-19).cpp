#include <bits/stdc++.h>

using namespace std;
#define MAXN 1000010
int v[MAXN];
int n, m, c;
deque<int> mn, mx;

void add(int val){
	while(mn.size() > 0 && mn.back() > val)
		mn.pop_back();
	mn.push_back(val);
	
	while(mx.size() > 0 && mx.back() < val)
		mx.pop_back();
	mx.push_back(val);
}

void del(int val){
	if(val == mn.front())
		mn.pop_front();
	if(val == mx.front())
		mx.pop_front();
}

int getMin(){
	return mn.front();
}

int getMax(){
	return mx.front();
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> c;
	bool ok = false;
	for (int i = 1; i <= n; i++)
	{
		cin >> v[i];
		if(i <= m){
			add(v[i]);
		}else{
			del(v[i-m]);
			add(v[i]);
			
			
		}
		
		if(i >= m){
			if(getMax() - getMin() <= c){
				cout << i-m+1 << "\n";
				ok = true;
			}
		}
	}
	if(!ok) 
		cout << "NONE\n";
	
	
}
