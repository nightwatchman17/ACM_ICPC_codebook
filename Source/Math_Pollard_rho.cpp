// need fack_mul, is_prime
ull gcd(ull a, ull b) {
	return (a%b==0)? b : gcd(b, a%b);
}
ull dif(ull a, ull b) {
	return a>b? a-b : b-a;
}
void pollard_rho(ull n, map<ull,int> &facs) {
	while( !(n&1ull) ) {
		// must extract factor 2
		int cnt = 0;
		while( !(n&1ull) )
			++cnt, n>>=1;
		facs[2] = cnt;
	}
	if( n==1ull ) return;
	if( is_prime(n) ) {
		facs[n]++;
		return;
	}
	ull x = rand()%n;
	ull y = x;
	ull a = rand()%(n-1) + 1;
	ull g = 1ull;
	while( g==1ull ) {
		x = (fake_mul(x,x,n) + a) %n;
		y = (fake_mul(y,y,n) + a) %n;
		y = (fake_mul(y,y,n) + a) %n;
		if( x==y ) {
			g = n;
			break;
		}
		g = gcd(dif(x,y), n);
	}
	if( g==n ) // unluck try again
		pollard_rho(n, facs);
	else if( g>1ull ) { // luck, found g
		pollard_rho(g, facs);
		pollard_rho(n/g, facs);
	}
}
