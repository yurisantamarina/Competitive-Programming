#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
int n;
string s;
stack<char> p;
int main(){
	cin >> n;
	cin >> s;
	for (int i = 0; i < n; i++)
	{
		if(p.empty()) p.push(s[i]);
		else if(p.top() != s[i]) p.pop();
		else p.push(s[i]);
	}
	cout << p.size() << endl;
	
	
	return 0;
}
