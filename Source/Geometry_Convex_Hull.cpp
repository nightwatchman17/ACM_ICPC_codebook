bool turnLeft(const Vector &v1, const Vector &v2) {
	return fdif(cross(v1, v2)) > 0LL;
}
vector<Point> convexHull(vector<Point> &ps) {
	// return convex hull without redundant point
	sort(ps.begin(), ps.end());

	vector<Point> up;
	for(int i=0; i<ps.size(); ++i) {
		while( up.size()>1
			&& !turnLeft(up.back()-up[up.size()-2],
				ps[i]-up.back()) )
			up.pop_back();
		up.emplace_back(ps[i]);
	}

	vector<Point> btn;
	for(int i=ps.size()-1; i>=0; --i) {
		while( btn.size()>1
			&& !turnLeft(btn.back()-btn[btn.size()-2],
				ps[i]-btn.back()) )
			btn.pop_back();
		btn.emplace_back(ps[i]);
	}

	vector<Point> res(up);
	res.insert(res.end(), btn.begin()+1, btn.end());
	res.pop_back();
	return res;
}
