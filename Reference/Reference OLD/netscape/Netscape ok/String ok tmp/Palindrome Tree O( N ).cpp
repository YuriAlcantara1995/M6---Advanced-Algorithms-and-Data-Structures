struct PalindromicTree{
    int tree[MAXN][30], link[MAXN], length[MAXN], sz, ult;
    int diff[MAXN], slink[MAXN], ans[MAXN], sans[MAXN];
    string s;
    void ini(  ){
        memset( tree, 0, sizeof(tree) );
        memset( link, 0, sizeof(link) );
        memset( length, 0, sizeof(length) );
        length[1] = -1, link[1] = 1;
        length[2] = 0, link[2] = 1;
        sz = ult = 2, s.clear();
    }
    int find_x( int suff, int p ){
		int len = length[suff];
		while( p - len < 1 || s[p] != s[p-len-1] )
		  suff = link[suff], len = length[suff];
		return suff;
	}
    void insertar( char c ){
        int p = s.size();
        s.push_back( c );
        int suff = find_x( ult, p );
        if( tree[suff][c-'a'] == 0 ){
			tree[suff][c-'a'] = ++sz;
			length[sz] = length[suff] + 2;
			link[sz] = ( length[sz] == 1 )? 2 :
				tree[find_x( link[suff], p )][c-'a'];
            diff[sz] = length[sz]-length[link[sz]];
            slink[sz] = ( diff[sz]!=diff[link[sz]] )?
                            link[sz] : slink[link[sz]];
        }
		ult = tree[suff][c-'a'];
    }
    void descomponer( int i ){
        ans[i] = 1 << 30;
        for(int v = ult; length[v]>0; v = slink[v]){
			sans[v]= ans[i -(length[slink[v]] + diff[v])];
			if(diff[v] == diff[link[v]])
				sans[v] = min(sans[v], sans[link[v]]);
			ans[i] = min(ans[i], sans[v] + 1);
		}
    }
}palin;