#include <cstdio>
#include <set>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

int N;
const int k = 4;
vector<int> G[104];
int lable[104];
int available[104];
bool notok[104][4];

void update_available(int u, int val, set<pair<int,int>> &nds) {
    if( nds.find({available[u], u}) != nds.end() ) {
        nds.erase({available[u], u});
        nds.insert({val, u});
    }
    available[u] = val;
}

bool kcolor(set<pair<int,int>> &nds) {
    if( nds.size() == 0 )
        return true;
    int nowAt = nds.begin()->second;
    nds.erase(nds.begin());
    for(int i=0; i<k; ++i) {
        if( notok[nowAt][i] )
            continue;
        bool gg = false;
        lable[nowAt] = i;
        vector<int> affect;
        for(auto u : G[nowAt])
            if( !notok[u][i] ) {
                if( available[u]-1 < 1 ) {
                    gg = true;
                    break;
                }
                update_available(u, available[u]-1, nds);
                notok[u][i] = true;
                affect.push_back(u);
            }
        if( !gg && kcolor(nds) )
            return true;
        lable[nowAt] = -1;
        for(auto u : affect) {
            update_available(u, available[u]+1, nds);
            notok[u][i] = false;
        }
    }
    nds.insert({available[nowAt], nowAt});
    return false;
}

int main() {
    int u, v;
    scanf("%d", &N);
    while( scanf("%d-%d", &u, &v) != EOF ) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    memset(lable, -1, sizeof(lable));
    memset(notok, 0, sizeof(notok));
    set<pair<int,int>> nodes;
    for(int i=1; i<=N; ++i) {
        available[i] = k;
        nodes.insert({available[i], i});
    }
    assert(kcolor(nodes));
    assert(nodes.size() == 0);
    for(int i=1; i<=N; ++i)
        printf("%d %d\n", i, lable[i]+1);
    return 0;
}
