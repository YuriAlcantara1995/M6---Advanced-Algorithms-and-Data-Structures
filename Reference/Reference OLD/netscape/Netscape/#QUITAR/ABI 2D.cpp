vector <int> V[1000003], tree[1000003];
void init ( ) {
    for ( int i = 1; i <= N; i ++ )
        if ( V[i].size() > 1 ) {
            V[i] = vector <int> ( 1, 0 );
            tree[i] = vector <int> ( 1, 0 );
        }
    for ( int i = 1; i <= n; i ++ )
        for ( int j = P[i].y; j <= N; j += (j&-j) ){
            V[j].push_back ( P[i].z );
            tree[j].push_back ( 0 );
        }
}
void update ( int x, int y, int v ) {
    int lo, l;
    for ( int i = x; i <= N; i += (i&-i) ) {
        lo = lower_bound ( V[i].begin(), V[i].end(), y )
        		                          - V[i].begin();
        l = V[i].size();
        for ( int j = lo; j < l; j += (j&-j) )
            tree[i][j] = max ( tree[i][j], v );
    }
}
int query ( int x, int y ) {
    if ( x <= 0 || y <= 0 ) return 0;
    int ret = 0, lo;
    for ( int i = x-1; i > 0; i -= (i&-i) ) {
        lo = lower_bound ( V[i].begin(), V[i].end(), y )
        				 - V[i].begin() - 1;
        for ( int j = lo; j > 0; j -= (j&-j) )
            ret = max ( ret, tree[i][j] );
    }
    return ret;
}