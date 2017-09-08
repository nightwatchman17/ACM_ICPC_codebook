const int N = 100000 + 10;
int visit[N], low[N], instack[N], time_stamp = 0;
int sccID[N], sccNum;
int numOfScc[N];
vector<int> G[N];
vector<int> stack;

void scc_dfs(int u) {
    visit[u] = low[u] = ++time_stamp;
    stack.push_back(u);
    instack[u] = true;

    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!visit[v])
            scc_dfs(v);
        if (instack[v])
           low[u] = min(low[u], low[v]);
    }

    if (visit[u] == low[u]) {
        int v;
        do {
            v = stack.back();
            stack.pop_back();
            instack[v] = false;
            sccID[v] = sccNum;
            numOfScc[sccNum]++;
        } while (v != u);
        sccNum++;
    }
}

// 0 base
void tarjan(int n) {
     memset(visit, 0, sizeof(visit));
     memset(numOfScc, 0, sizeof(numOfScc));
     memset(instack, 0, sizeof(instack));
     time_stamp = 0;
     sccNum = 0;
     for (int i = 0; i < n; ++i)
        if (!visit[i])
            scc_dfs(i);
}