#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;

struct rec{
	int d;
	string acao;
	double consumo;
	rec(){}
	rec(int a, string b, double c){
		d = a;
		acao = b;
		consumo = c;
	}
};

vector<rec> v;

double solve(){
	double consumoAtual = v[0].consumo;
	double ans = 0;
	double sum = 0;
	double leak = 0;
	
	for (int i = 1; i < v.size(); i++)
	{
		//~ cout << "atual = " << consumoAtual << " " << v[i].acao << " d = " << (v[i].d - v[i-1].d) << endl;
		sum = sum + (v[i].d - v[i-1].d)*1.0*(consumoAtual + leak);
		if(v[i].acao == "Leak") leak++;
		else if(v[i].acao == "Gas"){
			ans = max(ans, sum);
			sum = 0;
		}else if(v[i].acao == "Mechanic"){
			leak = 0;
		}else if(v[i].acao == "Fuel"){
			consumoAtual = v[i].consumo;
		}
	}
	ans = max(ans, sum);
	
	return ans;
}

int main(){
	string entrada, acao;
	int d, consumo;
	
	bool fst=true;
	while (getline(cin, entrada))
	{
		stringstream ss;
		ss << entrada;
		ss >> d;
		ss >> acao;
		if(acao == "Fuel"){
			ss >> acao;
			ss >> consumo;
			if(consumo==0) break;
			
			v.pb(rec(d, "Fuel", consumo*1.0/100));
		}else{
			if(acao=="Goal"){
				
				v.pb(rec(d, acao, -1));
				cout << fixed << setprecision(3) << solve() << "\n";
				//~ for (int i = 0; i < v.size(); i++)
				//~ {
					//~ cout << v[i].d << " " << v[i].acao << " " << v[i].consumo << endl;
				//~ }
				//~ cout << endl;
				
				v.clear();
			}else v.pb(rec(d, acao, -1));
			
		}
	}
	
	
}
