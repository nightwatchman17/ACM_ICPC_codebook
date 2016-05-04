#include <cstring>
#include <iostream>
using namespace std;
struct KM {
	static const int N = 105, big_value = 100000000;
	int G[N][N] , visx[N] , visy[N];
	int n , labelx[N] , labely[N] , matchx[N] , matchy[N] ;
	
	KM(int n_):n(n_) {} ;
	
	bool DFS(int x) {
		visx[x] = true ;
		int y ;
		for(y=0 ; y<n ; y++)
			if(!visy[y] && labelx[x]+labely[y]==G[x][y]) {
				visy[y] = true ;
				if(matchy[y]==-1 || DFS(matchy[y])) {
					matchx[x] = y ;
					matchy[y] = x ;
					return true ;
				}
			}
		return false ;
	}
	
	int max_match() {		//Maximum Weight Perfect Bipartite Matching
		memset(labelx,0,sizeof(labelx)) ;
		memset(labely,0,sizeof(labely)) ;
		memset(matchx,-1,sizeof(matchx)) ;
		memset(matchy,-1,sizeof(matchy)) ;
		int i , x , y ;
		for(x=0 ; x<n ; x++)
			for(y=0 ; y<n ; y++)
				labelx[x] = max(labelx[x],G[x][y]) ;
		for(i=0 ; i<n ; i++) 
			while(true) {
				memset(visx,0,sizeof(visx)) ;
				memset(visy,0,sizeof(visy)) ;
				if(DFS(i)) break ;
				int d=big_value ;
				for(x=0 ; x<n ; x++) if(visx[x])
					for(y=0 ; y<n ; y++) if(!visy[y])
						d = min(d,labelx[x]+labely[y]-G[x][y]) ;
				if(d==big_value) return -1 ;	//faile to exist perfect matching
				for(int j=0 ; j<n ; j++) {
					if(visx[j]) labelx[j] -= d ;
					if(visy[j]) labely[j] += d ;
				}
			}
		int total=0 ;
		for(i=0 ; i<n ; i++)					//must be perfect!!!
			total += G[i][matchx[i]] ;
		return total ;
	}
} ;
