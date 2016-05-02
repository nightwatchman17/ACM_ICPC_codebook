#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;
//Biconnected Components
struct BCC {
	static const int maxNum = 1010;
	vector<int> G[maxNum], bccGroup[maxNum];
	int Node;
	int bcc_cnt;
	int timeStamp;
	int low[maxNum];
	int visit[maxNum];
	int bcc[maxNum];
	bool is_ap[maxNum];
	stack< pair<int,int> > S;
	BCC(int Node) {
		for(int i = 0; i < maxNum; i++) {
			G[i].clear();
			bccGroup[i].clear();
			low[i] = visit[i] = bcc[i] = -1;
			is_ap[i] = false;
		}
		this->Node = Node;
		bcc_cnt = 0;
	}
	void DFS(int u,int parent) {
		int children = 0;
		low[u] = visit[u] = timeStamp++;
		for(int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if(visit[v] == -1) {
				S.push(make_pair(u, v));
				children++;
				DFS(v, u);
				low[u] = min(low[u], low[v]);
				if(low[v] >= visit[u]) {
					is_ap[u] = true;
					pair<int,int> e;
					do {
						e = S.top();
						if(bcc[e.first] != bcc_cnt) {
							bccGroup[bcc_cnt].push_back(e.first);
							bcc[e.first] = bcc_cnt;
						}
						if(bcc[e.second] != bcc_cnt) {
							bccGroup[bcc_cnt].push_back(e.second);
							bcc[e.second] = bcc_cnt;
						}
						S.pop();
					}while(e.first!=u || e.second!=v);
					bcc_cnt++;
				}
			} else if(v != parent) {
				S.push(make_pair(u, v));
				low[u] = min(low[u], visit[v]);
			}
		}
		if(u == parent)	// u is root
			is_ap[u] = (children >= 2);
	}
	void articulation_vertex() {
		timeStamp = 0;
		for(int i = 0; i < Node; i++)
			if(low[i] == -1)
				DFS(i, i);
	}
};
