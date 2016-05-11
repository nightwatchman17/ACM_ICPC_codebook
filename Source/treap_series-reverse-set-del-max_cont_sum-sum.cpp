#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cstring>
using namespace std;
const int oo = 1e9 ;
struct node {
	int v , p , sz ;
	int sum , presum , sufsum , maxsum , flag , set ;
	node *l , *r ;
	node(){ }
	node(int v_):p(rand()),sz(1),l(NULL),r(NULL) {
		v = sum = presum = sufsum = maxsum = v_ ;
		flag = 0 ;
		set = oo ;
	}
	int size() { return this ? sz : 0 ; }
	int Sum() { return this ? sum : 0 ; }
	int Presum() { return this ? (!flag ? presum : sufsum) : -oo ; }
	int Sufsum() { return this ? (!flag ? sufsum : presum) : -oo ; }
	int Maxsum() { return this ? maxsum : -oo ; }
	int max(int a,int b) { return a > b ? a : b ; }
	int max(int a,int b,int c) { return max(a,max(b,c)) ; }
	void makesame(int st) {
		if(this) {
			set = st ;
			sum = st*sz ;
			presum = sufsum = maxsum = (st <= 0 ? st : sum) ;
		}
	}
	void pushdown() {
		if(flag) {
			if(l) l->flag = !l->flag ;
			if(r) r->flag = !r->flag ;
			swap(l,r) ;
			swap(presum,sufsum) ;
			flag = 0 ;
		}
		if(set!=oo) {
			v = set ;
			l->makesame(set) ;
			r->makesame(set) ;
			set = oo ;
		}
	}
	void maintain() {
		presum = max(l->Presum(), l->Sum() + v, l->Sum() + v + r->Presum()) ;
		sufsum = max(r->Sufsum(), r->Sum() + v, r->Sum() + v + l->Sufsum()) ;
		int maxsum1 = max(l->Maxsum(), r->Maxsum(), v) ;
		int maxsum2 = max(l->Sufsum() + v, r->Presum() + v, l->Sufsum() + v + r->Presum()) ;
		maxsum = max(maxsum1, maxsum2) ;
		sum = l->Sum() + r->Sum() + v ;
		sz = 1 + l->size() + r->size() ;
	}
} ;
void splite(node *t,node* &a,node* &b,int k) {
	if(t == NULL) {
		a = b = NULL ;
		return ;
	}
	t->pushdown() ;
	if(t->l->size()+1 <= k) {
		a = t ;
		splite(t->r, a->r, b, k-(t->l->size()+1)) ;
		a->maintain() ;
	} else {
		b = t ;
		splite(t->l,a,b->l,k) ;
		b->maintain() ;
	}
}
node* merge(node *a,node *b) {
	if(!a || !b)
		return a ? a : b ;
	if(a->p > b->p) {
		a->pushdown() ;
		a->r = merge(a->r,b) ;
		a->maintain() ;
		return a ;
	} else {
		b->pushdown() ;
		b->l = merge(a,b->l) ;
		b->maintain() ;
		return b ;
	}
}
void Delete(node *t) {
	if(!t) return ;
	Delete(t->l) ;
	Delete(t->r) ;
	delete t ;
}
void INSERT(node* &root) {
	int p , k , v ;
	node *t=0 , *L, *R; 
	scanf("%d%d",&p,&k) ;
	for(int i=0 ; i<k ; i++) {
		scanf("%d",&v) ;
		t = merge(t,new node(v)) ;
	}
	splite(root, L, R, p) ;
	root = merge(L, merge(t, R)) ;
}
void DELETE(node* &root) {
	int p , k ;
	scanf("%d%d",&p,&k) ;
	node *L, *M, *R;
	splite(root, L, R, p-1) ;
	splite(R, M, R, k) ;
	Delete(M) ;
	root = merge(L, R) ;
}
void MAKE_SAME(node* &root) {
	int p , k , l ;
	scanf("%d%d%d",&p,&k,&l) ;
	node *L, *M, *R ;
	splite(root, L, R, p-1) ;
	splite(R, M, R, k) ;
	M->makesame(l) ;
	root = merge(L, merge(M, R)) ; 
}
void REVERSE(node* &root) {
	int p , k ;
	scanf("%d%d",&p,&k) ;
	node *L, *M, *R ;
	splite(root, L, R, p-1) ;
	splite(R, M, R, k) ;
	M->flag = !M->flag ;
	root = merge(L, merge(M, R)) ;
}
int GET_SUM(node* &root) {
	int p , k , v ;
	scanf("%d%d",&p,&k) ;
	node *L, *M, *R ;
	splite(root, L, R, p-1) ;
	splite(R, M, R, k) ;
	v = M->Sum() ;
	root = merge(L, merge(M, R)) ;
	return v ;
}
int MAX_SUM(node* &root) {
	return root->Maxsum() ;
}
int main () {
	int n, m ;
	srand(860514) ;
	while(scanf("%d%d",&n,&m)==2) {
		node *root=0 ;
		for(int i=0,v ; i<n ; i++) {
			scanf("%d",&v) ;
			root = merge(root,new node(v)) ;
		}
		while(m--) {
			char s[10] ;
			scanf("%s",s) ;
			if(strcmp(s,"INSERT")==0) {
				INSERT(root) ;
				continue ;
			}
			if(strcmp(s,"DELETE")==0) {
				DELETE(root) ;
				continue ;
			}
			if(strcmp(s,"MAKE-SAME")==0) {
				MAKE_SAME(root) ;
				continue ;
			}
			if(strcmp(s,"REVERSE")==0) {
				REVERSE(root) ;
				continue ;
			}
			if(strcmp(s,"GET-SUM")==0) {
				printf("%d\n",GET_SUM(root)) ;
				continue ;
			}
			if(strcmp(s,"MAX-SUM")==0) {
				printf("%d\n",MAX_SUM(root)) ;
				continue ;
			}
		}
	}
}
