vector<par> Q[MAXN];
vector<int> G[MAXN];
bool IMP[MAXN];
int cnt[MAXN], col[MAXN], lv[MAXN];
int in[MAXN], fin[MAXN], k, sz[MAXN], ord[MAXN];
void act_color( int c, int v ){ cnt[v] ^= c; }
void Dfs( int nod, int pad ){
    in[nod] = ++k, ord[k] = nod, sz[nod] = 1;
    for( auto newn : G[nod] ){
        if( pad == newn ) continue;
        lv[newn] = lv[nod]+1;
        Dfs( newn, nod );
        sz[nod] += sz[newn];
    }
    fin[nod] = k;
}
void dsu_on_tree( int nod, int pad, bool keep){
    int mx = -1, bigChild = -1;
    for( auto newn : G[nod] ) 
		if( newn != pad && sz[newn] > mx)
			mx = sz[newn], bigChild = newn;
	//run a dfs on small childs and clear them from cnt
    for( auto newn : G[nod])
        if(newn != pad && newn != bigChild)
            dsu_on_tree(newn, nod, 0);  
	//bigChild marked as big and not cleared from cnt
    if(bigChild != -1) dsu_on_tree(bigChild, nod, 1);  
	//update childs	
    for(auto newn : G[nod]){
        if(newn == pad || newn == bigChild) continue;
        for(int j = in[newn]; j <= fin[newn]; j++)
            act_color(col[ord[j]], lv[ord[j]] ); 
    }
    act_color( col[nod], lv[nod] ); //update nod    
	//You can answer the queries easily.
	//q.first -> id de la query
	//q.second -> informacion de la query    
    if( keep == 1 ) return;
    for(int j = in[nod]; j <= fin[nod]; j++)
        act_color( col[ ord[j] ], lv[ord[j]] );//clear
}