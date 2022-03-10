/// O( (N+I)log(N+I))
/// I-> cantidad de intersecciones
int n; db X;
struct segment {
    line l;
    db m, n;
}s[maxn];
struct event {
    point p;
    /// 1->inicio segmento, -1->fin segmento, 
    /// 0->interseccion
    int tip, id, a, b;
    /// a y b son los segmentos q se cortan
    bool operator < ( const event &e ) const {
        if ( p != e.p )
            return p < e.p;
        return (tip==0);
    }
};
multiset <event> e;
struct status {
    int id;
    db get_Y ( ) const {
        return s[id].m * X + s[id].n;
    }
    bool operator < ( const status &a ) const {
        return get_Y ( ) + eps < a.get_Y ( );
    }
};
multiset <status> st;
int sol = 0;
set <par> mark;
void intersectar ( auto it, auto it1 ) {
    if ( it->id == it1->id || 
		mark.count( par ( it->id, it1->id ) ) )
        return;
    if ( intersectSS ( s[it->id].l, s[it1->id].l ) ) {
        point p = crosspoint ( s[it->id].l, s[it1->id].l );
        if ( X-eps <= p.x ) {
            sol ++;
            e.insert ( event { p, 0, 0, it->id, it1->id } );
            mark.insert ( par ( it->id, it1->id ) );
            mark.insert ( par ( it1->id, it->id ) );
        }
    }
}
void insertar ( event i, bool band ) {
    if ( band ) X += eps*2.0;
    st.insert ( status { i.id } );
    auto it = st.find ( status { i.id } );
    if ( band ) X -= eps*2.0;
    if ( it != st.begin() ) {
        auto it1 = it;
        it1--;
        intersectar ( it, it1 );
    }
    auto it1 = it;
    it1++;
    if ( it1 != st.end() )  intersectar ( it, it1 );
}
void eliminar ( event i ) {
    auto it = st.find ( status { i.id } );
    auto it1 = it, it2 = it;
    it1--, it2++;
    if ( it != st.begin() && it2 != st.end() )
        intersectar ( it1, it2 );
    st.erase ( it );
}
void cruzar ( event i ) {
    st.erase ( status { i.a } );
    st.erase ( status { i.b } );
    event tmp;
    tmp.id  = i.a;
    insertar ( tmp, true );
    tmp.id = i.b;
    insertar ( tmp, true );
}
void clear ( ) {
    sol = 0;
    e.clear(), st.clear(), mark.clear();
}
int main() { 
	cin >> n;
	point a, b;
	for ( int i = 1; i <= n; i ++ ) {
		cin >> a.x >> a.y >> b.x >> b.y;
		a = rotate ( a, eps*5.0 );
		b = rotate ( b, eps*5.0 );
		if ( b < a ) swap ( a, b );
		s[i].l = line ( a, b );
		s[i].m = (a.y-b.y)/(a.x-b.x);
		s[i].n = a.y - s[i].m*a.x;
		e.insert ( event { a, 1, i, 0, 0 } );
		e.insert ( event { b, -1, i, 0, 0 } );
	}
	while ( !e.empty() ) {
		event i = (*e.begin());
		e.erase ( e.begin() );
		X = i.p.x;
		if ( i.tip == 1 ) insertar ( i, false );
		if ( i.tip == -1 ) eliminar ( i );
		if ( i.tip == 0 ) cruzar ( i );
	}
	cout << sol;
	clear ( );
}