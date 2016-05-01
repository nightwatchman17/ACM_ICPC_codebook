class TwoSAT {
private:
	static const int maxN = 100004;
	static const int size = 2*maxN + 4;
	bool        pick[size];
	vector<int> G   [size];

	int id(int i, int T) { return (i<<1) + T; }
	int alter(int i) { return i^1; }
	bool dfsTry(int nowAt, vector<int> &stk) {
		if( pick[alter(nowAt)] )
			return false;
		stk.emplace_back(nowAt);
		pick[nowAt] = true;
		for(auto v : G[nowAt]) {
			if( !pick[v] && !dfsTry(v, stk) )
				return false;
		}
		return true;
	}
public:
	void init() {
		memset(pick, 0, sizeof(pick));
		for(int i=0; i<size; ++i)
			G[i].clear();
	}
	void addClause(bool TA, int A, bool TB, int B) {
		// Add clause (TA + TB)
		// When TA not true, TB must true. vise versa.
		G[id(A, !TA)].emplace_back(id(B, TB));
		G[id(B, !TB)].emplace_back(id(A, TA));
	}
	bool solve() {
		// O(n) solve
		memset(pick, 0, sizeof(pick));
		for(int i=0; i<maxN; ++i) {
			if( pick[id(i, 0)] || pick[id(i, 1)] )
				continue;
			vector<int> stk;
			if( dfsTry(id(i, 0), stk) )
				continue;
			for(auto v : stk)
				pick[v] = false;
			if( !dfsTry(id(i, 1), stk) )
				return false;
		}
		return true;
	}
	bool T(int i) {
		// should solve() first
		return pick[id(i, 1)];
	}
};
