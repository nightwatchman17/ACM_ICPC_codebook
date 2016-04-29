struct MinVertexCover {
private:
	static const int MaxNum = 54;
	vector<int> G[MaxNum];
	int in[MaxNum];

	int undo(vector<int> &record) {
		for(int i=0; i<record.size(); ++i)
			++in[record[i]];
		record.clear();
	}
	int delNode(int u, vector<int> &record) {
		for(int i=0; i<G[u].size(); ++i)
			if( in[G[u][i]] ) {
				--in[G[u][i]];
				--in[u];
				record.push_back(G[u][i]);
				record.push_back(u);
			}
	}

	int cnt(int from, int *visited, bool type) {
		if( visited[from] ) return 0;
		if( type==1 ) visited[from] = 1;
		for(int i=0; i<G[from].size(); ++i)
		if( in[G[from][i]] && !visited[G[from][i]] )
			return type+cnt(G[from][i], visited, !type);
		return type;
	}
	int cnt(int *visited) {
		int ret = 0;
		for(int i=0; i<MaxNum; ++i)
			if( in[i]==1 && !visited[i] )
				ret += cnt(i, visited, 0);
		for(int i=0; i<MaxNum; ++i)
			if( in[i]==2 && !visited[i] )
				ret += cnt(i, visited, 0);
		return ret;
	}

public:
	int MVCPick[MaxNum];
	int MVC; // min vertex cover
	void init() {
		for(int i=0; i<MaxNum; ++i)
			G[i].clear();
		memset(in, 0, sizeof(in));
	}
	void addEdge(int u, int v) {
		G[u].push_back(v);
		G[v].push_back(u);
		++in[u];
		++in[v];
	}
	void minVertexCover(int nowMVC=0, const int *lastPick=NULL) {
		// O(n^2 * 1.38^n)
		int nowPick[MaxNum] = {};
		if( nowMVC==0 ) {
			MVC = MaxNum;
			memset(MVCPick, 0, sizeof(MVCPick));
		}
		else memcpy(nowPick, lastPick, sizeof(nowPick));

		int maxid = 0;
		for(int i=0; i<MaxNum; ++i)
			if( in[i]>in[maxid] )
				maxid = i;
		if( in[maxid]<=2 ) {
			nowMVC += cnt(nowPick);
			if( nowMVC<MVC ) {
				MVC = nowMVC;
				memcpy(MVCPick, nowPick, sizeof(nowPick));
			}
			return;
		}

		vector<int> record;

		delNode(maxid, record);
		nowPick[maxid] = 1;
		minVertexCover(nowMVC+1, nowPick);
		nowPick[maxid] = 0;
		undo(record);

		int cnt = 0;
		for(int i=0; i<G[maxid].size(); ++i)
			if( in[G[maxid][i]] ) {
				++cnt;
				delNode(G[maxid][i], record);
				nowPick[G[maxid][i]] = 1;
			}
		minVertexCover(nowMVC+cnt, nowPick);
		undo(record);
	}
};
