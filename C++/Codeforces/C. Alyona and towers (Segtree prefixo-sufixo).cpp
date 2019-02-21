#include <bits/stdc++.h>

using namespace std;

#define MAXN 301010
typedef long long int ll;

struct node{
	int a, b, c, d, e, f, ans, tam;
	ll vl, vr;
	node(){}
	node(int aa, int bb, int cc, int dd, int ee, int ff, int anss, int tamm, ll vll, ll vrr){
		a = aa;
		b = bb;
		c = cc;
		d = dd;
		e = ee;
		f = ff;
		ans = anss;
		tam = tamm;
		vl = vll;
		vr = vrr;
	}
};

node st[4*MAXN];
ll lazy[4*MAXN];
int v[MAXN];

void merge(int at, int esq, int dir){
	node x = st[esq];
	node y = st[dir];
	node z;
	
	z.a = x.a;
	z.b = y.b;
	z.c = x.c;
	z.d = y.d;
	z.e = x.e;
	z.f = y.f;
	z.tam = x.tam + y.tam;
	z.vl = x.vl;
	z.vr = y.vr;
	z.ans = max(x.ans, y.ans);
	
	//A
	if(x.e == x.tam){//pega o segmento lleiro
		if(x.vr != y.vl){//nao tem dois no topo com mesmo valor
			z.a = max(z.a, x.e + y.c);
		}
	}
	//A
	if(x.a == x.tam){
		if(y.vl < x.vr){//comeco do c e menor que o final do llervalo a
			z.a = max(z.a, x.a + y.c);
		}
	}
	//A
	if(x.e == x.tam){
		if(x.vr < y.vl){
			z.a = max(z.a, x.e + y.a);
		}
	}
	
	//B
	if(y.f == y.tam){
		if(y.vl != x.vr){
			z.b = max(z.b, y.f + x.d);
		}
	}
	//B
	if(y.b == y.tam){
		if(x.vr < y.vl){
			z.b = max(z.b, y.b + x.d);
		}
	}
	//B
	if(y.f == y.tam){
		if(y.vl < x.vr){
			z.b = max(z.b, x.b + y.f);
		}
	}
	
	//C
	if(x.c == x.tam){
		if(x.vr > y.vl){
			z.c = max(z.c, x.c + y.c);
		}
	}
	
	//D
	if(y.d == y.tam){
		if(x.vr < y.vl){
			z.d = max(z.d, y.d + x.d);
		}
	}
	
	//E
	if(x.e == x.tam){
		if(x.vr < y.vl){
			z.e = max(z.e, x.e + y.e);
		}
	}
	
	//F
	if(y.f == y.tam){
		if(y.vl < x.vr){
			z.f = max(z.f, x.f + y.f);
		}
	}
	
	//ans
	if(y.vl < x.vr){
		z.ans = max(z.ans, x.b + y.c);
	}
	//ans
	if(x.vr != y.vl){
		z.ans = max(z.ans, x.d + y.c);
	}
	//ans
	if(x.vr < y.vl){
		z.ans = max(z.ans, x.d + y.a);
	}
	
	st[at] = z;
}

void prlla(int no){
	node x = st[no];
	printf("a = %d\n", x.a);
	printf("b = %d\n", x.b);
	printf("c = %d\n", x.c);
	printf("d = %d\n", x.d);
	printf("e = %d\n", x.e);
	printf("f = %d\n", x.f);
	printf("ans = %d\n", x.ans);
	printf("tam = %d\n", x.tam);
	printf("vl = %d\n", x.vl);
	printf("vr = %d\n", x.vr);
	
	printf("\n\n");
}

void build(int no, int l, int r){
	if(l == r){
		st[no] = node(1, 1, 1, 1, 1, 1, 1, 1, v[l], v[l]);
		lazy[no] = 0;
		return;
	}
	int nxt = 2*no, mid = (l+r)/2;
	build(nxt, l, mid);
	build(nxt+1, mid+1, r);
	merge(no, nxt, nxt+1);
	lazy[no] = 0;
}

void propagate(int no, int l, int r){
	if(lazy[no] == 0) return;
	int nxt = 2*no;
	st[no].vl += lazy[no];
	st[no].vr += lazy[no];
	if(l!=r){
		lazy[nxt] += lazy[no];
		lazy[nxt+1] += lazy[no];
	}
	lazy[no] = 0;
}

void update(int no, int l, int r, int i, int j, ll val){
	propagate(no, l, r);
	if(j < l || r < i){
		return;
	}
	if(i<=l && r<=j){
		lazy[no] += val;
		propagate(no, l, r);
		return;
	}
	
	int nxt= 2*no, mid = (l+r)/2;
	update(nxt, l, mid, i, j, val);
	update(nxt+1, mid+1, r, i, j, val);
	merge(no, nxt, nxt+1);
}

int main(){
	int n, q, l, r, d;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &v[i]);
	}
	
	build(1, 0, n-1);
	
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d %d %d", &l, &r, &d);
		l--; r--;
		update(1, 0, n-1, l, r, d);
		printf("%d\n", st[1].ans);
	}
	
	
	
	return 0;
}
