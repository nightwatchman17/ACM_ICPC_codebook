#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

struct BlossomAlgorithm {
	private:
		static const int N = 205;	// number of vertex, zero base
		int match[N];				// 記錄各點所配對的點，值為-1為未匹配點
		int d[N];					// 值為-1未拜訪、0偶點、1奇點
		queue<int> q;				// queue，只放入偶點
		deque<int> path[N];			// p[x]記錄了樹根到x點的交錯路徑。
		
		// 設定好由樹根至花上各個奇點的交錯路徑，並讓奇點變成偶點。
		// 只處理花的其中一邊。
		// 邊xy是cross edge。bi是花托的索引值。
		void label_one_side(int x, int y, int bi) {
			for (int i = bi+1; i < path[x].size(); i++) {
				int z = path[x][i];
				if (d[z] == 1) {	// 設定好由樹根至花上奇點的交錯路徑。會經過cross edge。
					path[z] = path[y];
					path[z].insert(path[z].end(), path[x].rbegin(), path[x].rend()-i);
					d[z] = 0;		// 花上的奇點變偶點
					q.push(z);		// 將來可以延伸出交錯路徑
				}
			}
		}
		
		// 給定一個未匹配點r，建立交錯樹。
		bool BFS(int r) {
			for (int i = 0; i < n; ++i)
				path[i].clear();
			path[r].push_back(r);                  // 交錯樹樹根
		 
			memset(d, -1, sizeof(d));
			d[r] = 0;                           // 樹根是偶點

			while(!q.empty())
				q.pop();
			q.push(r);                          // 樹根放入queue
		 
			while (!q.empty()) {
				int x = q.front();
				q.pop();
				for (int y = 0; y < n; y++)
					if (map[x][y] && match[y] != y) // 有鄰點，點存在。
						if (d[y] == -1)         // 沒遇過的點
							if (match[y] == -1) {     // 發現擴充路徑
								for (int i = 0; i + 1 < path[x].size(); i += 2) {
									match[path[x][i]] = path[x][i+1];
									match[path[x][i+1]] = path[x][i];
								}
								match[x] = y; match[y] = x;
								return true;
							} else {                // 延伸交錯樹
								int z = match[y];
		 
								path[z] = path[x];
								path[z].push_back(y);
								path[z].push_back(z);
		 
								d[y] = 1; d[z] = 0;
								q.push(z);
							}
						else if (d[y] == 0) {		// 形成花
							int bi = 0;
							while (bi < path[x].size() && bi < path[y].size() && path[x][bi] == path[y][bi])
								bi++;	// LCA
							bi--;

							// 兩條路徑分開標記 不必擔心x與y在同一朵花上
							label_one_side(x, y, bi);
							label_one_side(y, x, bi);
						}
			}
			return false;
		}
	public:
		int max_match;
		int n;						// nodes
		bool map[N][N];				// adjacency matrix
		
		void matchAll() {
			memset(match, -1, sizeof(match));
			
			max_match = 0;
			for (int i = 0; i < n; i++)
				if (match[i] == -1)
					if (BFS(i))
						max_match++;        // 找到擴充路徑，增加匹配數
					else
						match[i] = i;   // 從圖上刪除此點
		}
		
		void init() {
			memset(map, false, sizeof(map));
		}
		
		void addedge(int u,int v) {
			map[u][v] = map[v][u] = true;
		}
} solver ;

/**
 *	Step:
 *		solver.init();
 *		solver.n = n;
 *		loop:
 *			solver.addedge(i, j);
 */