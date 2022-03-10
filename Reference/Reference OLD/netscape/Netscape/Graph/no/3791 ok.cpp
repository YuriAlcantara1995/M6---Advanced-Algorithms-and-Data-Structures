//============================================================================
// Name        : asd.cpp
// Author      : bestard
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;
typedef double db;
typedef pair<ll, ll> par;
typedef pair<ll, par> tri;

ll mod = 1e9+7;

struct matrix{
    ll a, b, c, d;
};

ll mul( ll a, ll b ){
    return (a*b)%mod;
}

matrix mul_matrix( matrix x, matrix y ){
    matrix s;
    s.a = ( mul( x.a, y.a ) + mul( x.b, y.c ) )%mod;
    s.b = ( mul( x.a, y.b ) + mul( x.b, y.d ) )%mod;
    s.c = ( mul( x.c, y.a ) + mul( x.d, y.c ) )%mod;
    s.d = ( mul( x.c, y.b ) + mul( x.d, y.d ) )%mod;
    return s;
}

matrix pow_matrix( matrix x, ll e ){
    matrix s = { 1, 0, 0, 1 };
    while ( e ) {
        if( e&1 ) s = mul_matrix( s, x );
        x = mul_matrix( x, x );
        e /=2ll;
    }
    return s;
}

matrix pot[100005];
//---------------------------------

vector<int> V[MAXN];
int n, sz[MAXN], lv[MAXN], P[MAXN], A[MAXN], B[MAXN], C[MAXN];

struct r{
    int a, b, c;
}Ar[MAXN];

int Dp[MAXN][25];
ll DpC[MAXN][25];

vector<par> L[MAXN];
vector<ll>  G[MAXN];
vector<par> Lr[MAXN];
vector<ll>  Gr[MAXN];

void ini(  ){
    for( int i = 1; i <= n ; i ++ ){
        sz[i] = 0;
        lv[i] = 0;
        P[i] = 0;
        C[i] = 0;
        B[i] = 0;
        A[i] = 0;
        V[i].clear();
        L[i].clear();
        Lr[i].clear();
        G[i].clear();
        Gr[i].clear();
        memset( Dp[i], 0, sizeof( Dp[i] ) );
        memset( DpC[i], 0, sizeof( DpC[i] ) );
    }
}

void Dfs( int nod, int pad ){
    int mej = nod;
    for( auto i : V[nod] ){
        if( i == pad ) continue;
        lv[i] = lv[nod]+1;
        Dfs( i, nod );
        if( sz[A[i]] > sz[mej] ) mej = A[i];
        sz[nod] += sz[i];
    }
    sz[nod] ++;
    P[mej] = pad;
    A[nod] = mej, B[nod] = C[mej];
    C[mej] ++;
}


void lazy( int ptr, int in, int fin, int lv ){
    if( in == fin ){
        L[ptr][lv] = { 0, 0 };
        return;
    }

    int mit = (in+fin)/2;

    int tmp = mit-in+1;

    if( ptr == 11 )
        int io = 0;

    G[ptr][lv*2] += ( mul( pot[tmp+1].c, L[ptr][lv].second ) + mul( pot[tmp+1].d, L[ptr][lv].first ) )%mod;
    G[ptr][lv*2] %= mod;
    G[ptr][lv*2] = ( G[ptr][lv*2] - L[ptr][lv].second + mod )%mod;

    ll tm = G[ptr][lv*2];

    L[ptr][lv*2].first = ( L[ptr][lv].first + L[ptr][lv*2].first)%mod;
    L[ptr][lv*2].second = (L[ptr][lv].second + L[ptr][lv*2].second)%mod;

    par vt;
    vt.second = ( mul( L[ptr][lv].second, pot[tmp].a ) + mul( L[ptr][lv].first, pot[tmp].b ) )%mod;
    vt.first = ( mul( L[ptr][lv].second, pot[tmp].c ) + mul( L[ptr][lv].first, pot[tmp].d ) )%mod;

    L[ptr][lv] = vt;

    tmp = fin-mit;

    G[ptr][lv*2+1] += ( mul( pot[tmp+1].c, L[ptr][lv].second ) + mul( pot[tmp+1].d, L[ptr][lv].first ) )%mod;
    G[ptr][lv*2+1] %= mod;
    G[ptr][lv*2+1] = ( G[ptr][lv*2+1] - L[ptr][lv].second + mod )%mod;

    tm = G[ptr][lv*2+1];

    L[ptr][lv*2+1].first = ( L[ptr][lv].first + L[ptr][lv*2+1].first)%mod;
    L[ptr][lv*2+1].second = (L[ptr][lv].second + L[ptr][lv*2+1].second)%mod;

    L[ptr][lv] = { 0, 0 };
}

void update( int ptr, int in, int fin, int lv, int x, int y, par v ){
    if( x > y ) return;
    if( in > y || fin < x ) return;
    if( L[ptr][lv] != par( 0, 0 ) ) lazy( ptr, in, fin, lv );

    if( x <= in && fin <= y ){
        int tmp = fin-in+1;
        G[ptr][lv] += ( mul( pot[tmp+1].c, v.second ) + mul( pot[tmp+1].d, v.first ) )%mod;
        G[ptr][lv] %= mod;
        G[ptr][lv] = (G[ptr][lv] - v.second + mod )%mod;
        ll to = G[ptr][lv];
        L[ptr][lv] = v;
        return;
    }

    int mit = (in+fin)/2;
    update( ptr, in, mit, lv*2, x, y, v );

    int tmp = max( 0, mit-max( x, in )+1 );
    par vt;
    vt.second = ( mul( v.second, pot[tmp].a ) + mul( v.first, pot[tmp].b ) )%mod;
    vt.first = ( mul( v.second, pot[tmp].c ) + mul( v.first, pot[tmp].d ) )%mod;

    update( ptr, mit+1, fin, lv*2+1, x, y, vt );

    G[ptr][lv] = ( G[ptr][lv*2] + G[ptr][lv*2+1] ) %mod;
}

ll query( int ptr, int in, int fin, int lv, int x, int y ){
    if( x > y ) return 0;

    if( in > y || fin < x ) return 0;

    if( L[ptr][lv] != par( 0, 0 ) ) lazy( ptr, in, fin, lv );

    if( x <= in && fin <= y ) return G[ptr][lv];

    int mit = (in+fin)/2;
    return ( query( ptr, in, mit, lv*2, x, y ) + query( ptr, mit+1, fin, lv*2+1, x, y ) )%mod;
}

//------------------------------------

void lazy_r( int ptr, int in, int fin, int lv ){
    if( in == fin ){
        Lr[ptr][lv] = { 0, 0 };
        return;
    }

    int mit = (in+fin)/2;

    int tmp = fin-mit;

    if( ptr == 11 )
        int io = 0;

    Gr[ptr][lv*2+1] += ( mul( pot[tmp+1].c, Lr[ptr][lv].second ) + mul( pot[tmp+1].d, Lr[ptr][lv].first ) )%mod;
    Gr[ptr][lv*2+1] %= mod;
    Gr[ptr][lv*2+1] = ( Gr[ptr][lv*2+1] - Lr[ptr][lv].second + mod )%mod;

    ll tm = Gr[ptr][lv*2+1];

    Lr[ptr][lv*2+1].first = ( Lr[ptr][lv].first + Lr[ptr][lv*2+1].first)%mod;
    Lr[ptr][lv*2+1].second = (Lr[ptr][lv].second + Lr[ptr][lv*2+1].second)%mod;

    par vt;
    vt.second = ( mul( Lr[ptr][lv].second, pot[tmp].a ) + mul( Lr[ptr][lv].first, pot[tmp].b ) )%mod;
    vt.first = ( mul( Lr[ptr][lv].second, pot[tmp].c ) + mul( Lr[ptr][lv].first, pot[tmp].d ) )%mod;

    Lr[ptr][lv] = vt;

    tmp = mit-in+1;

    Gr[ptr][lv*2] += ( mul( pot[tmp+1].c, Lr[ptr][lv].second ) + mul( pot[tmp+1].d, Lr[ptr][lv].first ) )%mod;
    Gr[ptr][lv*2] %= mod;
    Gr[ptr][lv*2] = ( Gr[ptr][lv*2] - Lr[ptr][lv].second + mod )%mod;

    tm = Gr[ptr][lv*2];

    Lr[ptr][lv*2].first = ( Lr[ptr][lv].first + Lr[ptr][lv*2].first)%mod;
    Lr[ptr][lv*2].second = (Lr[ptr][lv].second + Lr[ptr][lv*2].second)%mod;

    Lr[ptr][lv] = { 0, 0 };
}

void update_r( int ptr, int in, int fin, int lv, int x, int y, par v ){
    if( x > y ) return;
    if( in > y || fin < x ) return;
    if( Lr[ptr][lv] != par( 0, 0 ) ) lazy_r( ptr, in, fin, lv );

    if( x <= in && fin <= y ){
        int tmp = fin-in+1;
        Gr[ptr][lv] += ( mul( pot[tmp+1].c, v.second ) + mul( pot[tmp+1].d, v.first ) )%mod;
        Gr[ptr][lv] %= mod;
        Gr[ptr][lv] = (Gr[ptr][lv] - v.second + mod )%mod;
        ll to = Gr[ptr][lv];
        Lr[ptr][lv] = v;
        return;
    }

    int mit = (in+fin)/2;
    update_r( ptr, mit+1, fin, lv*2+1, x, y, v );

    int tmp = max( 0, min( y, fin )-mit );
    par vt;
    vt.second = ( mul( v.second, pot[tmp].a ) + mul( v.first, pot[tmp].b ) )%mod;
    vt.first = ( mul( v.second, pot[tmp].c ) + mul( v.first, pot[tmp].d ) )%mod;

    update_r( ptr, in, mit, lv*2, x, y, vt );

    Gr[ptr][lv] = ( Gr[ptr][lv*2] + Gr[ptr][lv*2+1] ) %mod;
}

ll query_r( int ptr, int in, int fin, int lv, int x, int y ){
    if( x > y ) return 0;

    if( in > y || fin < x ) return 0;

    if( Lr[ptr][lv] != par( 0, 0 ) ) lazy_r( ptr, in, fin, lv );

    if( x <= in && fin <= y ) return Gr[ptr][lv];

    int mit = (in+fin)/2;
    return ( query_r( ptr, in, mit, lv*2, x, y ) + query_r( ptr, mit+1, fin, lv*2+1, x, y ) )%mod;
}

//------------------------------------

ll sol;
void solve( int a, int b, bool band ){
    int a1 = a, b1 = b, dist = 0;
    while( A[a1] != A[b1] ){
       if( lv[ P[ A[a1] ] ] > lv[ P[ A[b1] ] ] )
          dist += lv[a1] - lv[ P[ A[a1] ] ], a1 =  P[ A[a1] ];
        else
          dist += lv[b1] - lv[ P[ A[b1] ] ], b1 =  P[ A[b1] ];
    }
    dist += abs( lv[ a1 ] - lv[ b1 ] );
    int lca = ( lv[a1] > lv[b1] ) ? b1 : a1;

    par in = { 3, 4 };
    while( A[a] != A[lca] ){
        if( band ) update( A[a], 0, C[ A[a] ]-1, 1, B[a], C[ A[a] ]-1, in );
        else{
            sol += query( A[a], 0, C[ A[a] ]-1, 1, B[a], C[ A[a] ]-1 );
            sol %= mod;
            sol += query_r( A[a], 0, C[ A[a] ]-1, 1, B[a], C[ A[a] ]-1 );
            sol %= mod;
        }

        int tmp = lv[a] - lv[ P[ A[a] ] ];

        par tin;
        tin.second = ( mul( in.second, pot[tmp].a ) + mul( in.first, pot[tmp].b ) )%mod;
        tin.first = ( mul( in.second, pot[tmp].c ) + mul( in.first, pot[tmp].d ) )%mod;

        in = tin;

        a = P[ A[a] ];
    }

    if( band ) update( A[a], 0, C[ A[a] ]-1, 1, B[a], B[lca]-1, in );
    else{
        sol += query( A[a], 0, C[ A[a] ]-1, 1, B[a], B[lca]-1 );
        sol %= mod;
        sol += query_r( A[a], 0, C[ A[a] ]-1, 1, B[a], B[lca]-1 );
        sol %= mod;
    }

    a1 = lv[b];
    while( A[b] != A[lca] ){

        int tmp = dist - (a1- lv[ P[A[b]] ] );
        in.second = ( mul( 4, pot[tmp].a ) + mul( 3, pot[tmp].b ) )%mod;
        in.first = ( mul( 4, pot[tmp].c ) + mul( 3, pot[tmp].d ) )%mod;

        if( band ) update_r( A[b], 0, C[ A[b] ]-1, 1, B[b], C[ A[b] ]-1, in );
        else{
                sol += query( A[b], 0, C[ A[b] ]-1, 1, B[b], C[ A[b] ]-1 );
                sol %= mod;
                sol += query_r( A[b], 0, C[ A[b] ]-1, 1, B[b], C[ A[b] ]-1 );
                sol %= mod;
        }



        b = P[ A[b] ];
    }

    int tmp = dist - (a1- lv[ lca ] );
    in.second = ( mul( 4, pot[tmp].a ) + mul( 3, pot[tmp].b ) )%mod;
    in.first = ( mul( 4, pot[tmp].c ) + mul( 3, pot[tmp].d ) )%mod;

    if( band ) update_r( A[b], 0, C[ A[b] ]-1, 1, B[b], B[lca]-1, in );
    else{
        sol += query( A[b], 0, C[ A[b] ]-1, 1, B[b], B[lca]-1 );
        sol %= mod;
        sol += query_r( A[b], 0, C[ A[b] ]-1, 1, B[b], B[lca]-1 );
        sol %= mod;
    }
}

//---------------------------------



int main() {
    #ifdef acm
        freopen("a.in", "r", stdin);
    #endif // acm
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    pot[0] = { 1, 0, 0, 1 };
    matrix fib = { 1, 1, 1, 0 };
    for( int i = 1; i <= 100000; i ++ )
        pot[i] = mul_matrix( pot[i-1], fib );

    while( cin >> n  ){

        ini();

        int a, b, c;
        for( int i = 1; i < n ; i ++ ){
            cin >> a >> b >> c;
            V[a].push_back( b );
            V[b].push_back( a );
            Ar[i] = { a, b, c };
        }

        lv[0] = -1;
        Dfs( 1, 0 );

        for( int i = 1; i < n ; i ++ ){
            if( lv[ Ar[i].a ] < lv[ Ar[i].b ] ) swap( Ar[i].a, Ar[i].b );
            Dp[Ar[i].a][0] = Ar[i].b;
            DpC[Ar[i].a][0] = Ar[i].c;
        }

        for( int i = 1; i <= 22; i ++ )
        for( int j = 1; j <= n ; j ++ ){
            Dp[j][i] = Dp[ Dp[j][i-1] ][i-1];
            DpC[j][i] = ( DpC[j][i-1] + DpC[ Dp[j][i-1] ][i-1] )%mod;
        }


        for( int i = 1; i <= n ; i ++ )if( C[i] ){
            G[i] = vector<ll>( 4*C[i], 0 );
            L[i] = vector<par>( 4*C[i], par( 0, 0 ) );

            Gr[i] = vector<ll>( 4*C[i], 0 );
            Lr[i] = vector<par>( 4*C[i], par( 0, 0 ) );
        }

        int Q;
        cin >> Q;

        for( int i = 1; i <= Q; i ++ ){
            cin >> a >> b >> c;

            sol = 0;
            solve( b, c, ( a == 2 ) );

            if( a == 1 ){
                if( lv[b] < lv[c] ) swap( b, c );
                for( int j = 22; j >= 0; j -- )
                    if( Dp[b][j] && lv[b] - (1<<j) >= lv[c] )
                        sol = (sol+DpC[b][j])%mod, b = Dp[b][j];

                if( c == b ){
                    cout << sol << '\n';
                    continue;
                }

                for( int j = 22; j >= 0; j -- )
                    if( Dp[b][j] && Dp[b][j] != Dp[c][j] ){
                        sol = (sol+DpC[b][j])%mod, b = Dp[b][j];
                        sol = (sol+DpC[c][j])%mod, c = Dp[c][j];
                    }

                sol = (sol+DpC[b][0])%mod;
                sol = (sol+DpC[c][0])%mod;

                cout << sol << '\n';
            }
        }

    }


    return 0;
}

