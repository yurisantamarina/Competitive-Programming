#include <bits/stdc++.h>

using namespace std;
#define MAXN 201010
int st[MAXN*4];
vector<pair<int, char> > v;
map<char, int> mapa;
map<int, char> rev;
string s;
int n;
set<int> occ[100];

void update(int no, int l, int r, int pos, int val){
	if(pos < l || pos > r) return;
	if(l == r){
		st[no] = val;
		return;
	}
	int nxt = 2*no, mid = (l+r)/2;
	update(nxt, l, mid, pos, val);
	update(nxt+1, mid+1, r, pos, val);
	st[no] = st[nxt] + st[nxt+1];
}

int build(){
	int idx = 0;
	for (char i = 'a'; i <= 'z'; i++){
		mapa[i] = idx++;
		rev[mapa[i]] = i;
	}
	for (char i = 'A'; i <= 'Z'; i++){
		mapa[i] = idx++;
		rev[mapa[i]] = i;
	}
	for (char i = '0'; i <= '9'; i++){
		mapa[i] = idx++;
		rev[mapa[i]] = i;
	}
		
	for (int i = 0; i < (int)s.size(); i++)
	{
		update(1, 1, n, i+1, 1);
		occ[mapa[s[i]]].insert(i+1);
	}
	return idx;
}

int kesimo(int no, int l, int r, int k){
	if(l == r) return l;
	int nxt = 2*no, mid = (l+r)/2, sumEsq = st[nxt];
	if(sumEsq >= k) return kesimo(nxt, l, mid, k);
	return kesimo(nxt+1, mid+1, r, k-sumEsq);
}

int getPos(int pos){
	return kesimo(1, 1, n, pos);
}

void process(int l, int r, int c){
	l = getPos(l);
	r = getPos(r);
	for(auto it = occ[c].lower_bound(l); *it <= r && it != occ[c].end(); it = occ[c].erase(it))
		update(1, 1, n, *it, 0);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int q, l, r;
	char c;
	cin >> n >> q;
	cin >> s;
	
	int sz = build();
	
	while (q--)
	{
		cin >> l >> r >> c;
		process(l, r, mapa[c]);
	}
	
	for (int i = 0; i < sz; i++)
		for(auto j : occ[i])
			v.push_back(make_pair(j, rev[i]));
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++)
		cout << v[i].second;
	cout << "\n";
	
	
	return 0;
}
