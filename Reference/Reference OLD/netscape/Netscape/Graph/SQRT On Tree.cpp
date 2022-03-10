void Dfs( int nod, int pad ){
	P[nod] = pad;
	if( lv[nod] % 2 ) G[nod] = ++k;
	for( auto i : V[nod] ){
		if( pad == i ) continue;
		lv[i] = lv[nod]+1;
		Dfs( i, nod );
	}
	if( lv[nod] % 2 == 0 ) G[nod] = ++k;
}
struct r{ int f, s, id; } Q[MAXA]; // f <= s
int R, kk;
bool comp ( const r s1, const r s2 ){
	if( G[s1.f] / R != G[s2.f] / R )
		return G[s1.f] / R < G[s2.f] / R;
	return G[s1.s] < G[s2.s];
}
void mov( int x, int y ){
    int p, cant = 0;
     while( x != y ){
        kk ++; 
        if( lv[x] >= lv[y]  ){
            p = P[x];
            if( mark[p] )
               mark[x] = false, remover( A[x] );
            else
               mark[p] = true, add( A[p] );
            x = p;
        }else{
            tmp[++cant] = y;
            y = P[y];
        }
    }
    for( int i = cant; i >= 1; i -- ){
        p = tmp[i];
        if( mark[p] )
            mark[x] = false, remover( A[x] );
        else
            mark[p] = true, add( A[p] );
        x = p;
    }
}