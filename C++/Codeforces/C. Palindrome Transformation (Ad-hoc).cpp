#include <bits/stdc++.h>

using namespace std;

int getDif(char a, char b){
	if(a == b) return 0;
	if(a > b){
		swap(a, b);
	}
	return min(b - a, (a - 'a') + 1 + 'z' - b);
}

int main(){
	int n, p, la, ra, lb, rb;
	string s;
	
	cin >> n >> p;
	p--;
	
	cin >> s;
	string rev = s;
	reverse(rev.begin(), rev.end());
	if(rev == s){
		cout << "0\n";
		return 0;
	}
	
	if(n % 2 == 0){
		la = 0; ra = (n/2)-1;
		lb = n/2; rb = n-1;
	}else{
		la = 0; ra = (n/2)-1;
		lb = n/2 + 1; rb = n-1;
	}
	
	int sum = 0, aux;
	int l = -1, r = -1;
	if((la <= p && p <= ra) || (p == n/2 && n%2!=0)){
		
		for (int i = la, j = n-1; i <= ra; i++, j--)
		{
			aux = getDif(s[i], s[j]);
			if(aux == 0) continue;
			
			sum += aux;
			if(l == -1) l = i;
			r = i;
		}
		
		la = l;
		ra = r;
		
		if(p < la){
			sum += ra - p;
		}else if(p > ra){
			sum += p - la;
		}else{
			sum += min(p-la+ra-la, ra-p+ra-la);
		}
		
	}else if(lb <= p && p <= rb){
		for (int i = rb, j = 0; i >= lb; i--, j++)
		{
			aux = getDif(s[i], s[j]);
			if(aux == 0) continue;
			
			sum += aux;
			if(r == -1) r = i;
			l = i;
		}
		
		lb = l;
		rb = r;
		
		if(p < lb){
			sum += rb - p;
		}else if(p > rb){
			sum += p - lb;
		}else{
			sum += min(p-lb+rb-lb, rb-p+rb-lb);
		}
		
	}
	
	cout << sum << "\n";
	
	return 0;
}
