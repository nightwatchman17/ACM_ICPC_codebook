class Dinic{
private:
	static const int maxN = 104;
	int pipe[maxN][maxN];
	vector<int> g[maxN];

	int level[maxN];
	bool bfsLabeling(int s, int t){
		memset(level , 0 , sizeof(level));
		queue<int> myQ;
		myQ.push( s );
		level[s] = 1;
		while( !myQ.empty() ){
			int nowAt = myQ.front();
			myQ.pop();
			for(int i=0;i<g[nowAt].size();++i)
				if( !level[g[nowAt][i]] && pipe[nowAt][g[nowAt][i]] ){
					level[g[nowAt][i]] = level[nowAt] + 1;
					myQ.push( g[nowAt][i] );
				}
		}
		return level[t];
	}
	int dfsFindRoute(int nowAt, int t, int maxC) {
		if( nowAt==t ){
			maxFlow += maxC;
			return maxC;
		}
		for(int i=0; i<g[nowAt].size(); ++i) {
			int next = g[nowAt][i];
			if( level[next] != level[nowAt]+1 ) continue;
			if( !pipe[nowAt][next] ) continue;
			int nowOut = dfsFindRoute(next ,t ,min(maxC , pipe[nowAt][next]));
			if( nowOut==0 )
				continue;
			pipe[nowAt][next] -= nowOut;
			pipe[next][nowAt] += nowOut;
			return nowOut;
		}
		return 0;
	}

public:
	int maxFlow;
	vector<pii> minCut;

	void init(){
		memset(pipe , 0 , sizeof(pipe));
		for(int i=0;i<maxN;++i)
			g[i].clear();
		maxFlow = 0;
		minCut.clear();
	}
	void addEdge(int u, int v, int c) {
		if( u==v ) return;
		if( pipe[u][v]==0 ) {
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
		pipe[u][v] += c;
		pipe[v][u] += c;
	}
	void coculAll(int s, int t) {
		// max flow
		while( bfsLabeling(s,t) )
			while( dfsFindRoute(s,t,1023456789) )
				;

		// min cut
		for(int i=0;i<maxN;++i) {
			if( level[i]!=0 )
				continue;
			for(int j=0; j<g[i].size(); ++j)
				if( level[g[i][j]]==0 )
					minCut.push_back({i, g[i][j]});
		}
	}
};
