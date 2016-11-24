class TwoSAT {
private:
	int V;
	vector<bool> pick;
	vector< vector<int> > G;

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
	void init(int varNum) {
		V = varNum;
		pick = vector<bool>(V*2 + 4, false);
		G = vector< vector<int> >(V*2 + 4);
	}
	void addClause(bool TA, int A, bool TB, int B) {
		// Add clause (TA + TB)
		G[id(A, !TA)].emplace_back(id(B, TB));
		G[id(B, !TB)].emplace_back(id(A, TA));
	}
	void imply(bool TA, int A, bool TB, int B) {
		// TA -> TB
		addClause(!TA, A, TB, B);
	}
	void preset(bool TA, int A) {
		pick[id(A, TA)] = true;
	}
	bool solve() {
		vector<int> stk;
		for(int i=0; i<V; ++i) {
			if( pick[id(i, true)] && !dfsTry(id(i, true), stk) )
				return false;
			if( pick[id(i, false)] && !dfsTry(id(i, false), stk) )
				return false;
			stk.clear();
		}
		for(int i=0; i<V; ++i) {
			if( pick[id(i, 0)] || pick[id(i, 1)] )
				continue;
			stk.clear();
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
		// should solved first
		return pick[id(i, 1)];
	}
};
