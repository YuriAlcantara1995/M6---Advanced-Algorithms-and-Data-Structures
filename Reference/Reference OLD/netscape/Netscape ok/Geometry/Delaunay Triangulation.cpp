/*Incremental Randomized Expected O(NlogN)*/
int n;
point P[maxn];
struct edge {
    int t;
    int side;
    edge ( ) { t = -1, side = 0; }
    edge ( int tt, int s ) { t = tt, side = s; }
};
struct triangle {
    point p[3];
    edge e[3];
    int child[3];
    triangle () {}
    triangle(const point&p0,const point&p1,const point&p2){
        p[0] = p0, p[1] = p1, p[2] = p2;
        child[0] = child[1] = child[2] = 0;
    }
    bool inside(const point &pp) const {
        point a = p[0]-pp, b = p[1]-pp, c = p[2]-pp;
        return cross(a, b) >= 0 &&
         cross(b, c) >= 0 &&
         cross(c, a) >= 0;
    }
};
triangle T[maxn*3];
int ct;
bool is_leaf ( int t ) {
    return !T[t].child[0]&&!T[t].child[1]&&!T[t].child[2];
}
void add_edge ( edge a, edge b ) {
    if ( a.t != -1 ) T[a.t].e[a.side] = b;
    if ( b.t != -1 ) T[b.t].e[b.side] = a;
}
struct Triangulation {
    Triangulation ( ) {
        int M = 1e5 * 3;//multiplicar el maximo valor por 3
        T[0]=triangle(point(-M,-M),point(M,-M),point(0,M));
        ct = 1;
    }
    int find ( int t, const point &p ) {
        while ( !is_leaf(t) ) {
          for ( int i = 0; i < 3; i ++ )
            if (T[t].child[i]&&T[T[t].child[i]].inside(p)){
              t = T[t].child[i];
              break;
            }
        }
        return t;
    }
    void add_point ( const point &p ) {
        int t = find ( 0, p ), tab, tbc, tca;
        tab = ct;
        T[ct++] = triangle ( T[t].p[0], T[t].p[1], p );
        tbc = ct;
        T[ct++] = triangle ( T[t].p[1], T[t].p[2], p );
        tca = ct;
        T[ct++] = triangle ( T[t].p[2], T[t].p[0], p );
        add_edge ( {tab,0}, {tbc,1} );
        add_edge ( {tbc,0}, {tca,1} );
        add_edge ( {tca,0}, {tab,1} );
        add_edge ( {tab,2}, T[t].e[2] );
        add_edge ( {tbc,2}, T[t].e[0] );
        add_edge ( {tca,2}, T[t].e[1] );
        T[t].child[0] = tab;
        T[t].child[1] = tbc;
        T[t].child[2] = tca;
        flip ( tab, 2 );
        flip ( tbc, 2 );
        flip ( tca, 2 );
    }
    void flip ( int ti, int pi ) {
        int tj = T[ti].e[pi].t;
        int pj = T[ti].e[pi].side;
        if ( tj == -1 ) return;
		if (!incircle(T[ti].p[0],T[ti].p[1],
					  T[ti].p[2],T[tj].p[pj]))
			return;
        int tk = ct;
        T[ct++]=triangle(T[ti].p[(pi+1)%3],
				         T[tj].p[pj],T[ti].p[pi]);
        int tl = ct;
        T[ct++] = triangle ( T[tj].p[(pj+1)%3],
							 T[ti].p[pi], T[tj].p[pj] );
        add_edge ( {tk,0}, {tl,0} );
        add_edge ( {tk,1}, T[ti].e[(pi+2)%3] );
		add_edge ( {tk,2}, T[tj].e[(pj+1)%3] );
		add_edge ( {tl,1}, T[tj].e[(pj+2)%3] );
		add_edge ( {tl,2}, T[ti].e[(pi+1)%3] );
        T[ti].child[0] = tk, T[ti].child[1] = tl,
		T[ti].child[2] = 0;
        T[tj].child[0] = tk, T[tj].child[1] = tl,
		T[tj].child[2] = 0;
        flip ( tk, 1 );
        flip ( tk, 2 );
        flip ( tl, 1 );
        flip ( tl, 2 );
    }
} delaunay;
void triangulate ( ) {
    delaunay = Triangulation();
    random_shuffle ( P+1, P+1+n );
    for ( int i = 1; i <= n; i ++ )
        delaunay.add_point ( P[i] );
}