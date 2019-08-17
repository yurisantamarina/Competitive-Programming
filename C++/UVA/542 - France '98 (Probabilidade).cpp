#include <bits/stdc++.h>

using namespace std;

string nome[17];
double prob[17][17];
double probQuartas[17];
double probSemi[17];
double probFinal[17];
double probCampeao[17];

int main(){
	for (int i = 1; i <= 16; i++)
		cin >> nome[i];
	
	for (int i = 1; i <= 16; i++)
	{
		for (int j = 1; j <= 16; j++)
		{
			cin >> prob[i][j];
			prob[i][j] /= 100.0;
		}
	}
	
	//probQuartas e a probabilidade do time chegar nas quartas de final
	for (int i = 1; i <= 16; i++)
	{
		if(i%2 != 0) probQuartas[i] = prob[i][i+1];
		else probQuartas[i] = prob[i][i-1];
	}
	
	//probSemi e a probabilidade do time chegar na semi final
	for (int i = 1; i <= 16; i++)
	{
		if(i % 4 == 1 || i % 4 == 2){//parte de cima
			if(i % 2 != 0){
				probSemi[i] += probQuartas[i] * probQuartas[i+2] * prob[i][i+2];
				probSemi[i] += probQuartas[i] * probQuartas[i+3] * prob[i][i+3];
			}else{
				probSemi[i] += probQuartas[i] * probQuartas[i+1] * prob[i][i+1];
				probSemi[i] += probQuartas[i] * probQuartas[i+2] * prob[i][i+2];
			}
		}else{//parte de baixo
			if(i % 2 != 0){
				probSemi[i] += probQuartas[i] * probQuartas[i-1] * prob[i][i-1];
				probSemi[i] += probQuartas[i] * probQuartas[i-2] * prob[i][i-2];
			}else{
				probSemi[i] += probQuartas[i] * probQuartas[i-2] * prob[i][i-2];
				probSemi[i] += probQuartas[i] * probQuartas[i-3] * prob[i][i-3];
			}
		}
		
		//~ cout << probSemi[i]*100 << "\n";
	}
	//~ cout << endl;
	
	//probFinal e a probabilidade do time chegar na final
	for (int i = 1; i <= 16; i++)
	{
		if(i >= 1 && i <= 4){
			for(int j = 5; j <= 8; j++){
				probFinal[i] += probSemi[i] * probSemi[j] * prob[i][j];
			}
		}else if(i <= 8){
			for(int j = 1; j <= 4; j++){
				probFinal[i] += probSemi[i] * probSemi[j] * prob[i][j];
			}
		}else if(i <= 12){
			for(int j = 13; j <= 16; j++){
				probFinal[i] += probSemi[i] * probSemi[j] * prob[i][j];
			}
		}else{
			for(int j = 9; j <= 12; j++){
				probFinal[i] += probSemi[i] * probSemi[j] * prob[i][j];
			}
		}
		
		//~ cout << probFinal[i]*100 << "\n";
	}
	
	//probCampeao e a probabilidade do time ser campeao
	for (int i = 1; i <= 16; i++)
	{
		if(i <= 8){
			for (int j = 9; j <= 16; j++){
				probCampeao[i] += probFinal[i] * probFinal[j] * prob[i][j];
			}
		}else{
			for (int j = 1; j <= 8; j++){
				probCampeao[i] += probFinal[i] * probFinal[j] * prob[i][j];
			}
		}
		cout << nome[i];
		for(int j = 0; j < 10 - nome[i].size(); j++) cout << " ";
		cout << " p=" << fixed << setprecision(2) << probCampeao[i]*100 << "%\n";
	}
	
	
	return 0;
}
