int tree[MAXN][26], fail[MAXN];
int termina[MAXN], size = 1;
void addWord( string pal ){
    int p = 0;
    for(char c : pal){
        if( !tree[p][c-'a'] )
            tree[p][c-'a'] = size++;
        p = tree[p][c-'a'];
    }
    //termina[p].push_back( pal_id );
    termina[p] = pal.size();
}
void buildersuffix(){
    queue<int> Q;
    for(int i = 0; i < 26; i++)
        if( tree[0][i] ) Q.push(tree[0][i]);
    while( !Q.empty() ){
        int u, v = Q.front(); Q.pop();
		//for( auto i : termina[fail[v]] ) 
		//	termina[v].push_back( i );	
        termina[v] = max(termina[v], termina[fail[v]]);
        for( int i = 0; i < 26; i++ )
            if(u = tree[v][i]){
                fail[u] = tree[fail[v]][i];
                Q.push( u );
            }else
                tree[v][i] = tree[fail[v]][i];
    }
}