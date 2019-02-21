#include <bits/stdc++.h>

using namespace std;
#define MAXN 1010101
set<int> pos[MAXN];
int e[MAXN], A, B, C, N, M, F;

void update(int house, int team){
	pos[e[house]].erase(house);
	e[house] = team;
	pos[e[house]].insert(house);
}

pair<int, int> query(int house, int team){
	if(pos[team].size() == 1) return {N, N};
	int cw, ccw;
	
	if(*pos[team].begin() == house){
		ccw = house + N - *(--pos[team].end());
	}else{
		auto it = pos[team].find(house);
		it--;
		ccw = house - *it;
	}
	
	if(*(--pos[team].end()) == house){
		cw = N - house + *pos[team].begin();
	}else{
		cw = *pos[team].upper_bound(house) - house;
	}
	
	return {ccw, cw};
}

void build(){
	e[1] = A;
	pos[e[1]].insert(1);
	for (int i = 2; i <= N; i++){
		e[i] = (B * e[i-1] + C) % F;
		pos[e[i]].insert(i);
	}
}

int main(){
	
	scanf("%d %d", &N, &F);
	scanf("%d %d %d", &A, &B, &C);
	build();
	
	int house, team;
	pair<int, int> p;
	
	scanf("%d", &M);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d %d", &house, &team);
		update(house, team);
		p = query(house, team);
		printf("%d %d\n", p.first, p.second);
	}
	
	
	return 0;
}
