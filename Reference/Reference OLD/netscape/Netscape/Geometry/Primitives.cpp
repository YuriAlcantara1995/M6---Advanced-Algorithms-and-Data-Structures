/**	1- Base element
	2- The traveling direction of the point (ccw)
	3- Intersection
	4- Distance.
	5- End point
	6- Polygon inclusion decision point
	7- Area of a polygon
	8- Perturbative deformation of the polygon
	9- triangulation
	10-Convex hull (Andrew's Monotone Chain)
	11-Convexity determination
	12-Cutting of a convex polygon
	13-Diameter of a convex polygon
	14-End point of a convex polygon
	15-Convex polygon inclusion decision point
	16-Incircle
	17-Closest Pair Point
	18-Intriangle
	19-Three Point Circle
	20-Circle_circle_intersect
	21-Tangents Point Circle
	22-Circle-Line-Intersection
	23-Centroid of a (possibly nonconvex) Polygon
	24-Point rotate **/

///----1-Base element----
struct point {
	db x, y;
	point ( db xx = 0, db yy = 0 ): x(xx), y(yy) { }
	point operator + ( const point &a ) const {
		return { x+a.x, y+a.y };
	}
	point operator - ( const point &a ) const {
		return { x-a.x, y-a.y };
	}
	point operator * ( const db &c ) const {
		return { x*c, y*c };
	}
	point operator * ( const point &p ) const {
		return { x*p.x - y*p.y, x*p.y + y*p.x };
	}
	point operator / ( const db &c ) const {
		return { x/c, y/c };
	}
	point operator / ( const point &a ) const {
        return point { x*a.x + y*a.y, y*a.x - x*a.y } / 
		/*divide 2 complejos*/( a.x*a.x + a.y*a.y );
    }
	bool operator < ( const point &a ) const {
		if ( abs( x-a.x ) > eps )
			return x+eps < a.x;
		return y+eps < a.y;
	}
};
typedef vector<point> polygon;
struct line : public vector<point> {
  line(const point &a, const point &b) {
    push_back(a); push_back(b);
  }
};
struct circle {
	point p;
	db r;
};
db cross ( const point &a, const point &b ) {
	return a.x*b.y - a.y*b.x;
}
db dot ( const point &a, const point &b ) {
	return a.x*b.x + a.y*b.y;
}
db norm ( const point &p ) {
	return dot ( p, p );
}
db abs ( const point &p ) {
	return sqrt ( norm(p) );
}
db arg ( const point &p ) {
	return atan2 ( p.y, p.x );
}
point conj ( const point &p ) {
    return point { p.x, -p.y };
}
point crosspoint(const line &l, const line &m) {
  db A = cross(l[1] - l[0], m[1] - m[0]);
  db B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A)<eps&&abs(B)<eps) return m[0];//same line
  if (abs(A)<eps)assert(false);//PRECONDITION NOT SATISFIED
  return m[0] + (m[1] - m[0])* B / A;
}

//---2-The traveling direction of the point------
int ccw(point a, point b, point c) {
  b = b-a; c = c-a;
  if (cross(b, c) > 0)return +1; // counter clockwise
  if (cross(b, c) < 0)return -1; // clockwise
  if (dot(b, c) < 0)  return +2; // c--a--b on line
  if (norm(b) < norm(c))return -2;// a--b--c on line
  return 0;
}

///----3-Intersection------
bool intersectLL(const line &l, const line &m) {
  return abs(cross(l[1]-l[0],m[1]-m[0]))>eps//non-parallel
         ||abs(cross(l[1]-l[0],m[0]-l[0]))<eps;//same line
}
bool intersectLS(const line &l, const line &s) {
  return cross(l[1]-l[0], s[0]-l[0])* // s[0] is left of l
        cross(l[1]-l[0],s[1]-l[0])<eps;//s[1] is right of l
}
bool intersectLP(const line &l, const point &p) {
  return abs(cross(l[1]-p, l[0]-p)) < eps;
}
bool intersectSS(const line &s, const line &t) {
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
         ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}
bool intersectSP(const line &s, const point &p) {
  return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0])<eps;
  //triangle inequality
}

///---4-Distance-------------
point projection(const line &l, const point &p) {
  db t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
  return l[0] + (l[0]-l[1])*t;
}
point reflection(const line &l, const point &p) {
  return p + point(2,0)*(projection(l, p) - p);
}
double distanceLP(const line &l, const point &p) {
  return abs(p - projection(l, p));
}
double distanceLL(const line &l, const line &m) {
  return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}
double distanceLS(const line &l, const line &s) {
  if (intersectLS(l, s)) return 0;
  return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
double distanceSP(const line &s, const point &p) {
  const point r = projection(s, p);
  if (intersectSP(s, r)) return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}
double distanceSS(const line &s, const line &t) {
  if (intersectSS(s, t)) return 0;
  return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
            min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}

///---5-End point----------------------------
point extreme(const polygon &G, const line &l ) {
  int k = 0;
  for (int i = 1; i < (int)G.size(); ++i)
    if (dot(G[i], l[1] - l[0]) > dot(G[k], l[1] - l[0])) 
		k = i;
  return G[k];
}

///----6-Polygon inclusion decision point----
#define curr(G, i) G[i]
#define next(G, i) G[(i+1)%G.size()]
enum { OUT, ON, IN };
int contains(const polygon &G, const point& p) {
  bool in = false;
  for (int i = 0; i < (int)G.size(); ++i) {
    point a = curr(G,i) - p, b = next(G,i) - p;
    if (a.y > b.y) swap(a, b);
    if (a.y <= 0 && 0 < b.y)
      if (cross(a, b) < 0) in = !in;
    if (cross(a, b) == 0 && dot(a, b) <= 0) return ON;
  }
  return in ? IN : OUT;
}

///----7-Area of a polygon---------------------------
double area2(const polygon& G) {
  double A = 0;
  for (int i = 0; i < (int)G.size(); ++i)
    A += cross(curr(G, i), next(G, i));
  return A;
}

///-----8-Perturbative deformation of a polygon---
#define prev(G,i) G[(i-1+G.size())%G.size()]
polygon shrink_polygon(const polygon &G, double len) {
  polygon res;
  for (int i = 0; i < (int)G.size(); ++i) {
    point a = prev(G,i), b = curr(G,i), c = next(G,i);
    point u = (b - a) / abs(b - a);
    double th = arg((c - b)/ u) * 0.5;
    res.push_back( b + u * point(-sin(th), cos(th))
				   * len / cos(th) );
  }
  return res;
}

///-----9-triangulation-----------------------------
polygon make_triangle(const point&a,const point&b,
		const point&c){
  polygon ret(3);
  ret[0] = a; ret[1] = b; ret[2] = c;
  return ret;
}
bool triangle_contains(const polygon&tri,const point&p){
  return ccw(tri[0], tri[1], p) >= 0 &&
         ccw(tri[1], tri[2], p) >= 0 &&
         ccw(tri[2], tri[0], p) >= 0;
}
bool ear_Q(int i, int j, int k, const polygon& G) {
  polygon tri = make_triangle(G[i], G[j], G[k]);
  if (ccw(tri[0], tri[1], tri[2]) <= 0) return false;
  for (int m = 0; m < (int)G.size(); ++m)
    if (m != i && m != j && m != k)
      if (triangle_contains(tri, G[m]))
        return false;
  return true;
}
void triangulate(const polygon& G, vector<polygon>& t) {
  const int n = G.size();
  vector<int> l, r;
  for (int i = 0; i < n; ++i) {
    l.push_back( (i-1+n) % n );
    r.push_back( (i+1+n) % n );
  }
  int i = n-1;
  while ((int)t.size() < n-2) {
    i = r[i];
    if (ear_Q(l[i], i, r[i], G)) {
      t.push_back(make_triangle(G[l[i]], G[i], G[r[i]]));
      l[ r[i] ] = l[i];
      r[ l[i] ] = r[i];
    }
  }
}

///---10-Convex_hull----------------------
vector<point> convex_hull(vector<point> ps) {
  int n = ps.size(), k = 0;
  sort(ps.begin(), ps.end());
  vector<point> ch(2*n);
  for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
    while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0)--k;
 for (int i = n-2,t = k+1;i>=0;ch[k++]=ps[i--])//upper-hull
    while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0)--k;
  ch.resize(k-1);
  return ch;
}

///--11-Convexity determination-------------------------
bool isconvex(const polygon &G) {
  for (int i = 0; i < (int)G.size(); ++i)
    if (ccw(prev(G, i), curr(G, i), next(G, i)) > 0) 
		return false;
  return true;
}

///---12-Cutting of a convex polygon-----------------
polygon convex_cut(const polygon& G, const line& l) {
  polygon Q;
  for (int i = 0; i < (int)G.size(); ++i) {
    point A = curr(G, i), B = next(G, i);
    if (ccw(l[0], l[1], A) != -1) Q.push_back(A);
    if (ccw(l[0], l[1], A)*ccw(l[0], l[1], B) < 0)
      Q.push_back(crosspoint(line(A, B), l));
  }
  return Q;
}

///--13-Diameter of a convex polygon-------
#define diff(G, i) (next(G, i) - curr(G, i))
double convex_diameter(const polygon &pt) {
  const int n = pt.size();
  int is = 0, js = 0;
  for (int i = 1; i < n; ++i) {
    if (pt[i].y > pt[is].y) is = i;
    if (pt[i].y < pt[js].y) js = i;
  }
  double maxd = norm(pt[is]-pt[js]);

  int i, maxi, j, maxj;
  i = maxi = is;
  j = maxj = js;
  do {
    if (cross(diff(pt,i), diff(pt,j)) >= 0) j = (j+1) % n;
    else i = (i+1) % n;
    if (norm(pt[i]-pt[j]) > maxd) {
      maxd = norm(pt[i]-pt[j]);
      maxi = i; maxj = j;
    }
  } while (i != is || j != js);
  return maxd;
}

///---14-End point of a convex polygon-----------
#define d(k) (dot(G[k], l.back() - *l.begin()))
point convex_extreme(const polygon &G, const line &l) {
  const int n = G.size();
  int a = 0, b = n;
  if (d(0) >= d(n-1) && d(0) >= d(1)) return G[0];
  while (a < b) {
    int c = (a + b) / 2;
    if (d(c) >= d(c-1) && d(c) >= d(c+1)) return G[c];
    if (d(a+1) > d(a)) {
      if (d(c+1) <= d(c) || d(a) > d(c)) b = c;
      else                               a = c;
    } else {
      if (d(c+1) > d(c) || d(a) >= d(c)) a = c;
      else                               b = c;
    }
  }

  return G[0];
}

///---15-Convex polygon inclusion decision point-------
///enum { OUT, ON, IN };
int convex_contains(const polygon &G, const point &p) {
  const int n = G.size();
  point g = (G[0] + G[n/3] + G[2*n/3]) / 3.0;//inner-point
  int a = 0, b = n;
  while (a+1 < b) { // invariant: c is in fan g-P[a]-P[b]
    int c = (a + b) / 2;
    if (cross(G[a]-g, G[c]-g) > 0) { // angle < 180 deg
      if (cross(G[a]-g, p-g) > 0 && cross(G[c]-g, p-g) < 0)
		  b = c;
      else a = c;
    } else {
      if (cross(G[a]-g, p-g) < 0 && cross(G[c]-g, p-g) > 0)
		  a = c;
      else b = c;
    }
  }
  b %= n;
  if (cross(G[a] - p, G[b] - p) < 0) return OUT;
  if (cross(G[a] - p, G[b] - p) > 0) return IN;
  return ON;
}

///--------16-Incircle-------------------------------
bool incircle(point a, point b, point c, point p) {
  a = a-p; b = b-p; c = c-p;
  return norm(a) * cross(b, c)
       + norm(b) * cross(c, a)
       + norm(c) * cross(a, b) >= 0; 
	   // < : inside, = cocircular, > outside
}

///--17-closestPair-------------------------------
pair<point,point> closestPair(polygon p) {
  int n = p.size(), s = 0, t = 1, m = 2, S[n];
  S[0] = 0, S[1] = 1;
  sort(p.begin(), p.end()); // "p < q" <=> "p.x < q.x"
  double d = norm(p[s]-p[t]);
  for (int i = 2; i < n; S[m++] = i++)
   for(int j = 0; j < m; j ++){
    if (norm(p[S[j]]-p[i])<d) 
		d = norm(p[s = S[j]]-p[t = i]);
    if (p[S[j]].x < p[i].x - d) S[j--] = S[--m];
  }
  return make_pair( p[s], p[t] );
}

///--18-Intriangle----------------
bool intriangle(point a, point b, point c, point p) {
  a = a-p; b = b-p; c = c-p;
  return cross(a, b) >= 0 &&
         cross(b, c) >= 0 &&
         cross(c, a) >= 0;
}

///----19-Three Point Circle------------------------
point three_point_circle(const point&a,const point&b,
                                       const point&c){
  point x = (b - a)/norm(b-a), y = (c - a)/norm(c-a);
  return (y-x)/(conj(x)*y - x*conj(y)) + a;
}

///--20-Circle_circle_intersect--------------------
pair<point, point> circle_circle_intersect(const point&c1,
	const double& r1, const point& c2, const double& r2) {
  point A = conj(c2-c1);
  point B = ((c2-c1)*conj(c2-c1))*-1.0 + r2*r2-r1*r1 ;
  point C = (c2-c1)*r1*r1;
  point D = B*B-A*C*4.0;

  complex <db> q ( D.x, D.y );
  q = sqrt(q);
  D = { real(q), imag(q) };
  point z1 = (B*-1.0+D)/(A*2.0)+c1, 
		z2 = (B*-1.0-D)/(A*2.0)+c1;
  return pair<point, point>(z1, z2);
}

///--21-Tangents Point Circle----------
vector<point> tangent(point p, circle c) {
    double D = abs(p - c.p);
    if (D + eps < c.r) return {};
    point t = c.p - p;
    double theta = asin( c.r / D );
    double d = cos(theta) * D;
    t = t / abs(t) * d;
    if ( abs(D - c.r) < eps ) return {p + t};
    point rot( cos(theta), sin(theta) );
    return {p + t * rot, p + t * conj(rot)};
}

///-22-Circle-Line-Intersection------------------------
vector<point> intersectLC( line l, circle c ){
    point u = l[0] - l[1], v = l[0] - c.p;
    double a = dot(u,u), b = dot(u,v), 
		   cc = dot(v,v) - c.r * c.r;
    double det = b * b - a * cc;
    if ( det < eps ) return { };
    else return { l[0] + u * (-b + sqrt(det)) / a,
                  l[0] + u * (-b - sqrt(det)) / a };
}

///-23--Centroid of a (possibly nonconvex) Polygon
point centroid(const polygon &poly) {
	point c(0, 0);
	double scale = 3.0 * area2(poly);
	for (int i = 0, n = poly.size(); i < n; ++i) {
		int j = (i+1)%n;
		c=c+(poly[i]+poly[j])*(cross(poly[i],poly[j]));
	}
	return c / scale;
}

///-24-Point rotate--------------------------
inline point rotate(point A,double ang){//respect to origin
	double r =  sqrt(dot(A , A));
	double oang = atan2(A.y , A.x);
	return (point){cos(ang + oang),sin(ang + oang)} * r;
}
