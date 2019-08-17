#include <bits/stdc++.h>

using namespace std;
#define mp make_pair
#define pb push_back
int dx[] = {1, 0, -1, 0, 1, -1, 1, -1};
int dy[] = {0, 1, 0, -1, 1,  1,-1, -1};
typedef long long int ll;

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	ll operator ^ (pv other) const{
		return (ll)x * other.y - (ll)y * other.x;
	}
	ll operator * (pv other) const{
		return (ll)x * other.x + (ll)y * other.y;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
};

vector<pv> v, s;
map<pair<int, int>, int> vis;
int quero, n;

bool onSeg(pv p, pv a, pv b){
	return ((p-a) * (b-a)) > 0 && ((p-b) * (a-b)) > 0;
}

int sinal(ll a){
	if(a > 0) return 1;
	if(a < 0) return -1;
	return 0;
}

bool tri(pv p, pv a, pv b, pv c){
	int A = sinal((b-a) ^ (p-a));
	int B = sinal((c-b) ^ (p-b));
	int C = sinal((a-c) ^ (p-c));
	
	return A == B && B == C;
}

bool inside(pv p){
	if(vis.count(mp(p.x, p.y))) return false;
	int lo = 1, hi = n-2, mid;
	ll c1, c2;
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		c1 = (v[mid] - v[0]) ^ (p - v[0]);
		c2 = (v[mid + 1] - v[0]) ^ (p - v[0]);
		if(c2 == 0 && mid + 1 == n - 1) return false;
		if(c1 == 0 && mid == 1) return false;
		
		if(c1 < 0 && c2 > 0) return tri(p, v[0], v[mid], v[mid+1]);
		if(c1 == 0) return onSeg(p, v[0], v[mid]);
		if(c2 == 0) return onSeg(p, v[0], v[mid+1]);
		if(c1 > 0) hi = mid-1;
		else lo = mid+1;
	}
	
	return false;
}

void dfs(int x, int y){
	if(s.size() >= quero) return;
	if(vis.count(mp(x, y))) return;
	vis[mp(x, y)] = 1;
	
	//~ printf("estou em %d %d\n", x, y);
	for (int i = 0; i < 8; i++)
	{
		if(inside(pv(x+dx[i], y+dy[i]))){
			s.pb(pv(x+dx[i], y+dy[i]));
			dfs(x+dx[i], y+dy[i]);
		}
	}
}

int main(){
	int tc, x, y;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		vis.clear();
		s.clear();
		v.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y;
			v.pb(pv(x, y));
			vis[mp(x, y)] = 1;
		}
		reverse(v.begin(), v.end());
		
		quero = n / 10;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < 8; j++)
			{
				if(inside(pv(v[i].x + dx[j], v[i].y + dy[j]))){
					s.pb(pv(v[i].x+dx[j], v[i].y+dy[j]));
					dfs(v[i].x+dx[j], v[i].y+dy[j]);
				}
			}
		}
		
		//~ cout << "sz = " << s.size() << endl;
		if(s.size() >= quero){
			for (int i = 0; i < quero; i++)
				cout << s[i].x << " " << s[i].y << "\n";
		}else cout << "-1\n";
	}
	
	
	
	return 0;
}
