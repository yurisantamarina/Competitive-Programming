#include <bits/stdc++.h>

using namespace std;

int n;

bool ok(int i, int j, int ii, int jj){
	cout << "? " << i << " " << j << " " << ii << " " << jj << endl;
	string s;
	cin >> s;
	return s[0] == 'Y';
}

string askIda(){
	int i = 1, j = 1;
	string s = "";
	while ((i + j) < (n + 1)){
		if(ok(i + 1, j, n, n)){
			i++;
			s += 'D';
		}else{
			j++;
			s += 'R';
		}
	}
	
	return s;
}

string askVolta(){
	int i = n, j = n;
	string s;
	
	while((i + j) > (n + 1)){
		if(ok(1, 1, i, j - 1)){
			j--;
			s += 'R';
		}else{
			i--;
			s += 'D';
		}
	}
	
	return s;
}

string getAns(){
	string normal = "", reverso = "";
	
	normal = askIda();
	reverso = askVolta();
	
	reverse(reverso.begin(), reverso.end());
	return normal + reverso;
}

int main(){
	cin >> n;
	
	string s = getAns();
	cout << "! " << s << "\n";
	
	return 0;
}
