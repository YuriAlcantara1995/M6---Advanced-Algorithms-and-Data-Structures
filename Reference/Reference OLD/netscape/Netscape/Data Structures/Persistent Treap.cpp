/* Careful with memory and recommended 
	to use Garbage Collection  */
typedef struct item* pitem;
struct item {
    int val, sz;
    pitem l, r;
    item ( ) {
        val = 0;
        sz = 1;
        l = r = 0;
    }
};
int sz ( pitem t ) { return (t)? t->sz : 0; }
void upd_sz ( pitem t ) {
    t->sz = sz(t->l) + sz(t->r) + 1;
}
typedef tuple<pitem,pitem> tupla;
tupla split ( pitem v, int k ) {
    if ( !v ) return make_tuple ( v, v );
    pitem l, r, ret;
    ret = new item();//ret = v ( treap )
    ret->val = v->val; 
    if ( k >= sz(v->l) + 1 ) {
        tie(l,r) = split ( v->r, k-sz(v->l)-1 );
        ret->l = v->l;//
        ret->r = l;
        upd_sz ( ret );
        return make_tuple ( ret, r );
    } else {
        tie(l,r) = split ( v->l, k );
        ret->r = v->r;//
        ret->l = r;
        upd_sz ( ret );
        return make_tuple( l, ret );
    }
}
pitem merge ( pitem l, pitem r ) {
    if ( !l ) return r;
    if ( !r ) return l;
    pitem clone = new item();//no crear 
    int tl = sz(l), tr = sz(r);
    if ( rand() % (tl+tr) < tl ) {
        clone->val = l->val;//clone = l
        clone->l = l->l;
        clone->r = merge ( l->r, r );
    } else {
        clone->val = r->val;//clone = r
        clone->r = r->r;
        clone->l = merge ( l, r->l );
    }
    upd_sz ( clone );
    return clone;
}