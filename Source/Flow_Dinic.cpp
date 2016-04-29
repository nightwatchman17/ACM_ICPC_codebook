struct Dinic{
	enum{
		maxN = 104
	};

	int maxFlow;
	int pipe[maxN][maxN];
	vector<int> g[maxN];

	void init(){
		maxFlow = 0;
		memset(pipe , 0 , sizeof(pipe));
		for(int i=0;i<maxN;++i)
			g[i].clear();
	}

	int level[maxN];
	bool bfsLabeling(int s,int t){
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
	
	int dfsFindRoute(const int &nowAt,const int &t,const int &maxC){
		if( nowAt==t ){
			maxFlow += maxC;
			return maxC;
		}
		for(int i=0;i<g[nowAt].size();++i){
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

	void findMaxFlow(int s,int t){
		while( bfsLabeling(s,t) )
			while( dfsFindRoute(s,t,1e8) )
				;
	}

	void findMinCut(int s,int t){
		findMaxFlow(s,t);
		for(int i=0;i<maxN;++i){
			if( level[i]!=0 )
				continue;
			for(int j=0;j<g[i].size();++j)
				if( level[g[i][j]]==0 )
					printf("%d %d\n",i,g[i][j]);
		}
	}
};
