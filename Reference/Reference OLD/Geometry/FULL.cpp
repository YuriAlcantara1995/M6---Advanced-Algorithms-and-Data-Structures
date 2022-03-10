/**
1- Base element
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
**/
///----1-Base element----
const double EPS = 1e-8;
const double inf = 1e12;
typedef complex<double> P;
typedef vector<P> polygon;
namespace std {
  bool operator < (const P& a, const P& b) {
    return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
  }
}
double cross(const P& a, const P& b) {
  return imag(conj(a)*b);
}
double dot(const P& a, const P& b) {
  return real(conj(a)*b);
}
struct L : public vector<P> {
  L(const P &a, const P &b) {
    push_back(a); push_back(b);
  }
};
struct C {
  P p; double r;
  C(const P &p, double r) : p(p), r(r) { }
};
P crosspoint(const L &l, const L &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
  return m[0] + B / A * (m[1] - m[0]);
}
//---2-The traveling direction of the point------
int ccw(P a, P b, P c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}
///----3-Intersection------
bool intersectLL(const L &l, const L &m) {
  return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
         abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}
bool intersectLS(const L &l, const L &s) {
  return cross(l[1]-l[0], s[0]-l[0])*       // s[0] is left of l
         cross(l[1]-l[0], s[1]-l[0]) < EPS; // s[1] is right of l
}
bool intersectLP(const L &l, const P &p) {
  return abs(cross(l[1]-p, l[0]-p)) < EPS;
}
bool intersectSS(const L &s, const L &t) {
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
         ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}
bool intersectSP(const L &s, const P &p) {
  return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}
///---4-Distance-------------
P projection(const L &l, const P &p) {
  double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
  return l[0] + t*(l[0]-l[1]);
}
P reflection(const L &l, const P &p) {
  return p + P(2,0)*(projection(l, p) - p);
}
double distanceLP(const L &l, const P &p) {
  return abs(p - projection(l, p));
}
double distanceLL(const L &l, const L &m) {
  return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}
double distanceLS(const L &l, const L &s) {
  if (intersectLS(l, s)) return 0;
  return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
double distanceSP(const L &s, const P &p) {
  const P r = projection(s, p);
  if (intersectSP(s, r)) return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}
double distanceSS(const L &s, const L &t) {
  if (intersectSS(s, t)) return 0;
  return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
             min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}
///---5-End point----------------------------
#define d(G, k) (dot(G[k], l[1] - l[0]))
P extreme(const polygon &G, const L &l) {
  int k = 0;
  for (int i = 1; i < (int)G.size(); ++i)
    if (d(G, i) > d(G, k)) k = i;
  return G[k];
}
///----6-Polygon inclusion decision point----------------------------
#define curr(G, i) G[i]
#define next(G, i) G[(i+1)%G.size()]
enum { OUT, ON, IN };
int contains(const polygon &G, const P& p) {
  bool in = false;
  for (int i = 0; i < (int)G.size(); ++i) {
    P a = curr(G,i) - p, b = next(G,i) - p;
    if (imag(a) > imag(b)) swap(a, b);
    if (imag(a) <= 0 && 0 < imag(b))
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
///-----8-Perturbative deformation of a polygon-------------------------------
#define prev(G,i) G[(i-1+G.size())%G.size()]
polygon shrink_polygon(const polygon &G, double len) {
  polygon res;
  for (int i = 0; i < (int)G.size(); ++i) {
    P a = prev(G,i), b = curr(G,i), c = next(G,i);
    P u = (b - a) / abs(b - a);
    double th = arg((c - b)/ u) * 0.5;
    res.push_back( b + u * P(-sin(th), cos(th)) * len / cos(th) );
  }
  return res;
}
///-----9-triangulation-----------------------------
polygon make_triangle(const P& a, const P& b, const P& c) {
  polygon ret(3);
  ret[0] = a; ret[1] = b; ret[2] = c;
  return ret;
}
bool triangle_contains(const polygon& tri, const P& p) {
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
vector<P> convex_hull(vector<P> ps) {
  int n = ps.size(), k = 0;
  sort(ps.begin(), ps.end());
  vector<P> ch(2*n);
  for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
    while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
  for (int i = n-2, t = k+1; i >= 0; ch[k++] = ps[i--]) // upper-hull
    while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
  ch.resize(k-1);
  return ch;
}
///--11-Convexity determination--------------------------
bool isconvex(const polygon &G) {
  for (int i = 0; i < (int)G.size(); ++i)
    if (ccw(prev(G, i), curr(G, i), next(G, i)) > 0) return false;
  return true;
}
///---12-Cutting of a convex polygon----------------------------
polygon convex_cut(const polygon& G, const L& l) {
  polygon Q;
  for (int i = 0; i < (int)G.size(); ++i) {
    P A = curr(G, i), B = next(G, i);
    if (ccw(l[0], l[1], A) != -1) Q.push_back(A);
    if (ccw(l[0], l[1], A)*ccw(l[0], l[1], B) < 0)
      Q.push_back(crosspoint(L(A, B), l));
  }
  return Q;
}
//--13-Diameter of a convex polygon-------
#define diff(G, i) (next(G, i) - curr(G, i))
double convex_diameter(const polygon &pt) {
  const int n = pt.size();
  int is = 0, js = 0;
  for (int i = 1; i < n; ++i) {
    if (imag(pt[i]) > imag(pt[is])) is = i;
    if (imag(pt[i]) < imag(pt[js])) js = i;
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
  return maxd; /* farthest pair is (maxi, maxj). */
}
///---14-End point of a convex polygon---------------------------------------
P convex_extreme(const polygon &G, const L &l) {
  const int n = G.size();
  int a = 0, b = n;
  if (d(G, 0) >= d(G, n-1) && d(G, 0) >= d(G, 1)) return G[0];
  while (a < b) {
    int c = (a + b) / 2;
    if (d(G, c) >= d(G, c-1) && d(G, c) >= d(G, c+1)) return G[c];
    if (d(G, a+1) > d(G, a)) {
      if (d(G, c+1) <= d(G, c) || d(G, a) > d(G, c)) b = c;
      else                               a = c;
    } else {
      if (d(G, c+1) > d(G, c) || d(G, a) >= d(G, c)) a = c;
      else                               b = c;
    }
  }

  return G[0];
}
///---15-Convex polygon inclusion decision point------------------------------------------
enum { OUT, ON, IN };
int convex_contains(const polygon &G, const P &p) {
  const int n = G.size();
  P g = (G[0] + G[n/3] + G[2*n/3]) / 3.0; // inner-point
  int a = 0, b = n;
  while (a+1 < b) { // invariant: c is in fan g-P[a]-P[b]
    int c = (a + b) / 2;
    if (cross(G[a]-g, G[c]-g) > 0) { // angle < 180 deg
      if (cross(G[a]-g, p-g) > 0 && cross(G[c]-g, p-g) < 0) b = c;
      else                                                  a = c;
    } else {
      if (cross(G[a]-g, p-g) < 0 && cross(G[c]-g, p-g) > 0) a = c;
      else                                                  b = c;
    }
  }
  b %= n;
  if (cross(G[a] - p, G[b] - p) < 0) return OUT;
  if (cross(G[a] - p, G[b] - p) > 0) return IN;
  return ON;
}
///--------16-Incircle----------------------------------------
bool incircle(P a, P b, P c, P p) {
  a -= p; b -= p; c -= p;
  return norm(a) * cross(b, c)
       + norm(b) * cross(c, a)
       + norm(c) * cross(a, b) >= 0; // < : inside, = cocircular, > outside
}
///--17-closestPair-------------------------------
pair<P,P> closestPair(polygon p) {
  int n = p.size(), s = 0, t = 1, m = 2, S[n]; S[0] = 0, S[1] = 1;
  sort(p.begin(), p.end()); // "p < q" <=> "p.x < q.x"
  double d = norm(p[s]-p[t]);
  for (int i = 2; i < n; S[m++] = i++)
   for(int j = 0; j < m; j ++){
    if (norm(p[S[j]]-p[i])<d) d = norm(p[s = S[j]]-p[t = i]);
    if (real(p[S[j]]) < real(p[i]) - d) S[j--] = S[--m];
  }
  return make_pair( p[s], p[t] );
}
///--18-Intriangle----------------
bool intriangle(P a, P b, P c, P p) {
  a -= p; b -= p; c -= p;
  return cross(a, b) >= 0 &&
         cross(b, c) >= 0 &&
         cross(c, a) >= 0;
}
///----19-Three Point Circle--------------------------
P three_point_circle(const P& a, const P& b, const P& c) {
  P x = 1.0/conj(b - a), y = 1.0/conj(c - a);
  return (y-x)/(conj(x)*y - x*conj(y)) + a;
}
///--20-Circle_circle_intersect--------------------
pair<P, P> circle_circle_intersect( const P& c1, const double& r1, const P& c2, const double& r2) {
  P A = conj(c2-c1), B = (r2*r2-r1*r1-(c2-c1)*conj(c2-c1)), C = r1*r1*(c2-c1);
  P D = B*B-4.0*A*C;
  P z1 = (-B+sqrt(D))/(2.0*A)+c1, z2 = (-B-sqrt(D))/(2.0*A)+c1;
  return pair<P, P>(z1, z2);
}