#include <bits/stdc++.h>

using namespace std;

struct pv{
	double x, y;
	pv(){}
	pv(double a, double b){
		x = a;
		y = b;
	}
	pv operator - (pv other) const{
		return pv(x - other.x, y - other.y);
	}
	pv operator + (pv other) const{
		return pv(x + other.x, y + other.y);
	}
	double operator * (pv other) const{
		return x * other.x + y * other.y;
	}
	double norma(){
		return sqrt((*this) * (*this));
	}
	pv operator * (double k) const{
		return pv(x * k, y * k);
	}
	pv operator / (double k) const{
		return pv(x / k, y / k);
	}
};

struct circle{
	pv c;
	double r;
	circle(){}
	circle(pv a, double b){
		c = a;
		r = b;
	}
};

circle v[120];
double dist[120][120];

double distPtPt(pv a, pv b){
	return (a-b).norma();
}

double getCost(int i, int j){
	circle c1 = v[i];
	circle c2 = v[j];
	
	double cost = distPtPt(c1.c, c2.c);
	if(cost < 1e-9) return 0.0;
	
	pv vet = c2.c - c1.c;
	vet = vet / vet.norma();
	
	pv p1 = c1.c + vet * c1.r;
	pv p2 = c1.c - vet * c1.r;
	
	cost = min({cost, distPtPt(p1, c2.c), distPtPt(p2, c2.c)});
	return cost;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, x, y, x0, yy;
	while (cin >> n >> x >> y >> x0 >> yy)
	{
		if(n == -1 && x == -1 && y == -1 && x0 == -1 && yy == -1) break;
		v[0] = circle(pv(x, y), 0);
		v[1] = circle(pv(x0, yy), 0);
		
		for (int i = 2; i < n+2; i++)
			cin >> v[i].c.x >> v[i].c.y >> v[i].r;
		
		for (int i = 0; i < n+2; i++)
			for (int j = 0; j < n+2; j++)
				dist[i][j] = getCost(i, j);
			
		for(int k = 0; k < n+2; k++)
			for(int i = 0; i < n+2; i++)
				for(int j = 0; j < n+2; j++)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				
		cout << fixed << setprecision(2) << dist[0][1] << "\n";
	}
	
	
	return 0;
}
