pll recur(long long n, long long m) {
	// solve one integer solution of 
	// x*n + y*m = gcd(n,m)
	if( n%m == 0 )
		return {0LL, 1LL};
	pll res = recur(m, n%m);
	pll ret = {res.second, res.first - res.second * (n/m)};
	return ret;
}
