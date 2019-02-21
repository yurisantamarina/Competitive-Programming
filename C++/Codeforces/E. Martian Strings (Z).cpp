#include <bits/stdc++.h>

using namespace std;
#define MAXN 101010
#define LOG 20
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define db(x) cerr << #x << " == " << x << ""
#define _ << ", " << 
typedef long long int ll;

void Z(string &s, vector<int> &z){
	int n = (int)s.size();
	z.resize(n);
	z[0] = 0;
	int l = 0, r = 0;
	
	for (int i = 1; i < n; i++)
	{
		if(i <= r) z[i] = min(z[i - l], r - i + 1);
		while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if(i + z[i] - 1 > r){
			l = i;
			r = i + z[i] - 1;
		}
	}
}

int mx[MAXN];

int process(string &a, string &b){
	string ra = a;
	reverse(ra.begin(), ra.end());
	string rb = b;
	reverse(rb.begin(), rb.end());
	
	string s = a + "$" + b;
	vector<int> z;
	Z(s, z);
	
	string s2 = ra + "$" + rb;
	vector<int> z2;
	Z(s2, z2);
	reverse(z2.begin() + (int)a.size() + 1, z2.end());
	
	mx[(int)z2.size()] = 0;
	for(int i = (int)z2.size() - 1; i > (int)a.size(); i--)
		mx[i] = max(z2[i], mx[i+1]);
	
	for (int i = (int)a.size() + 1; i < (int)z.size(); i++)
	{
		if(i + z[i] + ((int)a.size() - z[i]) > (int)z.size()) return 0;
		if(mx[i + z[i] + ((int)a.size() - z[i])] >= ((int)a.size() - z[i])) return 1;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string text, patt;
	cin >> text;
	int ans = 0, n;
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> patt;
		if((int)patt.size() == 1) continue;
		ans += process(patt, text);
	}
	
	cout << ans << "\n";
	
	return 0;
}

