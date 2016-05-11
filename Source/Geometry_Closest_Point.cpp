#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 10010
#define INFINITY__ 1e10
using namespace std;
int diff(double f) {
	if(fabs(f) < 1e-9)
		return 0;
	return f < 0 ? -1 : 1;
}
struct point {
	double x, y;
	bool operator < (const point &p) const {
		return diff(x - p.x) < 0;
	}
};
point pt[N], tmp[N];
double dis(point a,point b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
double closestpoint(int L,int R) {
	if(R - L + 1 == 1) return INFINITY__;
	int M = (L+R)/2;
	double middle = pt[M].x;
	double Ldis = closestpoint(L, M);
	double Rdis = closestpoint(M+1, R);
	double radi = min(Ldis, Rdis);
	int cntpt = 0;
	merge(pt+L, pt+M+1, pt+M+1, pt+R+1, tmp+L, [](point a,point b) {
		return diff(a.y - b.y) < 0;
	});
	copy(tmp + L,tmp + R + 1, pt + L);
	for(int i = L; i <= R; i++)
		if(diff(fabs(pt[i].x - middle) - radi) < 0)
			tmp[cntpt++] = pt[i];
	for(int i = 0; i < cntpt; i++)
		for(int j = 1; i + j < cntpt && j < 8; j++)
			radi = min(radi, dis(tmp[i], tmp[i+j]));
	return radi;
}
