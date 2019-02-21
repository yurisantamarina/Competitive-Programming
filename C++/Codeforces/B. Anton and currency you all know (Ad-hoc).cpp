#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
typedef long long int ll;
int n, k;

int main(){
	string s;
	cin >> s;
	for (int i = 0; i < s.size()-1; i++)
	{
		if((s[i]-'0')%2 == 0 && s[i] < s[s.size()-1]){
			swap(s[i], s[s.size()-1]);
			cout << s << endl;
			return 0;
		}
	}
	for (int i = s.size()-2; i >= 0; i--)
	{
		if((s[i]-'0')%2 == 0){
			swap(s[i], s[s.size()-1]);
			cout << s << endl;
			return 0;
		}
	}
	
	cout << "-1\n";
	return 0;
}
