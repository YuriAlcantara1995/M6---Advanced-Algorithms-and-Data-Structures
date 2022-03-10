#include <bits/stdc++.h>
#define maxn 100005

using namespace std;

char cad[maxn];
int l, Q;
struct splay_tree{
    const int inf = 1e9;
	struct nodo {
		int size;
		nodo *l, *r, *p;
		bool inv;
		int laz, let, cant[30];
		nodo(nodo *f=0, nodo *i = 0, nodo *d = 0){
		    l = i, p = f, r = d, size = 1, let = 0, laz = 0, inv = false;
		    for( int i = 0; i <= 29; i++ )
                cant[i] = 0;
		}
	} *root;
    splay_tree () { root = NULL; }

	inline void zig ( nodo *x ) {
        nodo *y = x->p, *z = y->p;
        y->l = x->r;
        if ( x->r )
            x->r->p = y;
        x->p = z;
        if ( z )
            if ( z->l == y ) z->l = x;
            else z->r = x;
        y->p = x;
        x->r = y;
        updata (y);
	}

	inline void zag ( nodo *x ) {
        nodo *y = x->p, *z = y->p;
        y->r = x->l;
        if ( x->l )
            x->l->p = y;
        x->p = z;
        if ( z )
            if ( z->l == y ) z->l = x;
            else z->r = x;
        y->p = x;
        x->l = y;
        updata (y);
	}

	inline void splay ( nodo *x ) {
        nodo *y, *z;
        while ( x->p ) {
            y = x->p, z = y->p;
            if ( !z ) {
                if ( y->l == x ) zig(x);
                else zag(x);
            }
            else if ( z->l == y && y->l == x ) zig(y), zig(x);
            else if ( z->r == y && y->r == x ) zag(y), zag(x);
            else if ( z->r == y && y->l == x ) zig(x), zag(x);
            else                               zag(x), zig(x);
        }
        root = x;
        updata (root);
	}

    inline void updata ( nodo *x ) {
        x->size = ( (x->l)? x->l->size : 0 ) + ( (x->r)? x->r->size : 0 ) + 1;
        for( int i = 0; i <= 27; i++ )
            x->cant[i] = ((x->l)?x->l->cant[i]:0) + ((x->r)?x->r->cant[i]:0) + (i == x->let);
    }

    inline void find ( int x ) {
        if ( !root )
            return;
        nodo *p = root;
        int izq;
        while ( true ) {
            lazy (p);
            izq = ( p->l )? p->l->size : 0;
            if ( x == izq+1 ) break;
            if ( x > izq+1 ) {
                x -= izq+1;
                if ( p->r ) p = p->r; else break;
            }
            else
                if ( p->l ) p = p->l; else break;
        }
        splay(p);
    }

    inline void insert ( int a ) {
        nodo *p = root, *f = 0;
        while ( p ) { f = p, p = p->r; };
        p = new nodo ( f, 0, 0 );
        p->let = a;
        if ( f ) f->r = p;
        splay (p);
    }

    inline splay_tree split ( int x ) {
        if ( !root ) return splay_tree ();
        splay_tree L = splay_tree ();
        find(x);
        if ( root->l )
            root->l->p = 0;
        L.root = root->l,
        root->l = 0;
        updata ( root );
        return L;
    }

    inline void join ( splay_tree L ) {
        if ( !L.root ) return;
        if ( !root ) root = L.root;
        else {
            find(-inf);
            root->l = L.root;
            root->l->p = root;
            updata(root);
        }
        L.root = NULL;
    }

    inline void erase ( int x ) {
        find(x);
        if ( !root ) return;
        if ( !root->l ) {
            nodo *tmp = root;
            root = root->r;
            if ( root ) root->p = 0;
            delete tmp;
        }
        else {
            nodo *t = root->r, *tmp = root;
            root = root->l;
            root->p = 0;
            find ( x );
            root->r = t;
            if ( t ) t->p = root;
            updata ( root );
            delete ( tmp );
        }
    }

    void lazy ( nodo *x ) {
        if ( !x )
            return;
        if( x->inv ){
            if( x->l ){
                x->l->inv ^= 1;
                swap(x->l->l,x->l->r);
            }
            if( x->r ){
                x->r->inv ^= 1;
                swap(x->r->l,x->r->r);
            }
            x->inv = 0;
        }
        if( x->laz ){
            if( x->l ){
                x->l->laz = 1;
                x->l->let = x->let;
                for( int i = 0; i <= 27; i++ )
                    x->l->cant[i] = 0;
                x->l->cant[x->let] = x->l->size;
            }
            if( x->r ){
                x->r->laz = 1;
                x->r->let = x->let;
                for( int i = 0; i <= 27; i++ )
                    x->r->cant[i] = 0;
                x->r->cant[x->let] = x->r->size;
            }
            x->laz = 0;
        }
    }

    int count( int a, int b, int c ){
        splay_tree t = split(a);
        splay_tree t1 = split(b-a+2);
        int ret = t1.root->cant[c];
        join(t1);
        join(t);
        return ret;
    }
    void change( int a, int b, int c ){
        splay_tree t = split(a);
        splay_tree t1 = split(b-a+2);

        for( int i = 0; i <= 27; i++ )
            t1.root->cant[i] = 0;
        t1.root->cant[c] = b-a+1;
        t1.root->laz = 1;
        t1.root->let = c;

        join(t1);
        join(t);
    }

    void reverse( int a, int b ){
        splay_tree t = split(a);
        splay_tree t1 = split(b-a+2);

        t1.root->inv = 1;
        swap(t1.root->l,t1.root->r);

        join(t1);
        join(t);
    }

}ST;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    #ifdef acm
    freopen("a.in","r",stdin);
    #endif // acm

    int N;
    cin >> (cad+1) >> N;
    l = strlen ( cad+1 );
    for ( int i = 1; i <= l; i ++ )
        ST.insert ( cad[i]-'a' );
    ST.insert ( 26 );
    int a, b, d;
    char q, c;
    while( N-- ){
        cin >> q;
        if( q == 'C' ){
            cin >> a >> b >> c;
            cout << ST.count(a,b,c-'a') << '\n';
        }
        if( q == 'S' ){
            cin >> a >> b >> c;
            ST.change(a,b,c-'a');
        }
        if( q == 'R' ){
            cin >> a >> b;
            ST.reverse(a,b);
        }
    }

    return 0;
}
