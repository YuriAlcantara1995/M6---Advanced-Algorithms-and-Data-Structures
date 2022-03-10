typedef struct item* pitem;
struct item {
    int prio, sz;
    par men, v;
    bool rev;
    pitem l, r;
    item ( int x, int i ) {
        rev = false;
        prio = rand();
        sz = 1;
        v = par ( x,i );
        men = par ( x,i );
        l = r = 0;
    }
}*root;
inline int sz ( pitem t ) { return t? t->sz : 0; }
inline par val ( pitem t ) {
    return t? t->men : par(1<<30,1<<30);
}
void updata ( pitem t ) {
    if ( !t ) return;
    t->sz = sz(t->l) + sz(t->r) + 1;
    t->men = min ( { t->v, val(t->l), val(t->r) } );
}
void push ( pitem t ) {
    if ( !t || !t->rev ) return;
    swap ( t->l, t->r );
    if ( t->l ) t->l->rev ^= 1;
    if ( t->r ) t->r->rev ^= 1;
    t->rev = 0;
}
tuple <pitem,pitem> split ( pitem t, int k ) {
    if ( !t ) return make_tuple(nullptr,nullptr);
    push(t);
    pitem l, r;
    if ( k >= sz(t->l)+1 ) {
        tie(l,r) = split ( t->r, k-sz(t->l)-1 );
        t->r = l;
        updata ( t );
        return make_tuple ( t, r );
    } else {
        tie(l,r) = split ( t->l, k );
        t->l = r;
        updata ( t );
        return make_tuple ( l, t );
    }
}
pitem merge ( pitem l, pitem r ) {
    if ( !l ) return r;
    if ( !r ) return l;
    push(l), push(r);
    if ( l->prio > r->prio ) {
        l->r = merge ( l->r, r );
        updata(l);
        return l;
    } else {
        r->l = merge ( l, r->l );
        updata(r);
        return r;
    }
}