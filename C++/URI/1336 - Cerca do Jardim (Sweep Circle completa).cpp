#include <bits/stdc++.h>

using namespace std;
#define pb push_back

struct pv{
	int x, y, val, tipo;
	pv(){}
	pv(int _x, int _y){
		x = _x;
		y = _y;
		val = 0;
	}
	pv(int _x, int _y, int _val, int _tipo){
		x = _x;
		y = _y;
		val = _val;
		tipo = _tipo;
	}
	
	int getQuad(){
		if(x>=0 && y>=0) return 1;
		if(x<0 && y>=0) return 2;
		if(x<=0 && y<0) return 3;
		return 4;
	}
	
	pv operator + (pv other){
		return pv(x+other.x, y+other.y);
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y, val, tipo);
	}
	
	pv operator * (int k){
		return pv(x*k, y*k);
	}
	
	pv operator / (int k){
		return pv(x/k, y/k);
	}
	
	bool operator == (pv other){
		return x == other.x && y == other.y;
	}
};

int cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

int dot(pv a, pv b){
	return a.x * b.x + a.y * b.y;
}

int normasq(pv a){
	return dot(a, a);
}

bool comparePolarAngle(pv a, pv b){
	if(a==b) return true;
	int q1 = a.getQuad();
	int q2 = b.getQuad();
	
	if(q1==q2){
		if(cross(a, b) == 0) return normasq(a) < normasq(b);
		return cross(a, b) > 0;
	}
	return q1 < q2;
}

void merge(vector<pv> &cima, vector<pv> &baixo, vector<pv> &v){
	v.clear();
	int i = 0, j = 0;
	
	while (i < (int)cima.size() && j < (int)baixo.size())
	{
		if(cross(cima[i], baixo[j]) <= 0) v.pb(cima[i++]);
		else v.pb(baixo[j++]);
	}
	while (i < (int)cima.size())
	{
		v.pb(cima[i++]);
	}
	while (j < (int)baixo.size())
	{
		v.pb(baixo[j++]);
	}
}


void build(vector<pv> &v){
	sort(v.begin(), v.end(), comparePolarAngle);
	vector<pv> cima, baixo;
	for (int i = 0; i < (int)v.size(); i++)
	{
		if((v[i].x >= 0 && v[i].y >= 0) || (v[i].x < 0 && v[i].y > 0)){
			cima.pb(v[i]);
		}else{
			baixo.pb(v[i]);
		}
	}
	
	merge(cima, baixo, v);
	//~ cout << "CIMA:\n";
	//~ for (int i = 0; i < (int)cima.size(); i++)
	//~ {
		//~ cout << cima[i].x << " " << cima[i].y << endl;
	//~ }
	//~ cout << endl;
	//~ cout << "BAIXO:\n";
	//~ for (int i = 0; i < (int)baixo.size(); i++)
	//~ {
		//~ cout << baixo[i].x << " " << baixo[i].y << endl;
	//~ }
	//~ cout << endl;
	//~ cout << "COMPLETO:\n";
	//~ for (int i = 0; i < (int)v.size(); i++)
	//~ {
		//~ cout << v[i].x << " " << v[i].y << endl;
	//~ }
	//~ cout << endl << endl;
}

int p, l;

int solve(int cor1, vector<pv> &v){
	int cor2 = cor1 == 0 ? 1 : 0;
	int sz = (int)v.size();
	//~ cout << endl;
	int at = 0;
	int ans = 1e9;
	for (int i = 0; i < sz; i++)
	{
		//~ printf("%d, %d\n", v[i].x, v[i].y);
		if((v[i].x >= 0 && v[i].y >= 0) || (v[i].x < 0 && v[i].y > 0)){
			if(v[i].tipo != cor1) at += v[i].val;
		}else{
			if(v[i].tipo != cor2) at += v[i].val;
		}
	}
	ans = min(ans, at);
	//~ cout << "at = " << at << endl;
	
	int j;
	for (int i = 0; i < sz; i++)
	{
		j = i;
		while (j < sz && cross(v[j], v[i]) == 0)
		{
			if(v[j].y == 0){
				if(v[j].x > 0){
					if(v[j].tipo == cor1){
						at += v[j].val;
					}else{
						at -= v[j].val;
					}
				}else{
					if(v[j].tipo == cor2){
						at += v[j].val;
					}else{
						at -= v[j].val;
					}
				}
			}else if(v[j].y > 0){
				if(v[j].tipo == cor1){
					at += v[j].val;
				}else{
					at -= v[j].val;
				}
			}else{
				if(v[j].tipo == cor2){
					at += v[j].val;
				}else{
					at -= v[j].val;
				}
			}
			
			
			
			j++;
		}
		i = j-1;
		ans = min(ans, at);
	}
	
	//~ printf("cor = %d ans = %d\n", cor1, ans);
	return ans;
}

int main(){
	int x, y, val;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	while(cin >> p >> l){
		if(p == 0 && l == 0) break;
		vector<pv> v, ent;
		for (int i = 0; i < p; i++)
		{
			cin >> x >> y >> val;
			ent.pb(pv(x, y, val, 0));
		}
		for (int i = 0; i < l; i++)
		{
			cin >> x >> y >> val;
			ent.pb(pv(x, y, val, 1));
		}
		
		int ans = 1e9;
		for (int i = 0; i < p+l; i++)
		{
			v.clear();
			for (int j = 0; j < p+l; j++)
			{
				if(i==j) continue;
				v.pb(ent[j] - ent[i]);
			}
			build(v);
			//~ printf("pivot = (%d, %d)\n", ent[i].x, ent[i].y);
			ans = min(ans, solve(0, v));
			ans = min(ans, solve(1, v));
		}
		
		cout << ans << "\n";
	}
		
	
	
	
	
	return 0;
}

