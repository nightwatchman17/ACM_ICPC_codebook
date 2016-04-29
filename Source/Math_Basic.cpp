vector<pii> primeFac(int n) {
	vector<pii> ret;
	for(int i=2; n>1; ++i){
		if( n%i != 0 ) continue;
		int e = 0;
		while( n%i == 0 ) ++e , n/=i;
		ret.push_back({i, e});
	}
	return ret;
}
long long fastPow(long long x, int n, long long m){
	long long ans = 1LL;
	while( n ){
		if( n&1 ) ans = ans * x % m;
		x = x*x % m;
		n >>= 1;
	}
	return ans;
}
long long modInv(long long x, long long p){
	return fastPow(x, p-2, p);
}
long long modInv_euler(long long x, long long m){
	// must be gcd(x,m)==1
	// phi is euler function: O(sqrt(x))
	return fastPow(x, phi(m)-1, m);
}
