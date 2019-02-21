#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
typedef long long int ll;
#define F first
#define S second
#define MAXN 101010

struct reta{
	ll a, b, id;
	reta(){}
	reta(ll _a, ll _b, ll _id){
		a = _a;
		b = _b;
		id = _id;
	}
	
	ll getY(ll x){
		return a*x + b;
	}
};

struct node{
	vector<reta> ch;
	node(){
		ch.clear();
	}
	bool remove(reta _1, reta _2, reta _3){
		return (_3.b - _1.b) * (_1.a - _2.a) <= (_2.b - _1.b) * (_1.a - _3.a);
	}
	
	void add(reta r){
		while (ch.size() > 1 && remove(ch[ch.size()-2], ch[ch.size()-1], r))
		{
			ch.pop_back();
		}
		ch.pb(r);
	}
};

node st[4*MAXN];
vector<reta> v;

bool compare(reta _1, reta _2){
	if(_1.a == _2.a)
		return _1.b > _2.b;
	return _1.a < _2.a;
}

vector<reta> SAIDAQUICURIOSO(vector<reta> esq, vector<reta> dir){
	vector<reta> total;
	for (int i = 0; i < esq.size(); i++)
	{
		total.pb(esq[i]);
	}
	
	for (int i = 0; i < dir.size(); i++)
	{
		total.pb(dir[i]);
	}
	int lst;
	sort(total.begin(), total.end(), compare);
	node ans;
	for (int i = 0; i < total.size(); i++)
	{
		if(i==0){
			ans.add(total[i]);
		}else{
			if(total[i].a != total[i-1].a)
				ans.add(total[i]);
		}
	}
	return ans.ch;
}

void build(int no, int l, int r){
	if(l==r){
		st[no] = node();
		st[no].add(v[l]);
		return;
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	
	st[no].ch = SAIDAQUICURIOSO(st[nxt].ch, st[nxt+1].ch);
}

pair<ll, ll> nulo = mp(-100000, -100000);
pair<ll, ll> getAns(int no, int x){
	int lo = 0;
	vector<reta> &CH_RES = st[no].ch;
	int hi = CH_RES.size() - 2;
	int mid, mid2;
	
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		mid2 = mid+1;
		if(CH_RES[mid].getY(x) <= CH_RES[mid2].getY(x)){
			lo = mid+1;
		}else{
			hi = mid-1;
		}
	}
	
	return mp(CH_RES[lo].id, CH_RES[lo].getY(x));
}

ll X;
pair<ll, ll> query(int no, int l, int r, int i, int j){
	if(l > j || r < i) return nulo;
	if(i<=l && r<=j){
		return getAns(no, X);
	}
	int nxt = 2*no;
	int mid = (l+r)/2;
	pair<ll, ll> esq = query(nxt, l, mid, i, j);
	pair<ll, ll> dir = query(nxt+1, mid+1, r, i, j);
	
	if(esq.S > dir.S) return esq;
	return dir;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q, a, b, l, r, x;
	cin >> n >> q;
	for (int i = 0; i < n; i++)
	{
		cin >> b >> a;
		v.pb(reta(a, b, i));
	}
	build(1, 0, n-1);
	while (q--)
	{
		cin >> l >> r >> X;
		l--; r--;
		cout << query(1, 0, n-1, l, r).F+1 << "\n";
		 
	}
	
	
	
}
