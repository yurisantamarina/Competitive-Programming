#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define oioi printf("oioi\n")
#define eoq cout << "eoq" << '\n'
#define CLS while (getchar () != '\n')
using namespace std;
typedef long long int ll;
typedef unsigned long long int llu;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int dx[] = { 0, 1, -1, 0, 1, -1, -1,  1};
const int dy[] = {-1, 0,  0, 1, 1,  1, -1, -1};

double prob[2][10000];//probabilidade de comecar sacando na rodada i
 
int main () {
	
	int n, t;
	double ganhar, perder;
	cin >> t;
	while (t--)
	{
		cin >> n >> ganhar;
		perder = 1-ganhar;
		prob[0][1] = 1.0;//0 sempre comeca sacando
		prob[1][1] = 0;
		for (int i = 2; i <= n+1; i++)
		{
			prob[0][i] = prob[1][i-1]*0.7 + prob[0][i-1]*0.3;//probabilidade do 1 comecar sacando na rodada anterioir e ganhar + probabilidade do 0 comecar sacando na rodada anterior e perder
			prob[1][i] = 1-prob[0][i];
		}
		
		cout << prob[0][n]*0.7 + prob[1][n]*0.3 << "\n";//probabilidade do 0 ganhar na rodada n == comecar sacando e ganhar + nao comecar sacando e ganhar
	}
	
	return 0;
}
