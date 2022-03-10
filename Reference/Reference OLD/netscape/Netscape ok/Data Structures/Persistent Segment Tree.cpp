/*  * query -> get the number of elements in [a,b] interval
      who's values lie inside [x,y] interval
	* k_th -> find the k_th element in [a,b] sorted 
	  interval -> O(logN) time per operation   */
struct pst {
    struct node {
        int l, r, cant;
        node ( ) { l = r = cant = 0; }
    }tree[MAXN*24];
    int n, roots[MAXN];
    pst ( ) { n = 0; }
    void init ( int ini, int fin, int lv ) {
        if ( ini == fin ) return;
        tree[lv].l = ++n;
        tree[lv].r = ++n;
        int piv = (ini+fin)>>1;
        init ( ini, piv, tree[lv].l );
        init ( piv+1, fin, tree[lv].r );
    }
    void add ( int ini, int fin, int nod, int ant, int p ){
        if ( ini == fin ) {
            tree[nod].cant = tree[ant].cant + 1;
            return;
        }
        int piv = (ini+fin)>>1;
        if ( p <= piv ) {
            tree[nod].r = tree[ant].r;
            tree[nod].l = ++n;
            add ( ini, piv, tree[nod].l, tree[ant].l, p );
        } else {
            tree[nod].l = tree[ant].l;
            tree[nod].r = ++n;
            add ( piv+1, fin, tree[nod].r, tree[ant].r, p);
        }
        tree[nod].cant=tree[tree[nod].l].cant
		              +tree[tree[nod].r].cant;
    }
    int query ( int ini, int fin, int nod, int a, int b ) {
        if ( a <= ini && b >= fin ) return tree[nod].cant;
        if ( a > fin || b < ini ) return 0;
        int piv = (ini+fin)>>1;
        return query ( ini, piv, tree[nod].l, a, b ) +
			   query ( piv+1, fin, tree[nod].r, a, b );
    }
    int query ( int a, int b, int x, int y ) {
        return query ( 1, N, roots[b], x, y ) -
		       query ( 1, N, roots[a-1], x, y );
    }
	int k_th ( int ini, int fin, int a, int b, int k ) {
		if ( ini == fin ) return ini;
		int piv = ( ini + fin ) >> 1;
		int c= tree[tree[b].l].cant - tree[tree[a].l].cant;
		if ( c >= k ) 
			return k_th (ini,piv,tree[a].l, tree[b].l, k );
		return k_th (piv+1,fin,tree[a].r, tree[b].r, k-c );
	} 
	int k_th ( int a, int b, int k )  {
		return k_th ( 1, N, roots[a], roots[b], k );
	}	
};