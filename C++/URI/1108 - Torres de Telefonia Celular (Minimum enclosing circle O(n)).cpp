#include <bits/stdc++.h>

using namespace std;
#define eps 1e-8

struct pv{
	double x, y;
	pv(){}
	pv(double a, double b){
		x = a;
		y = b;
	}
	pv operator - (pv other){
		return pv(x - other.x, y - other.y);
	}
	double distance(pv other){
		return hypot(x - other.x, y - other.y);
	}
	double norm(){
		return x * x + y * y;
	}
	int operator ^ (pv other){
		return x * other.y - y * other.x;
	}
};

struct circle{
	double x, y, r;
	circle(){}
	circle(double a, double b, double c){
		x = a;
		y = b;
		r = c;
	}
	circle(pv a, double b){
		x = a.x;
		y = a.y;
		r = b;
	}
	
	bool contains(pv p){
		return pv(x, y).distance(p) <= r + eps;
	}
	bool contains(vector<pv> ps){
		for(auto p : ps)
			if(!contains(p))
				return false;
		return true;
	}
};

circle *makeCircumcircle(pv a, pv b, pv c){
	double d = (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) * 2;
	if(d == 0) return NULL;
	double x = (a.norm() * (b.y - c.y) + b.norm() * (c.y - a.y) + c.norm() * (a.y - b.y)) / d;
	double y = (a.norm() * (c.x - b.x) + b.norm() * (a.x - c.x) + c.norm() * (b.x - a.x)) / d;
	pv p = pv(x, y);
	return new circle(p, p.distance(a));
}

circle makeDiameter(pv a, pv b){
	return circle(pv((a.x + b.x) / 2, (a.y + b.y) / 2), a.distance(b) / 2);
}

circle makeCircleTwoPoints(vector<pv>& points, pv p, pv q){
	circle temp = makeDiameter(p, q);
	if(temp.contains(points))
		return temp;
	
	circle *left = NULL;
	circle *right = NULL;
	
	for(pv r : points){
		pv pq = q - p;
		double cross = pq ^ (r - p);
		circle *c = makeCircumcircle(p, q, r);
		if(c == NULL) continue;
		else if(cross > 0 && (left == NULL || ((pq ^ (pv(c->x, c->y) - p)) > (pq ^ (pv(left->x, left->y) - p)))))
			left = c;
		else if(cross < 0 && (right == NULL || ( (pq ^ (pv(c->x, c->y) - p)) < (pq ^ (pv(right->x, right->y) - p)) )))
			right = c;
	}
	
	return (right == NULL || left != NULL && left->r <= right->r) ? *left : *right;
}

circle makeCircleOnePoint(vector<pv>& points, pv p){
	circle c = circle(p, 0);
	for(int i = 0; i < points.size(); i++){
		pv q = points[i];
		if(!c.contains(q)){
			if(c.r == 0)
				c = makeDiameter(p, q);
			else{
				vector<pv> aux(&points[0], &points[i + 1]);
				c = makeCircleTwoPoints(aux, p, q);
			}
		}
	}
	return c;
}

circle makeCircle(vector<pv> &points){
	vector<pv> shuffled = points;
	random_shuffle(shuffled.begin(), shuffled.end());
	circle c;
	bool first = true;
	for(int i = 0; i < shuffled.size(); i++){
		pv p = shuffled[i];
		if(first || !c.contains(p)){
			vector<pv> aux(&shuffled[0], &shuffled[i + 1]);
			c = makeCircleOnePoint(aux, p);
			first = false;
		}
	}
	return c;
}

double solve2(vector<pv> &points){
	vector<pv> outside;
	double ans = 1000000000.0;
	for (int i = 0; i < points.size(); i++){
		for (int j = i + 1; j < points.size(); j++){
			outside.clear();
			circle c = makeDiameter(points[i], points[j]);
			
			for(int k = 0; k < points.size(); k++)
				if(!c.contains(points[k]))
					outside.push_back(points[k]);

			circle c2 = makeCircle(outside);
			if(c.r >= c2.r) ans = min(ans, c.r);
		}
	}
	
	return ans;
}

double solve3(vector<pv> &points){
	vector<pv> outside;
	double ans = 1000000000.0;
	for (int i = 0; i < points.size(); i++){
		for (int j = i + 1; j < points.size(); j++){
			for(int k = j + 1; k < points.size(); k++){
				circle *c = makeCircumcircle(points[i], points[j], points[k]);
				if(c == NULL) continue;
				outside.clear();
				
				for(int l = 0; l < points.size(); l++)
					if(!c->contains(points[l]))
						outside.push_back(points[l]);
				
				circle c2 = makeCircle(outside);
				if(c->r >= c2.r) ans = min(ans, c->r);
			}
		}
	}
	
	return ans;
}

int main(){
	vector<pv> p;
	int n, x, y;
	while (scanf("%d", &n), n)
	{
		p.clear();
		for(int i = 0; i < n; i++){
			scanf("%d %d", &x, &y);
			p.push_back(pv(x, y));
		}
		
		double ans = solve2(p);
		ans = min(ans, solve3(p));
		printf("%.2lf\n", ans);
	}
	
	return 0;
}

