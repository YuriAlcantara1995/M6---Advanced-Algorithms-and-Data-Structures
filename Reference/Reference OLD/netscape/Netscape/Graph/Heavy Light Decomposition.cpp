vector<int> V[MAXN];
int n, sz[MAXN], lv[MAXN], P[MAXN], A[MAXN], B[MAXN], C[MAXN];
// P: padre  A: ult hoja B: pos C:cant
// G[i] = vector<int>( 4*C[i], 0 );
// lv[1] = 1;
void Dfs( int nod = 1, int pad = 0 ){
    int mej = nod;
    A[nod] = nod;
    for( auto i : V[nod] ){
        if( i == pad ) continue;
        lv[i] = lv[nod]+1;
        Dfs( i, nod );
        if( sz[i] > sz[mej] ) mej = i;
        sz[nod] += sz[i];
    }
    mej = A[mej];
    sz[nod] ++;
    P[mej] = pad;
    A[nod] = mej, B[nod] = C[mej];
    C[mej] ++;
}
int sol;
void solve( int a, int b ){
    int a1 = a, b1 = b, dist = 0;
    while( A[a1] != A[b1] ){
       if( lv[ P[ A[a1] ] ] > lv[ P[ A[b1] ] ] )
          dist += lv[a1] - lv[ P[ A[a1] ] ], a1 =  P[ A[a1] ];
        else
          dist += lv[b1] - lv[ P[ A[b1] ] ], b1 =  P[ A[b1] ];
    }
    dist += abs( lv[ a1 ] - lv[ b1 ] );
    int lca = ( lv[a1] > lv[b1] ) ? b1 : a1;

    sol = 0;
    while( A[a] != A[lca] ){
        sol =__gcd(sol,query(A[a],0,C[A[a]]-1,1,B[a],C[A[a]]-1));
        a = P[ A[a] ];
    }

    sol =__gcd(sol, query(A[a], 0, C[A[a]]-1, 1, B[a], B[lca]-1 ));

    while( A[b] != A[lca] ){
        sol =__gcd(sol,query(A[b],0,C[A[b]]-1,1,B[b],C[A[b]]-1));
        b = P[ A[b] ];
    }

    sol =__gcd(sol, query(A[b], 0, C[A[b]]-1, 1, B[b], B[lca] ));
}