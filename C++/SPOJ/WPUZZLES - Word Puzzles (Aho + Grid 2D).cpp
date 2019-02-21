    #include <bits/stdc++.h>
    #define pb push_back
    #define mp make_pair
    #define F first
    #define S second
    #define oioi printf("oioi\n")
    #define eoq cout << "eoq" << '\n'
    using namespace std;
    typedef long long int ll;
    typedef unsigned long long int llu;
    typedef pair<ll, ll> ii;
    typedef pair<double, double> dd;
    typedef vector<ll> vi;
    typedef vector<ii> vii;
    const int dx[] = {-1,-1,0,1,1,1,0,-1};
    const int dy[] = {0,1,1,1,0,-1,-1,-1};
    string DIRECAO="ABCDEFGH";
     
    string s;
     
    struct node{
    	node* pai;
    	node* suffix_link;
    	node* nxt[26];
    	bool end;
    	bitset<1000> b;
    	int c;
    	node(int letra, node* p){
    		c = letra;
    		pai = p;
    		suffix_link = NULL;
    		for(int i = 0; i < 26; i++)
    			nxt[i] = NULL;
    		end = false;
    		b.reset();
    	}
    	
    	void add(int i, int idxPattern){
    		if(i==s.size()){
    			end = true;
    			b.set(idxPattern);
    			return;
    		}
    		
    		int letra = s[i]-'A';
    		if(!nxt[letra])
    			nxt[letra] = new node(letra, this);
    		
    		nxt[letra]->add(i+1, idxPattern);
    	}
    	
    	void build(){
    		queue<node*> q;
    		for (int i = 0; i < 26; i++)
    			if(nxt[i]) 
    				q.push(nxt[i]);
    				
    		while (!q.empty())
    		{
    			node* t = q.front(); q.pop();
    			node* w = t->pai->suffix_link;
    			
    			int letra = t->c;
    			while (w && !w->nxt[letra])
    			{
    				w = w->suffix_link;
    			}
    			
    			t->suffix_link = w ? w->nxt[letra] : this;//this = root
    			t->end |= t->suffix_link->end;
    			t->b |= t->suffix_link->b;
    			for (int i = 0; i < 26; i++)
					if(t->nxt[i]) 
						q.push(t->nxt[i]);
				}
    		
    	}
    };
     
    node* trie;
    int grid[1002][1002];
     
    node* sobe(node *t, int letra){
    	
    	while (t && !t->nxt[letra])
    	{
    		t = t->suffix_link;
    	}
    	
    	return t ? t->nxt[letra] : trie;
    }
     
     
     
    int n, m;
    set<int> disp;
    vector<pair<char, pair<int, int> > > saida;
    vector<string> pattern;
     
    void getAns(bitset<1000> b, int x, int y, int dir){
    	vector<int> rem;
    	for (auto i : disp)
    	{
    		if(b[i]){
    			saida[i] = mp(DIRECAO[dir], mp(x-dx[dir]*(pattern[i].size()-1), y-dy[dir]*(pattern[i].size()-1)));
    			rem.pb(i);
    		}
    	}
    	for (int i = 0; i < rem.size(); i++)
    	{
    		disp.erase(rem[i]);
    	}
    	
    }
     
     
     
    void find(int x, int y, int dir){
    	node* t = trie;
    	bool ok = x>=0 && x<n && y>=0 && y<m;
    	while (ok)
    	{
    		
    		int letra = grid[x][y];
    		
    		t = sobe(t, letra);
    		
    		if(t->end){
    			getAns(t->b, x, y, dir);
    		}
    		
    		x += dx[dir];
    		y += dy[dir];
    		
    		ok = x>=0 && x<n && y>=0 && y<m;
    	}
    	
    	
    }
     
    int main () {
    	ios_base::sync_with_stdio (0);
    	cin.tie (0);
    	int tc, qtdPattern;
    	char c;
    	cin >> tc;
    	bool fst = true;
    	while (tc--)
    	{
    		if(!fst) cout << "\n";
    		fst = false;
    		trie = new node('$', NULL);
    		saida.clear();
    		cin >> n >> m >> qtdPattern;
    		pattern.clear();
    		saida.resize(qtdPattern);
    		for (int i = 0; i < n; i++)
    		{
    			for (int j = 0; j < m; j++)
    			{
    				cin >> c;
    				grid[i][j] = c-'A';
    			}
    		}
    		
    		for (int i = 0; i < qtdPattern; i++)
    		{
    			cin >> s;
    			pattern.pb(s);
    			disp.insert(i);
    			trie->add(0, i);
    		}
    		trie->build();
    		
    		for (int i = 0; i < n; i++)
    		{
    			for (int j = 0; j < 8; j++)
    			{
    				find(i, 0, j);
    				find(i, m-1, j);
    			}
    		}
    		for (int i = 0; i < m; i++)
    		{
    			for (int j = 0; j < 8; j++)
    			{
    				find(0, i, j);
    				find(n-1, i, j);
    			}
    		}
    		
    		
    		//~ cout << saida.size() << endl;
    		
    		for (int i = 0; i < saida.size(); i++)
    		{
    			cout << saida[i].S.F << " " << saida[i].S.S << " " << saida[i].F << "\n";
    		}
    		
    	}
    	
    	
    	return 0;
    }
     
