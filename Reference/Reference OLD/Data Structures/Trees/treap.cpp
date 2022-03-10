#include <bits/stdc++.h>
using namespace std;

template <class T>
struct treap{
    struct nodo{
        nodo *l, *r;
        T key;
        int size, prio, inv, lazy;
        nodo(){
            l = r = nullptr;
            size = 1;
            inv = lazy = 0;
            prio = rand();
        }
    }*root;
    treap(){
        root = nullptr;
    }
    typedef pair<nodo*,nodo*>nn;
	
	//necesario para simular AVL y similar queda el upper bound y lower bound
	int find( nodo *n, T p ){
        if( !n )return 1;
        if( n->key < p )
            return sz(n->l)+1+find(n->r,p);
        return find(n->l,p);
    }
	
	//para simular un AVL e insertar en la posicion que le corresponde y no sea necesariamente al final
    void insert_1( T p ){
        int pos = find(root,p);
        treap a = split(pos-1);
        nodo *newn = new nodo(p);
        root = merge(a.root,merge(newn,root));
    }
	
    int sz( nodo *n ){
        if( !n )return 0;
        return n->size;
    }
    void update( nodo *n ){
        if( !n )return;
        n->size = sz(n->l) + sz(n->r) + 1;
        //do the merge between the subtrees like sum, min, max, hash etc
    }
    void insert( T x ){
        nodo *n = new nodo();
        n->key = x;
        root = merge(root,n);
    }
    void merge( treap a ){
        root = merge(root,a.root);
    }
    nodo *merge( nodo *l, nodo *r ){
        if( !l )return r;
        if( !r )return l;
        if( l->prio > r->prio ){
            updLazy(l);
            l->r = merge(l->r,r);
            update(l);
            return l;
        }
        updLazy(r);
        r->l = merge(l,r->l);
        update(r);
        return r;
    }
    treap split( int k ){
        treap ret;
        nn x = split(root,k);
        root = x.second;
        ret.root = x.first;
        return ret;
    }
     nn split( nodo *n, int k ){
        if( !n ) return nn(n,n);
        updLazy(n);
        if( sz(n->l) >= k ){
            nn x = split(n->l,k);
            n->l = x.second;
            update(n);
            return nn(x.first,n);
        }else{
            nn x = split(n->r,k-sz(n->l)-1);
            n->r = x.first;
            update(n);
            return nn(n,x.second);
        }
    }
    void print( ){
        print(root);
    }

    void updateInv( nodo *n ){//update the reverse lazy
        if( !n )return;
        n->inv ^= 1;
        swap( n->l,n->r );
    }

    void updLazy( nodo *n ){//update all the lazy propagation
        if( !n )return;
        if( n->lazy ){
            //do a lazy propagation like sum, min, max etc
            n->lazy = 0;
        }
        if( n->inv ){//do lazy of reverse
            updateInv(n->l);
            updateInv(n->r);
            n->inv = 0;
        }
    }

    void print( nodo *n ){
        if( !n )return;
		updLazy(n);
        print(n->l);
        cout << n->key << " ";
        print(n->r);
    }
    void reverse( int l, int r ){
        treap a = split(l-1);
        treap b = split(r-l+1);
        b.root->inv = 1;
        swap( b.root->l, b.root->r );
        root = merge(b.root,root);
        root = merge(a.root,root);
    }
};

//srand(time(0));
