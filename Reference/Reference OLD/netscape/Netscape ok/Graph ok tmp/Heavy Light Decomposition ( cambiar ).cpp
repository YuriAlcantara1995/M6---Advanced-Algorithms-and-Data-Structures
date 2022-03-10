///Havy light decomposition
/// lv- nivel del nodo
/// cant- la cantidad de nodos
/// pos- la pos. donde aparece
/// nn- el nod en el cual aparece
/// pd- el link con el padre full superior
/// G-Dp
/// L-lazy
/// V-grafo
#define MAXN 100005
vector<int> G[MAXN], V[MAXN];
vector<bool> L[MAXN];
int cant[MAXN], pos[MAXN], nn[MAXN], pd[MAXN], lv[MAXN];
void Dfs( int nod, int pad ){
    int mej = nod;
    for( auto newn : V[nod] ){
        if( newn == pad ) continue;
        lv[newn] = lv[nod]+1;
        Dfs( newn, nod );
        if( cant[mej] < cant[nn[newn]] )
            mej = nn[newn];
    }

    pos[nod] = cant[mej];
    cant[mej] ++;
    nn[nod] = mej;
    pd[mej] = pad;
}
typedef pair<int, int> par;
typedef pair<int, par> tri;
typedef vector<tri> vt;
/// me da el recorrido desde a hasta b en vector<tri>
vt rec( int a, int b ){
	vt C1;
	C1.clear();
	while( nn[a] != nn[b] ){
      if( lv[pd[nn[a]]] < lv[pd[nn[b]]] ) swap( a, b );
      C1.push_back( tri( nn[a], par( pos[a], cant[nn[a]] - 1 ) ) );
      a = pd[nn[a]];
	}
    C1.push_back( tri( nn[a], par( min( pos[a], pos[b] ), 
                                   max( pos[a], pos[b] ) ) ) );
    return C1;
}
void havy_light( ){
    lv[1] = 1;
	Dfs( 1, 0 ); // root
	for( int i = 1; i <= N; i ++ )/// rellenar con 4*cant
		if( cant[i] ){
			G[i] = vector<int> ( cant[i]*4, 0 );
			L[i] = vector<bool> ( cant[i]*4, false );
		}
}