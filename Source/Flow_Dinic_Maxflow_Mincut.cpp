class Dinic{
private:
    typedef pair<int,int> pii;
    static const int maxN = 504;
    static const int infF = 1023456789;
    int cap [maxN][maxN];
    int pipe[maxN][maxN];
    vector<int> g[maxN];
    int level[maxN], visited[maxN];

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
        visited[nowAt] = true;
        if( nowAt==t ){
            maxFlow += maxC;
            return maxC;
        }
        for(int i=0; i<g[nowAt].size(); ++i) {
            int next = g[nowAt][i];
            if( visited[next] ) continue;
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
    void dfsFindMinCut(int nowAt) {
        sside[nowAt] = 1;
        for(auto v : g[nowAt])
            if( !sside[v] && pipe[nowAt][v] )
                dfsFindMinCut(v);
    }

public:
    int maxFlow;
    bool sside[maxN];
    vector<pii> minCut;

    void init() {
        memset(cap  , 0, sizeof(cap));
        memset(pipe , 0, sizeof(pipe));
        memset(sside, 0, sizeof(sside));
        for(int i=0;i<maxN;++i)
            g[i].clear();
        maxFlow = 0;
        minCut.clear();
    }
    void addEdge(int u, int v, int c) {
        if( u==v ) return;
        if( !cap[u][v] && !cap[v][u] ) {
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        cap[u][v] += c;
    }
    void coculAll(int s, int t) {
        memcpy(pipe, cap, sizeof(pipe));

        // max flow
        while( bfsLabeling(s,t) ) {
            memset(visited, 0, sizeof(visited));
            while( dfsFindRoute(s,t,infF) )
                ;
        }

        // min cut
        dfsFindMinCut(s);
        for(int u=0; u<maxN; ++u)
        if( sside[u] )
            for(auto v : g[u])
            if( !sside[v] )
                minCut.push_back({u, v});
    }
};
