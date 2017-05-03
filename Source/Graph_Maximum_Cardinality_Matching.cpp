#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

struct BlossomAlgorithm {
    private:
        // number of vertex, zero base
        static const int N = 205;
        int match[N];
        int d[N];
        queue<int> q;
        deque<int> path[N];
        
        void label_one_side(int x, int y, int bi) {
            for(int i = bi+1; i < path[x].size(); i++) {
                int z = path[x][i];
                if (d[z] == 1) {
                    path[z] = path[y];
                    path[z].insert(path[z].end(), path[x].rbegin(), path[x].rend()-i);
                    d[z] = 0;
                    q.push(z);
                }
            }
        }
        
        bool BFS(int r) {
            for (int i = 0; i < n; ++i)
                path[i].clear();
            path[r].push_back(r);
         
            memset(d, -1, sizeof(d));
            d[r] = 0;

            while(!q.empty())
                q.pop();
            q.push(r);
         
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (int y = 0; y < n; y++)
                    if (map[x][y] && match[y] != y)
                        if (d[y] == -1)
                            if (match[y] == -1) {
                                for (int i = 0; i + 1 < path[x].size(); i += 2) {
                                    match[path[x][i]] = path[x][i+1];
                                    match[path[x][i+1]] = path[x][i];
                                }
                                match[x] = y; match[y] = x;
                                return true;
                            }
                            else {
                                int z = match[y];
         
                                path[z] = path[x];
                                path[z].push_back(y);
                                path[z].push_back(z);
         
                                d[y] = 1; d[z] = 0;
                                q.push(z);
                            }
                        else if (d[y] == 0) {
                            int bi = 0;
                            while (bi < path[x].size() && bi < path[y].size() && path[x][bi] == path[y][bi])
                                bi++;
                            bi--;

                            label_one_side(x, y, bi);
                            label_one_side(y, x, bi);
                        }
            }
            return false;
        }
    public:
        int max_match;
        int n;
        bool map[N][N];
        
        void matchAll() {
            memset(match, -1, sizeof(match));
            
            max_match = 0;
            for (int i = 0; i < n; i++)
                if (match[i] == -1)
                    if (BFS(i))
                        max_match++;
                    else
                        match[i] = i;
        }
        
        void init() {
            memset(map, false, sizeof(map));
        }
        
        void addedge(int u,int v) {
            map[u][v] = map[v][u] = true;
        }
} solver;

/**
 *  Step:
 *      solver.init();
 *      solver.n = n;
 *      loop:
 *          solver.addedge(i, j);
 */
