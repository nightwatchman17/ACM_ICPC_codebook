struct Circle {
	Point c;
	double R2; // square of radius
	Circle() {}
	Circle(const Point &p1, const Point &p2) {
		c.x = (p1.x+p2.x)/2.0;
		c.y = (p1.y+p2.y)/2.0;
		R2 = dot(p1-p2, p1-p2)/4.0;
	}
	Circle(const Point &p1, const Point &p2, const Point &p3) {
		// p1, p2, p3 should not on same line
		c = outerCircle(p1, p2, p3);
		double dx = p1.x - c.x;
		double dy = p1.y - c.y;
		R2 = dx*dx + dy*dy;
	}
	bool contain(const Point &p) const {
		double dx = c.x - p.x;
		double dy = c.y - p.y;
		return fdif(dx*dx + dy*dy - R2)<=0;
	}
};

Circle minEncloseDisk(vector<Point> &ps) {
	// Find minimal circal enclose all point
	// worst case O(n^3), expected O(n)
	Circle D;
	if( ps.size()==0 ) return D;
	if( ps.size()==1 ) {
		D.c  = ps[0];
		D.R2 = 0.0;
		return D;
	}

	random_shuffle(ps.begin(), ps.end());
	D = Circle(ps[0], ps[1]);
	for(int i=2; i<ps.size(); ++i) {
		if( D.contain(ps[i]) )
			continue;
		D = Circle(ps[i], ps[0]);
		for(int j=1; j<i; ++j) {
			if( D.contain(ps[j]) )
				continue;
			D = Circle(ps[i], ps[j]);
			for(int k=0; k<j; ++k) {
				if( D.contain(ps[k]) )
					continue;
				D = Circle(ps[i], ps[j], ps[k]);
			}
		}
	}
}
