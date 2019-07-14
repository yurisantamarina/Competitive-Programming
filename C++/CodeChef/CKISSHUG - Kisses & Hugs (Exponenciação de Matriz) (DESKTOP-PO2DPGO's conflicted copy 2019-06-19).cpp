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
    ll MOD = 1e9+7;
     
    struct mat{
    	ll v[3][3];
    	mat(){
    		memset(v, 0, sizeof v);
    	}
    	mat operator * (mat other){
    		mat ans;
    		for (int i = 0; i < 3; i++)
    		{
    			for (int j = 0; j < 3; j++)
    			{
    				for (int k = 0; k < 3; k++)
    				{
    					ans.v[i][j] += v[i][k] * other.v[k][j];
    					ans.v[i][j] %= MOD;
    				}
    			}
    		}
    		return ans;
    	}
    };
     
    mat impar, par, base, ret;
     
    mat exponencia(ll exp){
    	if(exp==0) return ret;
    	mat aux = exponencia(exp/2);
    	aux = aux*aux;
    	if(exp%2) aux = aux*base;
    	return aux;
    }
     
    int main () {
    	int t;
    	cin >> t;
    	
    	par.v[0][0] = 2;
    	par.v[0][2] = -1;
    	par.v[1][0] = 1;
    	par.v[2][1] = 1;
    	
    	impar.v[0][0] = 2;
    	impar.v[0][1] = -1;
    	impar.v[1][0] = 1;
    	impar.v[2][1] = 1;
    	
    	base = impar * par;
    	
    	for (int i = 0; i < 3; i++)
    	{
    		ret.v[i][i] = 1;
    	}
    	
    	
    	
    	
    	while (t--)
    	{
    		ll n;
    		mat ans;
    		cin >> n;
    		if(n==1) cout << 2 << "\n";
    		else if(n==2) cout << 4 << "\n";
    		else if(n==3) cout << 6 << "\n";
    		else{
    			if(n%2!=0){
    				ans = exponencia(n/2 - 1);
    			}else{
    				ans = exponencia(n/2 - 2);
    				ans = par * ans;
    			}
    			
    			//~ for (int i = 0; i < 3; i++)
    			//~ {
    				//~ for (int j = 0; j < 3; j++)
    				//~ {
    					//~ cout << ans.v[i][j] << " ";
    				//~ }
    				//~ cout << endl;
    			//~ }
    			
    			ll aux = (ans.v[0][0]*6 + ans.v[0][1]*4 + ans.v[0][2]*2)%MOD;
    			while(aux<0) aux+=MOD;
    			cout << aux%MOD << "\n";
    		}
    	}
    	
    	
    	
    	
    	
    	return 0;
    }
     
