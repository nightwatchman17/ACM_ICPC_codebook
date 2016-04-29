struct Point{
	double x,y;
	Point(double xi=0.0,double yi=0.0){
		x = xi , y = yi;  
	}
	Point operator - (const Point &r)const{
		return Point(x-r.x , y-r.y);
	}
};
typedef Point Vector;

double angle(const Vector &v,const Vector &u){
	// return rad [0, pi] of two vector 
	return acos( dot(v,u)/len(v)/len(u) );
}
Vector rotate(const Vector &v,double rad){
	return Vector(
		v.x*cos(rad) - v.y*sin(rad),
		v.x*sin(rad) + v.y*cos(rad)
	);
}
double pointSegLen(const Point &A,const Point &B,const Point &Q){
	if(A==B) return len(Q-A);
	if( dot(B-A , Q-A)<0 ) return len(Q-A);
	if( dot(B-A , Q-B)>0 ) return len(Q-B);
	return fabs( cross(B-A , Q-A) ) / len(B-A);
}
bool pointOnSeg(const Point &A,const Point &B,const Point &Q){
	return fabs( len(Q-B)+len(Q-A)-len(A-B) ) < 1e-9;
}

struct Line{
	Point P0;
	Vector v;
	Line(const Point &pi,const Vector &vi):p0(pi) , v(vi) {}
};

double pointLineLen(const Line &L,const Point &Q){
	return fabs( cross(L.v , Q-L.P0) ) / len(L.v);
}
Point projectToLine(const Line &L,const Point &Q){
	double t = dot(Q-L.P0 , L.v) / dot(L.v , L.v);
	return L.P0 + L.v * t;
}

Point innerCircle(point &p1, point &p2, point &p3){
	// p1,p2,p3 should not on same line
	double a1 = (-2*p1.x + 2*p2.x);
	double b1 = (-2*p1.y + 2*p2.y);
	double c1 = (p2.x*p2.x + p2.y*p2.y - p1.x*p1.x - p1.y*p1.y);
	double a2 = (-2*p1.x + 2*p3.x);
	double b2 = (-2*p1.y + 2*p3.y);
	double c2 = (p3.x*p3.x + p3.y*p3.y - p1.x*p1.x - p1.y*p1.y);
	double cx = (c1*b2-c2*b1) / (a1*b2-a2*b1);
	double cy = (a1*c2-a2*c1) / (a1*b2-a2*b1);
	return Point(cx, cy);
}
Point outerCircle(point &p1, point &p2, point &p3) {
	// p1,p2,p3 should not on same line
	double x1 = (p1.x+p2.x)/2.0;
	double y1 = (p1.y+p2.y)/2.0;
	double x2 = (p2.x+p3.x)/2.0;
	double y2 = (p2.y+p3.y)/2.0;
	double vx = p2.x-p1.x;
	double vy = p2.y-p1.y;
	double ux = p3.x-p2.x;
	double uy = p3.y-p2.y;
	double A  = vx*x1 + vy*y1;
	double B  = ux*x2 + uy*y2;
	double cx = (uy*A - vy*B) / (uy*vx - ux*vy);
	double cy = (ux*A - vx*B) / (ux*vy - uy*vx);
	return Point(cx, cy);
}

