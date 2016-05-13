pair<double,double> findMinMaxTri(vector<Point> &ps) {
	static const double PI = acos(-1.0);
	struct Seg {
		double rad; // [, pi]
		int s1, s2;
	};

	const int n = ps.size();
	sort(ps.begin(), ps.end(), [](const Point &l, const Point &r) {
		if( fdif(l.x - r.x) == 0 )
			return l.y > r.y;
		return l.x < r.x;
	});
	vector<int> id(n+4);
	for(int i=0; i<n; ++i)
		id[i] = i;

	// sort all pair of point
	vector<Seg> segs;
	for(int i=0; i<n; ++i)
	for(int j=i+1; j<n; ++j) {
		double m = atan2(ps[j].y-ps[i].y, ps[j].x-ps[i].x) + PI;
		segs.push_back({m,i,j});
	}
	sort(segs.begin(), segs.end(), [](const Seg &l, const Seg &r) {
		return fdif(l.rad - r.rad) < 0;
	});

	// find min max triangle
	pair<double,double> ret;
	ret.first = ret.second = fabs(cross(ps[0], ps[1], ps[2]));
	for(auto seg : segs) {
		swap(ps[id[seg.s1]], ps[id[seg.s2]]);
		swap(id[seg.s1], id[seg.s2]);

		const Point &p1 = ps[id[seg.s1]];
		const Point &p2 = ps[id[seg.s2]];
		int id1 = min(id[seg.s1], id[seg.s2]);
		int id2 = max(id[seg.s1], id[seg.s2]);

		// find min triangle
		if( id1-1 >= 0 ) {
			double a = fabs(cross(p1, p2, ps[id1-1]));
			if( a < ret.first )
				ret.first = a;
		}
		if( id2+1 < n ) {
			double a = fabs(cross(p1, p2, ps[id2+1]));
			if( a < ret.first )
				ret.first = a;
		}

		// fin max triangle
		if( id1 != 0 ) {
			double a = fabs(cross(p1, p2, ps[0]));
			if( a > ret.second )
				ret.second = a;
		}
		if( id2 != n-1 ) {
			double a = fabs(cross(p1, p2, ps[n-1]));
			if( a > ret.second )
				ret.second = a;
		}
	}
	ret.first  /= 2.0;
	ret.second /= 2.0;
	return ret;
}
