#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;

multiset<int, greater<int> > s;
int n, v[MAXN];

int main(){
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
		if(i)
			s.insert(v[i] - v[i-1]);
	}
	
	int ans = *s.begin(), mx;
	
	for (int i = 0; i < n; i++)
	{
		if(i == 0 || i == n-1){
			if(i == 0)
				s.erase(s.find(v[1] - v[0]));
			else
				s.erase(s.find(v[n-1] - v[n-2]));
			
			//~ for(auto it : s) cout << it << " ";
			//~ cout << endl;
			mx = *s.begin();
			s.erase(s.find(mx));
			//~ printf("i = %d  mx = %d\n", i, mx);
			if(mx == 1) ans = 1;
			else{
				if(mx & 1){
					s.insert(mx/2);
					s.insert(mx/2+1);
				}else{
					s.insert(mx/2);
					s.insert(mx/2);
				}
				ans = min(ans, *s.begin());
				if(mx & 1){
					s.erase(s.find(mx/2));
					s.erase(s.find(mx/2+1));
				}else{
					s.erase(s.find(mx/2));
					s.erase(s.find(mx/2));
				}
			}
			s.insert(mx);
			if(i == 0)
				s.insert(v[1] - v[0]);
			else
				s.insert(v[n-1] - v[n-2]);
		}else{
			s.erase(s.find(v[i] - v[i-1]));
			s.erase(s.find(v[i+1] - v[i]));
			
			s.insert(v[i+1] - v[i-1]);
			mx = *s.begin();
			if(mx == 1) ans = 1;
			else{
				if(mx & 1){
					s.insert(mx/2);
					s.insert(mx/2+1);
				}else{
					s.insert(mx/2);
					s.insert(mx/2);
				}
				ans = min(ans, *s.begin());
				if(mx & 1){
					s.erase(s.find(mx/2));
					s.erase(s.find(mx/2+1));
				}else{
					s.erase(s.find(mx/2));
					s.erase(s.find(mx/2));
				}
			}
			
			s.insert(v[i] - v[i-1]);
			s.insert(v[i+1] - v[i]);
			s.erase(s.find(v[i+1] - v[i-1]));
		}
	}
	
	cout << ans << "\n";
	
	
	
	return 0;
}
