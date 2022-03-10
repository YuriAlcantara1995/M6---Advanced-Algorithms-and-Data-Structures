// Task  : Given a bipartite graph, find its minimum vertex cover
//  Running time: O(VE)
#define MAXV 5000
int X, Y, E;
int matched[MAXV];
bool mark[MAXV];
bool T[MAXV];
vector<int> ady[MAXV];
typedef pair<int, bool> par;
queue<par> Q;
bool augment( int nod ){
	if ( nod == -1 ) return true;
	int size = ady[nod].size();
	for ( int i = 0; i < size; i++ ){
		int newn = ady[nod][i];
		if ( mark[newn] ) continue ;
		mark[newn] = true;
		if ( augment( matched[newn] ) )	{
			matched[nod] = newn;
			matched[newn] = nod;
			return true;
		}
	}
	return false;
}
/// X->Y
void Vertex_Cover_Bipartite(  ){
    /* Find maximum matching */
    memset( matched, -1, sizeof( matched ) );
    memset( T, false, sizeof( T ) );
	int cardinality = 0;
	for ( int i = 0; i < X; i++ ){
		memset( mark, 0, sizeof( mark ) );
		if ( augment( i ) ) cardinality++;
	}
    /* Find minimum vertex cover */
	for ( int i = 0; i < X; i++ )
		if ( matched[i] == -1 ){
			T[i] = true;
			Q.push( par( i, true ) );
        }
    int nod, newn; bool band;
	while ( !Q.empty() ){
		nod = Q.front().first;
		band = Q.front().second;
		Q.pop();
		int size = ady[nod].size();
		for ( int i = 0; i < size; i++ ){
			newn = ady[nod][i];
			if ( T[newn] ) continue ;
			if ( ( band && newn != matched[nod] ) || ( !band && newn == matched[nod] )){
				T[newn] = true;
				Q.push( par( newn, !band ) );
			}
		}
	}
	printf("%d\n", cardinality );
	//printf( "Minimum Vertex Cover:\n" );
	for ( int i = X; i < X + Y; i++ )
		if ( T[i] ) printf("vline %d %d %d\n", V[i-X+1].x, V[i-X+1].a, V[i-X+1].b );
	for ( int i = 0; i < X; i++ )
		if ( !T[i] ) printf("hline %d %d %d\n", H[i+1].x, H[i+1].a, H[i+1].b );
}