#include <cstring>
#include <iostream>
using namespace std;
struct KM {
	static const int N = 105;
	int visx[N], visy[N];
	int nx, ny, matchx[N], matchy[N];
	int labelx[N], labely[N], G[N][N];
	bool labeled[N];
	
	int max_match_value;
	bool isPerfect;
	
	KM(int nx_,int ny_):nx(nx_),ny(ny_) {} ;
	
	bool DFS(int x) {
		visx[x] = true ;
		int y ;
		for(int y = 0; y < ny ; y++)
			if(hasEdge(x, y) && !visy[y] && labelx[x] + labely[y] == G[x][y]	) {
				visy[y] = true ;
				if(matchy[y]==-1 || DFS(matchy[y])) {
					matchx[x] = y ;
					matchy[y] = x ;
					return true ;
				}
			}
		return false ;
	}
	
	bool max_match() {		//Maximum Weight Perfect Bipartite Matching
		isPerfect = true;
		for(int y = 0; y < ny; y++)
			labely[y] = 0;
		memset(labeled, 0, sizeof(labeled));
		memset(matchx,-1,sizeof(matchx)) ;
		memset(matchy,-1,sizeof(matchy)) ;
		for(int x = 0; x < nx ; x++)
			for(int y = 0; y < ny ; y++)
				if(hasEdge(x, y))
					if(!labeled[x]) {
						labelx[x] = G[x][y];
						labeled[x] = true;
					} else
						labelx[x] = max(labelx[x], G[x][y]) ;
		for(int i = 0; i < nx ; i++)
			while(true) {
				memset(visx, 0, sizeof(visx)) ;
				memset(visy, 0, sizeof(visy)) ;
				if(DFS(i)) break ;
				int d;
				bool flag = false;
				for(int x = 0; x < nx; x++) if(visx[x])
					for(int y = 0; y < ny; y++) if(!visy[y])
						if(hasEdge(x, y))
							if(!flag) {
								d = labelx[x] + labely[y] - G[x][y];
								flag = true;
							} else
								d = min(d, labelx[x] + labely[y] - G[x][y]) ;
				if(!flag) {
					isPerfect = false;
					break;
				}
				for(int j = 0; j < nx; j++)
					if(visx[j]) labelx[j] -= d;
				for(int j = 0; j < ny; j++)
					if(visy[j]) labely[j] += d;
			}
		int total = 0;
		for(int x = 0; x < nx; x++)					//must be perfect!!!
			if(matchx[x] != -1)
				total += G[x][matchx[x]];
		max_match_value = total;
		return isPerfect;
	}
	bool hasEdge(int u,int v) {
		//TODO
	}
};
/*******************
 * change edge data type
 * negative edge for min_match
 * initialize G[][]
 * call km.max_match()
 * check km.isPerfect
 * check km.max_match_value
 */