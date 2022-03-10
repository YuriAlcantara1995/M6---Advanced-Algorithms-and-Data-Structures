#include <cstdio>
#include <algorithm>
#define maxn 100005

using namespace std;

typedef long long ll;

int N, Q;
struct point {
 int x, y;
}P[maxn];

bool cmpx ( const point &a, const point &b ) {
 return a.x < b.x;
}

bool cmpy ( const point &a, const point &b ) {
 return a.y < b.y;
}

inline ll dist ( point a, point b ) {
 return 1ll*(a.x-b.x)*(a.x-b.x) + 1ll*(a.y-b.y)*(a.y-b.y);
}

struct kd {
 kd *h1, *h2;
 point p;
}*KD;

void init ( int ini, int fin, kd *nod, int split ) {
if ( !split )
   sort ( P+ini, P+1+fin, cmpx );
 else
   sort ( P+ini, P+1+fin, cmpy );

 int piv = ( ini+fin )>> 1;
 nod->p = P[piv];

 if ( ini < piv ) {
   nod->h1 = new kd();
   init ( ini, piv-1, nod->h1, split^1 );
  }
 if ( piv+1 <= fin ) {
   nod->h2 = new kd();
   init ( piv+1, fin, nod->h2, split^1 );
  }
}

ll best;
void query ( kd *nod, point p, int split ) {
 best = min ( best, dist ( p, nod->p ) );
 ll tmp = ( !split )? p.x - nod->p.x : p.y - nod->p.y;

 if ( tmp < 0 ) {
  if ( nod->h1 )
    query ( nod->h1, p, split^1 );
  if ( nod->h2 && tmp*tmp < best )
    query ( nod->h2, p, split^1 );
 }
 else {
  if ( nod->h2 )
    query ( nod->h2, p, split^1 );
  if ( nod->h1 && tmp*tmp < best )
    query ( nod->h1, p, split^1 );
 }
}

int main() {


 scanf ("%d%d", &N, &Q );
 for ( int i = 1; i <= N; i ++ )
   scanf ("%d%d", &P[i].x, &P[i].y );

 KD = new kd();
 init ( 1, N, KD, 0 );

 int x, y;
 while ( Q-- ) {
  scanf ("%d%d", &x, &y );
  best = 1ll << 50;
  query ( KD, point{x,y}, 0 );
  printf ("%.2f\n", 1.0*sqrt(best) );
 }

 return 0;
}