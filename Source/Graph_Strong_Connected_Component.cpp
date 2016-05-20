class SCC {
private:
    static const int maxN = 10004;
    vector<int> G[maxN];
    vector<int> invG[maxN];
    vector<int> stk;
    bool visited[maxN];
    void dfs_1(int nowAt) {
        visited[nowAt] = true;
        for(auto v : G[nowAt])
            if( !visited[v] )
                dfs_1(v);
        stk.emplace_back(nowAt);
    }
    void dfs_2(int nowAt, const int id) {
        sccID[nowAt] = id;
        for(auto v : invG[nowAt])
            if( sccID[v]==-1 )
                dfs_2(v, id);
    }
public:
    int sccNum;
    int sccID[maxN];

    void init() {
        for(int i=0; i<maxN; ++i) {
            G   [i].clear();
            invG[i].clear();
        }
    }
    void addEdge(int u, int v) {
        G   [u].emplace_back(v);
        invG[v].emplace_back(u);
    }
    vector<vector<int>> findAllSCC(int base, int n) {
        memset(visited, 0, sizeof(visited));
        stk.clear();
        for(int i=base; i<=n; ++i)
            if( !visited[i] )
                dfs_1(i);

        sccNum = 0;
        memset(sccID, -1, sizeof(sccID));
        for(int i=stk.size()-1; i>=0; --i)
            if( sccID[stk[i]]==-1 ) {
                dfs_2(stk[i], sccNum);
                ++sccNum;
            }

        // returned zero base scc dag
        vector<vector<int>> sccDAG(sccNum);
        vector<unordered_set<int>> have(sccNum);
        for(int u=base; u<=n; ++u) {
            int sccU = sccID[u];
            for(auto v : G[u]) {
                int sccV = sccID[v];
                if( sccU==sccV ) continue;
                if( have[sccU].find(sccV) == have[sccU].end() ) {
                    have  [sccU].insert      (sccV);
                    sccDAG[sccU].emplace_back(sccV);
                }
            }
        }

        return sccDAG;
    }
};
