https://sio2.mimuw.edu.pl/c/brazil-2018-day1/submit/
https://szkopul.edu.pl/problemset/problem/4yTtNIf4H61mJrquuAIhoSh_/site/?key=statement

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
typedef long long int ll;

struct pv{
	int x, y;
	pv(){}
	pv(int a, int b){
		x = a;
		y = b;
	}
	int operator ^ (pv other) const{
		return x * other.y - y * other.x;
	}
	int operator * (pv other) const{
		return x * other.x + y * other.y;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
};

struct seg{
	pv a, b;
	seg(){}
	seg(pv aa, pv bb){
		a = aa;
		b = bb;
	}
};

vector<pv> pts;
map<pair<int, int>, int> mapa;
pv poly[1300];
int n, acc[620][1300], online[620][620], isVertice[620], vet[1300], valor[10010];

bool onSeg(pv p, seg s){
	pv a = s.a;
	pv b = s.b;
	int c1 = (p-a) ^ (b-a);
	int c2 = (p-a) * (b-a);
	int c3 = (p-b) * (a-b);
	return c1 == 0 && c2 >= 0 && c3 >= 0;
}

int get2(int l, int r, int pivo){
	if(l < 0 || r < 0){
		cout << "oi\n";
		return 0;
	}
	return acc[pivo][r] - acc[pivo][l];
}

int get(int l, int r, int pivo){
	if(l < 0 || r < 0){
		cout << "oi\n";
		return 0;
	}
	int ans = acc[pivo][r] - acc[pivo][l];
	ans += online[pivo][vet[l]];
	return ans;
}

int getSum(int a, int b, int c){
	int v1 = vet[a];
	int v2 = vet[b];
	int v3 = vet[c];
	
	int ans = get(b, c, a);
	ans -= get2(v3 + n - (c - b), v3 + n - 1, v3);
	//~ ans += isVertice[v1];
	//~ ans += isVertice[v2];
	//~ ans += isVertice[v3];
	
	return ans;
}

void search(int a, int idx){
	int lo = 1, hi = n-2, mid, c1, c2;
	pv p = pts[idx], p1, p2;
	
	while(lo <= hi){
		mid = (lo + hi)/2;
		p1 = poly[a + mid];
		p2 = poly[a + mid + 1];
		
		
		if(onSeg(p, seg(poly[a], p1))){
			online[a][vet[a + mid]] += valor[idx];
			acc[a][a + mid] += valor[idx];
			return;
		}
		if(onSeg(p, seg(poly[a], p2))){
			online[a][vet[a + mid + 1]] += valor[idx];
			acc[a][a + mid + 1] += valor[idx];
			return;
		}
		c1 = (p1 - poly[a]) ^ (p - poly[a]);
		c2 = (p2 - poly[a]) ^ (p - poly[a]);
		if(c1 < 0 && c2 > 0){
			acc[a][a + mid + 1] += valor[idx];
			return;
		}
		if(c1 > 0) hi = mid - 1;
		else lo = mid + 1;
	}
}

void build(int a){
	for (int i = 0; i < pts.size(); i++)
	{
		if(onSeg(pts[i], seg(poly[a], poly[a + 1]))){
			online[a][vet[a + 1]] += valor[i];
			continue;
		}
		if(onSeg(pts[i], seg(poly[a], poly[a + n - 1]))){
			online[a][vet[a + n - 1]] += valor[i];
			acc[a][a + n - 1] += valor[i];
			continue;
		}
		search(a, i);
	}
	for(int i = a + 1; i < a + n; i++)
		acc[a][i] += acc[a][i-1];
}

int main(){
	//~ ios_base::sync_with_stdio(0);
	//~ cin.tie(0);
	//~ cin >> n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		//~ cin >> poly[i].x >> poly[i].y;
		scanf("%d %d", &poly[i].x, &poly[i].y);
		
		poly[i+n] = poly[i];
		mapa[mp(poly[i].x, poly[i].y)] = i;
		vet[i+n] = vet[i] = i;
	}
	
	int q, x, y;
	//~ cin >> q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		//~ cin >> x >> y >> valor[i];
		scanf("%d %d %d", &x, &y, &valor[i]);
		//~ if(mapa.count(mp(x, y))) isVertice[mapa[mp(x, y)]] += valor[i];
		pts.pb(pv(x, y));
	}
	
	for (int i = 0; i < n; i++)
		build(i);
	
	int ans = -1e9;
	for (int a = 0; a < n; a++)
	{
		for (int b = a + 1; b < n; b++)
		{
			for (int c = b + 1; c < n; c++)
			{
				ans = max(ans, getSum(a, b, c));
			}
		}
	}
	printf("%d\n", ans);
	//~ cout << ans << "\n";
	
	return 0;
}
