#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define MAXN 100010
#define oioi printf("oioi\n")

#define AP 0
#define BP 1
double INF = 1000000000000000000.0;

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
		if(start)ret*=10;
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
	double x, y;
	pv(){}
	pv(double _x, double _y){
		x = _x;
		y = _y;
	}
	
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
	}
};

int fst, snd, direcao;

double cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

int getDir(pv a, pv b, pv c){
	double aux = cross(b-a, c-b);
	if(aux > 0) return 1;
	if(aux < 0) return -1;
	return 0;
}

double getArea(pv a, pv b, pv c){
	return fabs(cross(b-a, c-b));
}

double auxiliar(pv a, pv b, pv c){
	return cross(b-a, c-b);
}

bool pode(pv lst2, pv lst1, pv at){
	int dir = getDir(lst2, lst1, at);
	
	return dir == direcao || dir==0;
}

int n;
pv ponto[MAXN];
pv medio[MAXN][2];
int memo[MAXN][2][2][2];
double dp[MAXN][2][2][2];



double solve(int pos, int lst2, int lst1, bool temArea){
	if(pos==n){
		if(!temArea) return INF;
		return 0.0;
	}
	if(memo[pos][lst2][lst1][temArea]) return dp[pos][lst2][lst1][temArea];
	memo[pos][lst2][lst1][temArea] = 1;
	
	double ans = INF;
	double area = 0.0;
	
	if(pos==n-1){
		
		if( pode(medio[pos-2][lst2], medio[pos-1][lst1], medio[pos][AP]) && pode(medio[pos-1][lst1], medio[pos][AP], medio[0][fst]) && pode(medio[pos][AP], medio[0][fst], medio[1][snd]) ){
			area = getArea(medio[0][fst], medio[pos-1][lst1], medio[pos][AP]);
			ans = min(ans, area + solve(pos+1, lst1, AP, temArea || area > 0.0));
			
		}
		
		if( pode(medio[pos-2][lst2], medio[pos-1][lst1], medio[pos][BP]) && pode(medio[pos-1][lst1], medio[pos][BP], medio[0][fst]) && pode(medio[pos][BP], medio[0][fst], medio[1][snd]) ){
			area = getArea(medio[0][fst], medio[pos-1][lst1], medio[pos][BP]);
			ans = min(ans, area + solve(pos+1, lst1, BP, temArea || area > 0.0));
			
		}
		
	}else{
		if( pode(medio[pos-2][lst2], medio[pos-1][lst1], medio[pos][AP]) ){
			
			area = getArea(medio[0][fst], medio[pos-1][lst1], medio[pos][AP]);
			ans = min(ans, area + solve(pos+1, lst1, AP, temArea || area > 0.0));
			
		}
		
		if( pode(medio[pos-2][lst2], medio[pos-1][lst1], medio[pos][BP]) ){
			
			area = getArea(medio[0][fst], medio[pos-1][lst1], medio[pos][BP]);
			ans = min(ans, area + solve(pos+1, lst1, BP, temArea || area > 0.0));
			
		}
	}
	
	
	return dp[pos][lst2][lst1][temArea] = ans;
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	n = read_int();
	
	int x, y;
	for (int i = 0; i < n; i++)
	{
		//~ cin >> x >> y;
		x = read_int();
		y = read_int();
		ponto[i] = pv((double)x, (double)y);
	}
	
	pv A, B;
	
	//~ cin >> x >> y;
	x = read_int();
	y = read_int();
	A = pv(x, y);
	
	//~ cin >> x >> y;
	x = read_int();
	y = read_int();
	B = pv(x, y);
	
	for (int i = 0; i < n; i++)
	{
		medio[i][AP] = pv((ponto[i].x + A.x)/2.0, (ponto[i].y + A.y)/2.0);
		medio[i][BP] = pv((ponto[i].x + B.x)/2.0, (ponto[i].y + B.y)/2.0);
	}
	
	double ans = INF;
	for (int FST = 0; FST < 2; FST++)
	{
		for (int SND = 0; SND < 2; SND++)
		{
			for (int DIR = -1; DIR <= 1; DIR++)
			{
				if(DIR == 0) continue;
				memset(memo, 0, sizeof memo);
				fst = FST;
				snd = SND;
				direcao = DIR;
				ans = min(ans, solve(2, fst, snd, false));
			}
		}
	}
	
	printf("%.3lf\n", ans/2.0);
	//~ cout << fixed << setprecision(3) << ans/2.0 << "\n";
	
	
	return 0;
}
