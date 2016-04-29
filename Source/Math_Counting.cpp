const int MaxNum = 1000004;
const int modNum = 1000000009;
long long fac  [MaxNum];
long long facIv[MaxNum];
void initFac(){
	fac[0] = facIv[0] = 1LL;
	for(int i=1; i<MaxNum; ++i) {
		fac  [i] = fac[i-1]*i % modNum;
		facIv[i] = modInv(fac[i], modNum);
	}
}
long long Cnm(int n, int m){
	if( m==0 || n==m ) return 1LL;
	return fac[n]*facIv[m] % modNum *facIv[n-m] % modNum;
}
long long nBlock_kColor(int n,int k){
	// n different blocks; k different colors
	// use inclusion-exclusion principle
	long long ans = fastPow(k, n, modNum);
	bool del = true;
	for(int i=k-1; i>0; --i, del=!del){
		long long now = Cnm(k, i)*fastPow(i, n, modNum) %modNum;
		if( del ) ans = (ans+modNum-now) % modNum;
		else ans = (ans+now) % modNum;
	}
	return ans;
}
