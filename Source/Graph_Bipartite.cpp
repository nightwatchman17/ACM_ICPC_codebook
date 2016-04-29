class Bipartite {
private:
	static const int MaxNum = 1004;
	vector<int> g[MaxNum];
	bool visited [MaxNum];

	bool bipart(int nowAt, int nowSide) {
		visited[nowAt] = true;
		side[nowAt] = nowSide;
		for(auto &id : g[nowAt])
			if( !visited[id] )
				bipart(id , !nowSide);
			else if( side[id]==nowSide )
				return false;
		return true;
	}
	bool maxMatch(int nowAt) {
		visited[nowAt] = true;
		for(auto &id : g[nowAt])
			if( cp[id]==-1
				|| (!visited[cp[id]] && maxMatch(cp[id])) ){
				cp[id]    = nowAt;
				cp[nowAt] = id;
				return true;
			}
		return false;
	}
	void minVertexCover(int nowAt) {
		MVC[nowAt] = 1;
		for(auto &id : g[nowAt])
			if( !MVC[id] ) {
				MVC[id] = 1;
				minVertexCover(cp[id]);
			}
	}
	void maxIndependentSet(int nowAt) {
		MIS[nowAt] = 1;
		for(auto &id : g[nowAt])
			if( !MIS[cp[id]] )
				maxIndependentSet(cp[id]);
	}
public:
	int  matchNum;     // max match num
	int  cp  [MaxNum]; // id and cp[id] is couple
	bool side[MaxNum]; // left/right side
	bool MVC [MaxNum]; // min vertex cover
	bool MIS [MaxNum]; // max indepent set
	void addEdge(int u, int v) {
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	void init() {
		for(int i=0; i<MaxNum; ++i)
			g[i].clear();
	}
	bool countAll() {
		// if graph is not bipartite return false

		// bipartite
		memset(side, 0, sizeof(side));
		memset(visited , 0 , sizeof(visited));
		for(int i=0 ; i<MaxNum ; ++i)
			if( !visited[i] && !bipart(i, 0) )
				return false;


		// maximum match
		// O(VE), this code can be more optimized
		// alternative: dinic O(V^0.5*E)
		matchNum = 0;
		memset(cp , -1 , sizeof(cp));
		for(int i=0 ; i<MaxNum ; ++i){
			if( cp[i]!=-1 ) continue;
			memset(visited , 0 , sizeof(visited));
			if( maxMatch(i) )
				++matchNum;
		}

		// min vertex cover
		memset(MVC, 0, sizeof(MVC));
		for(int i=0; i<MaxNum; ++i)
			if( side[i]==1 && cp[i]==-1 )
				minVertexCover(i);
		for(int i=0; i<MaxNum; ++i)
			if( side[i]==1 )
				MVC[i] = !MVC[i];

		// max independent set
		memset(MIS, 0, sizeof(MIS));
		for(int i=0; i<MaxNum; ++i)
			if( cp[i]==-1 )
				maxIndependentSet(i);
		for(int i=0; i<MaxNum; ++i)
			if( side[i]==1 && cp[i]!=-1 
				&& !MIS[i] && !MIS[cp[i]] )
				MIS[i] = 1;

		return true;
	}
};
