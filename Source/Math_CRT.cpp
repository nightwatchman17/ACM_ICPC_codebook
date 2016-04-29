bool china_solvable(vector<pii> &rule) {
	for(int i=0; i<rule.size(); ++i)
	for(int j=1; j<rule.size(); ++j) {
		int gcd = __gcd(rule[i].second, rule[j].second);
		if( rule[i].first%gcd != rule[j].first%gcd )
			return false;
	}
	return true;
}
long long china(const vector<pii> &rule, int nlt=0){
	// solve x = ai (mod mi)
	// rule should solvable
	long long MM = 1LL;
	for(auto &r : rule)
		MM = lcm(MM, r.second);
	long long x = 0LL;
	for(auto &r : rule){
		long long ai = r.first;
		long long mi = r.second;
		long long Mi = MM / r.second;
		long long Mv = modInv_euler(Mi%mi, mi);
		long long tmp = ai*Mi%MM *Mv %MM;
		x = (x+tmp) % MM;
	}
	if( x>=nlt ) return x;
	long long n = ceil((nlt-x)*1.0/MM);
	return x + n*MM;
}
