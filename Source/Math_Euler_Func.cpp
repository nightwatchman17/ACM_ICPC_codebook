int phi(int n){
	// euler function: in [0,n], # of coprime(i, n)
	vector<pii> fac = primeFac(n);
	int num = 1 , m = 1;
	for(auto &p : fac)
		num *= (p.first-1) , m *= p.first;
	return n/m * num;
}
