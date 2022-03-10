Geometria Computacional

const double EPS = 1e-8;
const double oo = 1e12;
const double PI = 3.141592653589793;
#define X real()
#define Y imag()
typedef complex<double> P;
typedef vector<P> Pol;
struct circle{
   P p; double r;
   circle(){}
   circle(P x,double rr){
      p=x, r = rr;
   }
};
struct L: public vector <P>{ //Linea
   L (P a, P b){
      push_back(a); push_back(b);
 }};
inline bool operator<(const P a, const P b){
   return a.X!=b.X ?a.X<b.X :a.Y <b.Y;
}
double cross(P a, P b){//1
   return imag(conj(a) * b);
}
double dot(P a, P b){//2
   return (conj(a)*b).X;
}
//Orientacion de 3 puntos
int ccw(P a, P b, P c){ //3,1 2
   b-=a; c-=a;
   if(cross(b,c)>0) return +1;
   if(cross(b,c)<0) return -1;
   if(dot(b,c)<0) return +2;//c-a-b line
   if(norm(b)<norm(c)) return -2;//a-b-c line
   return 0;
}
//Interseccion de 2 rectas
bool intersectLL (L l, L m){//4,1
	//non-parallel
   return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS
	   || abs(cross(l[1]-l[0], m[0]-l[0])) < EPS; 
} //same-line

//Punto interseccion recta recta
P crosspoint(L l, L m){ //5,1
   double A = cross( l[1]-l[0], m[1]-m[0]);
   double B = cross( l[1]-l[0], l[1]-m[0]);
   if(abs(A)<EPS && abs(B)<EPS) 
      return m[0]; //Same line
   if(abs(A)<EPS) return P(0,0);//parallels
   return m[0] + B / A * (m [1] - m [0]);
}
//Interseccion recta y segmento
bool intersectLS (L l, L s){//6, 1
	//s[0] is left of l
   return cross(l[1]-l[0], s[0]-l[0]) * 
      cross(l[1]-l[0],s[1]-l[0])<EPS;  
} //s[1] is right of l

//Interseccion recta y punto
bool intersectLP (L l, P p){//7,1
   return abs(cross(l[1]-p, l[0]-p))<EPS;
}
//Interseccion de 2 segmento
bool intersectSS (L s, L t){//8,3
   FOR(i,2)FOR(j,2) if(abs(s[i]-t[j])<EPS)
      return 1;  // same point
 return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1])<=0
    && ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1])<=0;
}

//Interseccion segmento y punto
bool intersectSP (L s,P p){//9
   double a=abs(s[0]-p)+abs(s[1]-p);
   return a-abs(s[1]-s[0])<EPS; 
}
//Interseccion circulo circulo
pair<P, P> intersectCC(circle a,circle b) {
   P x= b.p - a.p;
   P A= conj(x), C = a.r*a.r*(x); 
   P B= (b.r*b.r-a.r*a.r-(x)*conj(x));
   P D= B*B-4.0*A*C;
   P z1= (-B+sqrt(D)) / (2.0*A) +a.p; 
   P z2= (-B-sqrt(D)) / (2.0*A) +a.p;
   return pair<P, P>(z1, z2);
}
//Proyeccion punto recta
P projection(L l,P p){//10,2
  double t=dot(p-l[0], l[0]-l[1])/norm(l[0]-l[1]);
  return l[0] + t*(l[0]-l[1]);
}

//Refleccion punto recta
P reflection(L l, P p){//11, 10
   return p +(P(2,0) *(projection(l,p)-p));
}

//Distancia recta punto
double distanceLP(L l,P p){//12, 10
   return abs(p - projection(l,p));
}

//Distancia recta recta
double distanceLL(L a, L b){//13,4 12
   if(intersectLL(a,b)) return 0;
   return distanceLP(a,b[0]);
}
//Distancia recta segmento
double distanceLS(L l, L s){//14,7 12
  if(intersectLS(l,s)) return 0;
  return min(distanceLP(l,s[0]),distanceLP(l,s[1]));
}

//Distancia segmento punto
double distanceSP(L s, P p){//15, 10 9
   const P r = projection(s,p);
   if (intersectSP(s,r)) return abs(r-p);
   return min( abs(s[0]-p), abs(s[1]-p) );
}

//distancia segmento segmento
double distanceSS (L s, L t) {//16,8 15
   if (intersectSS(s, t)) return 0;
   double a=oo,b=oo;
   FOR(i,2) a=min(a, distanceSP(s,t[i]));
   FOR(i,2) b=min(b, distanceSP(t,s[i]));
   return min(a,b);
}

//Centro de circunferencia dado 3 puntos
P circunferenceCenter(P a, P b, P c){//17 
   P x =1.0/conj(b-a), y=1.0/conj(c-a);
   return (y-x)/(conj(x)*y-x*conj(y)) +a;
}
double anguloEjeX(P a){//18,1 2
   P b = P(1,0);
   if(dot(b,a)/(abs(a)*abs(b))==1) return 0;
   if(dot(b,a)/(abs(a)*abs(b))==-1) return PI;
   double aux=asin(cross(b,a)/(abs(a)*abs(b)));
   if(a.X<0 && a.Y>0) aux+=PI/2;
   if(a.X<0 && a.Y<0) aux-=PI/2;
   if(aux<0) aux += 2*PI;
   return aux;
}

double anguloEntreVectores(P a, P b){//19,18
   double aa = anguloEjeX(a);
   double bb = anguloEjeX(b);
   double r = bb - aa;
   if (r<0) r+=2*PI;
   return r;
}

double anguloEntre3Puntos(P a, P b, P c){//20,19
   a-=b; c-=b;
   return anguloEntreVectores(a,b);
}

Pol convexHull(Pol ps){//21,3
  int t,i,n = ps.size(), k=0;
  if (n < 3) return ps; 
  sort(ps.begin(), ps.end());
  Pol ch (2*n);
  for(i=0;i<n;ch[k++]=ps[i++]) //lower
  while(k>=2 && ccw(ch[k-2],ch[k-1],ps[i])<=0) --k;
  for(i=n-2,t=k+1 ;i>=0; ch[k++]=ps[i--])// upper
 while(k>=t && ccw(ch[k-2],ch[k-1], ps[i])<=0) --k;
  ch.resize(k-1);
  return ch;
}
 
int pointInPolygon(Pol pol, P p){//22, 1 2
   bool in = false; int n=pol.size();
   FOR(i,n){
      P a= pol[i] - p, b= pol[(i+1)%n]-p;
        if(a.Y > b.Y) swap(a,b);
        if(a.Y<=0 && 0 < b.Y)
          if (cross(a,b)<0) in = !in;
          if(abs(cross(a,b))<=EPS &&dot(a,b)<=0) 
		return true; // ON
   }
   return in; // IN | OUT
}
pair <P,P> closestPair (Pol p) {//23
   int i,n = p.size(), s=0, t=1, m=2;
   vector<int> S(n);  S[0]=0, S[1]=1;
   sort(p.begin(), p.end());
   double d = norm(p[s]-p[t]);
   for(i =2;i<n; S[m++]=i++)
      FOR(j,m){
         if(norm(p[S[j]]-p[i])<d) 
            d=norm(p[s=S[j]]-p[t = i]);
         if(p[S[j]].X < p[i].X-d) 
            S[j--] = S[--m];
   }
   return make_pair( p[s], p[t] );
}

//max distance pair points, O(n)
double diameter(Pol pt) {//24, 1 
   int is=0,js=0, n=pt.size();
   FAB(i,1,n){
      if(pt[i].Y >pt[is].Y) is=i;
      if(pt[i].Y <pt[js].Y) js=i;
   }
   double maxd=norm(pt[is]-pt[js]);
   int i,maxi,j,maxj;
   i = maxi = is;  j = maxj = js;
   do {
     if(cross(pt[(i+1)%n]-pt[i],
             pt[(j+1)%n]-pt[j])>=0) 
       j=(j+1)%n; else i=(i+1)%n;
      if (norm(pt[i]-pt[j])>maxd){
         maxd =norm(pt[i]-pt[j]);
         maxi=i; maxj=j;
  } }while(i!=is || j!=js);
   return maxd;
}
double area(Pol pol) {//25, 1
   double A=0; int n=pol.size();
   FOR(i,n)
      A+=cross(pol[i],pol[(i+1)%n]);
   return A/2;
}
Minimal Enclosing Circle

double distSqr(P &p1, P &p2){
   return (p1.X-p2.X)*(p1.X-p2.X) + 
          (p1.Y-p2.Y)*(p1.Y-p2.Y);
}
bool contain(circle c,P p){
   return distSqr(c.p,p)<= c.r*c.r;
}
circle findCircle(P a,P b){
   P p( real(a+b)/2.0 , imag(a+b)/2.0);
   return circle( p, sqrt(distSqr(a,p)));
}
circle findCircle(P pa,P pb,P pc) {
   double a,b,c,x,y,r,d;
   c = sqrt(distSqr(pa , pb));
   b = sqrt(distSqr(pa , pc));
   a = sqrt(distSqr(pb , pc));
   if (b==0 || c==0 || a*a>= b*b+c*c)
      return findCircle(pb,pc);
   if (b*b >= a*a+c*c)
      return findCircle(pa,pc);
   if (c*c >= a*a+b*b)
      return findCircle(pa,pb);
   d = real(pb-pa)*imag(pc-pa);
   d = 2 * (d - imag(pb-pa)*real(pc-pa));
   x = (imag(pc-pa)*c*c-imag(pb-pa)*b*b)/d;
   y = (real(pb-pa)*b*b-real(pc-pa)*c*c)/d;
   x += real(pa), y += imag(pa);
   r= sqrt(pow(real(pa)-x,2)+ pow(imag(pa)-y,2));
   return circle(P(x,y),r);
}

P points[MAXN], R[3];
circle sed(int n,int nr){
   circle c;
   if(nr == 3)
      c = findCircle(R[0],R[1],R[2]);
   else if (n == 0 && nr==2)
      c = findCircle(R[0], R[1]);
   else if(n==1 && nr == 0)
      c = circle(points[0],0);
   else if(n == 1 && nr == 1)
      c = findCircle(R[0],points[0]);
   else{
      c = sed(n-1, nr);
      if(!contain(c,points[n-1])){
         R[nr++] = (points[n-1]);
         c = sed(n-1, nr);
      }
   }
   return c;
}
