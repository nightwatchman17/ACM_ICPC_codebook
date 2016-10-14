#include <iostream>
#include <cstdio>
#include <vector>
#include <string.h>
#define N 50000
using namespace std;

vector<int> G[N];
int ind[N], f[N], d[N], head[N], son[N], pn, n;

int dfs(int u,int parent) {
	int i, v, x, w = 0, sum = 1;
	f[u] = parent;
	son[u] = -1;
	for(i = 0; i < G[u].size(); i++) {
		v = G[u][i];
		if(v != parent) {
			d[v] = d[u] + 1;
			x = dfs(v,u);
			sum += x;
			if(x > w) {
				son[u] = v;
				w = x;
			}
		}
	}
	return sum;
}
void chain(int u) {
	int i , v;
	ind[u] = pn++;
	if(f[u] == -1 || son[f[u]] != u)
		head[u] = u;
	else
		head[u] = head[f[u]];
	if(son[u]!=-1)
		chain(son[u]);
	for(i=0; i<G[u].size(); i++) {
		v = G[u][i] ;
		if(v != f[u] && v != son[u])
			chain(v);
	}
}
void modify(int u, int v, ...) {
	while(head[u] != head[v])
		if(d[head[u]] > d[head[v]]) {
			//do something in rang(ind[head[u]], ind[u]);
			u = f[head[u]];
		} else {
			//do something in rang(ind[head[v]], ind[v]);
			v = f[head[v]];
		}
	if(d[u] > d[v])
		//do something in rang(ind[head[u]], ind[u]);
	else
		//do something in rang(ind[head[v]], ind[v]);
}
void build() {
	pn = 1;
	d[0] = 0;	//set depth of root to 0
	dfs(0,-1);	
	chain(0);	//relabel node
}