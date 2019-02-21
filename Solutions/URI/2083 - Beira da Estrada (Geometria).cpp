#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define mp make_pair
#define F first
#define S second
int read_int(){
	char r;
	bool start=false,neg=false;
	int ret=0;
	while(true){
		r=getchar();
		if((r-'0'<0 || r-'0'>9) && r!='-' && !start){
			continue;
		}
		if((r-'0'<0 || r-'0'>9) && r!='-' && start){
			break;
		}
		if(start)ret*=10LL;
		start=true;
		if(r=='-')neg=true;
		else ret+=r-'0';
	}
	if(!neg)
		return ret;
	else
		return -ret;
}

struct pv{
	int x, y;
	pv(){}
	pv(int _x, int _y){
		x = _x;
		y = _y;
	}
	
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
	}
};

map<pair<ll, int>, int> mapa;
set<pair<ll, int> > s;
pv vet[1010];
int n;

/*
(x, y) = (x0, y0) + t * (vx, vy);
x = x0 + t * vx;
y = y0 + t * vy;

t = -y0 / vy;

x = x0 - (y0/vy) * vx;
x = (vy * x0 - y0 * vx) / vy;
*/

void solve(pv at, pv other){
	pv v = other - at;
	ll num = (ll)v.y * (ll)at.x - (ll)at.y * (ll)v.x;
	int den = v.y;
	int g = __gcd(num, (ll)den);
	num /= g;
	den /= g;
	
	if(!s.count(mp(num, den))){
		mapa[mp(num, den)]++;
		s.insert(mp(num, den));
	}
}

int main(){
	int x, y;
	//~ cin >> n;
	n = read_int();
	for (int i = 0; i < n; i++)
	{
		//~ cin >> x >> y;
		x = read_int();
		y = read_int();
		vet[i] = pv(x, y);
	}
	
	for (int i = 0; i < n; i++)
	{
		s.clear();
		for (int j = 0; j < n; j++)
		{
			if(i==j || vet[i].y <= vet[j].y) continue;
			
			solve(vet[i], vet[j]);
		}
		
	}
	
	set<int> ans;
	ans.insert(n);
	for(auto i : mapa){
		ans.insert(i.S);
	}
	printf("%d\n", (int)ans.size());
	//~ cout << ans.size() << "\n";
	
	
	
	return 0;
}
