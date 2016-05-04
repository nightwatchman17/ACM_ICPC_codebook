class System_of_DifConstrain {
private:
	static const int maxN = 504;
	static const int maxM = 3004;
	struct Edge {
		int s, t;
		long long cost;
	};
	Edge es[maxM];
	int eSize;
public:
	bool solvable;
	long long x[maxN]; // one solution
	void init() {
		eSize = -1;
	}
	void addConstrain(int xI, int xJ, long long c) {
		// add xi - xj <= c
		es[++eSize] = {xJ, xI, c};
	}
	bool solve(int n=maxN) {
		// n is max # of node of CC
		memset(x, 0, sizeof(x));
		for(int i=0; i<n; ++i)
		for(int j=0; j<=eSize; ++j)
			if( x[es[j].s] + es[j].cost < x[es[j].t] )
				x[es[j].t] = x[es[j].s] + es[j].cost;
		for(int j=0; j<=eSize; ++j)
			if( x[es[j].s] + es[j].cost < x[es[j].t] )
				return solvable = false;
		return solvable = true;
	}
};
