class TreeMinVertexCover {
private:
	static const int maxNum = 100004;
	vector<int> G[maxNum];
	int in[maxNum];
public:
	bool pick[maxNum];
	int MVC; // min vertext cover
	void init() {
		for(int i=0; i<maxNum; ++i)
			G[i].clear();
		memset(in, 0, sizeof(in));
	}
	void addEdge(int u, int v) {
		G[u].emplace_back(v);
		G[v].emplace_back(u);
		++in[u];
		++in[v];
	}
	int treeMinVertexCover() {
		memset(pick, 0, sizeof(pick));
		MVC = 0;
		queue<int> myQ;
		for(int i=1; i<=maxNum; ++i)
			if( in[i]==1 ) myQ.push(i);
		while( myQ.size() ) {
			int nowAt = myQ.front();
			myQ.pop();
			if( in[nowAt]==0 ) continue;
			++MVC;
			int id;
			for(int i=0; i<G[nowAt].size(); ++i)
				if( in[G[nowAt][i]] ) {
					id = G[nowAt][i];
					break;
				}
			for(int i=0; i<G[id].size(); ++i)
				if( in[G[id][i]] ) {
					--in[G[id][i]];
					--in[id];
					if( in[G[id][i]]==1 )
						myQ.push(G[id][i]);
				}
		}
		return MVC;
	}
};
