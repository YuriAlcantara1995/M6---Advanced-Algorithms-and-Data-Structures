int pos, Index[MAXN];///index = -1, pos = 0
int lv[MAXN], Id[MAXN], in, fin, n;
struct edges{ ///N cant de nodos
 int nod, newn, cap, next;
 edges( int a = 0, int b = 0, int c = 0, int e = 0 ){
  nod = a, newn = b, cap = c, next = e;
 }
 int nextn ( int a ){
  return ( nod == a )? newn : nod;
 }
}G[MAXE];
///nod, newn, cap
void insertar( int a, int b, int c ){
 G[pos] = edges( a, b, c, Index[a] );
 Index[a] = pos ++;
 G[pos] = edges( b, a, 0, Index[b] );
 Index[b] = pos ++;
}
queue<int> Q;
bool Bfs( int limt ){
	while( !Q.empty() ) Q.pop();
	fill( lv, lv + n+1, 0);
	lv[in] = 1;
	Q.push( in );
	while( !Q.empty() ) {
		int nod = Q.front();
		Q.pop();
		for( int i = Index[nod]; i != -1; i = G[i].next ){
			int newn = G[i].newn;
			if( lv[newn] != 0 || G[i].cap < limt )continue;
			lv[newn] = lv[nod] + 1;
			Q.push( newn );
			if( newn == fin ) return true;
		}
	}
	return false;
}
bool Dfs( int nod, int limt ){
	if( nod == fin ) return true;
	for( ; Id[nod] != -1; Id[nod] = G[Id[nod]].next ){
		int newn = G[Id[nod]].newn;
		if( lv[nod] + 1 == lv[newn] &&
			G[Id[nod]].cap >= limt && Dfs( newn, limt ) ){
			G[Id[nod]].cap -= limt;
			G[Id[nod]^1].cap += limt;
			return true;
		}
	}
	return false;
}
int Dinic( ){
	int flow = 0;
	for( int limt = 1024; limt > 0; ){
		if( !Bfs( limt ) ){
            limt >>= 1;
			continue;
		}
		for( int i = 0; i <= n; i ++ )
			Id[i] = Index[i];
		while( limt > 0 && Dfs( in, limt ) )
			flow += limt;
	}
	return flow;
}