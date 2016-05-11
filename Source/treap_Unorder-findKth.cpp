struct node {
	int v , p , sz ;
	node *l , *r ;
	node() { l = r = NULL ;} 
	node(int v_):v(v_),p(rand()),sz(1) {l = r = 0;}
	int size() {
		return this!=NULL ? this->sz : 0 ;
	}
	void maintain() {
		sz = l->size() + r->size() + 1 ;
	}
} ;
void splite_v(node *t,node* &a,node* &b,int v) {
	if(!t)
		a = b = NULL ;
	else if(v >= t->v) {
		a = t ;
		splite_v(t->r,a->r,b,v) ;
		a->maintain() ;
	} else if(v < t->v) {
		b = t ;
		splite_v(t->l,a,b->l,v) ;
		b->maintain() ;
	}
}
node* merge(node *a,node *b) {
	if(a==NULL || b==NULL)
		return a!=NULL ? a : b;
	if(a->p > b->p) {
		a->r = merge(a->r,b) ;
		a->maintain() ;
		return a ;
	} else if(a->p <= b->p) {
		b->l = merge(a,b->l) ;
		b->maintain() ;
		return b ;
	}
}
int kth(node *t,int k) {
	if(k<=t->l->size())
		return kth(t->l,k) ;
	else if(k>t->l->size()+1)
		return kth(t->r,k-t->l->size()-1) ;
	return t->v ;
}
void release(node *t) {
	if(t) {
		release(t->l) ;
		release(t->r) ;
		delete t ;
	}
}
