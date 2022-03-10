#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;
vector<int>G[maxn];
int next[maxn], LCA[maxn][30], L[maxn];
typedef pair<int,int>par;
par P[maxn];
int I[maxn], top, S[maxn];

void dfs_sin_rec( int nodo, int pad )
{
    P[++top] = par(nodo,pad);//meto en la pila el nodo
    I[top] = 0;//inicializo el inicio del for de los adyacentes
    while( top )
    {
        nodo = P[top].first, pad = P[top].second;//saco de la pila
        int tam = G[nodo].size();
        for( int i = I[top]; i < tam; i++ )//recorro los adyacentes de donde me quede
        {
            int ady = G[nodo][i];
            I[top] = i+1;//actualizo donde me quede en ese nodo
            if( ady == pad )
                continue;
            P[++top] = par(ady,nodo); //meto en la pila(como llamar recursivamente)
            break;
        }
        if( I[top] == tam )//verifico si ya revise todos los adyacentes para bajar la recursividad
        {
            nodo = P[top].first, pad = P[top].second;
            I[top] = 0;
            top--;//bajo la recursividad
            int tam = G[nodo].size();
            for( int i = 0; i < tam; i++ )
            {
                int ady = G[nodo][i];
                if( ady == pad )
                    continue;
                if( S[ady] + 1 > S[nodo] )//actualizo el siguente nodo de la cadena
                    S[nodo] = S[ady]+1, next[nodo] = ady;
            }
        }
    }
}


int dfs( int nodo, int pad )
{
    int tam = G[nodo].size();
    int msize = 0;
    for( int i = 0; i < tam; i++ )
    {
        int ady = G[nodo][i];
        if( ady == pad )
            continue;
        int sz = dfs(ady,nodo);
        if( sz > msize )
            msize = sz, next[nodo] = ady;
    }
    return msize+1;
}

int cad[maxn], ncad, len[maxn], pos[maxn], link[maxn];
struct st{
    int on, off, b;
    st( int a = 0, int d = 0, int c = 0 )
    {
        on = a, off = d, b = c;
    }
};
vector< vector<st> >T;

int mark[maxn];
void hld_sin_rec( int nodo, int pad )
{
    top = 0;
    P[++top] = par(nodo,pad);
    I[top] = 0;
    while( top )
    {
        nodo = P[top].first, pad = P[top].second;
        if( !mark[nodo] )//para no analizarlo 2 veces
        {
            cad[nodo] = ncad;
            pos[nodo] = ++len[ncad];
        }
        mark[nodo] ++;
        if( next[nodo] && mark[nodo] == 1 )//si tiene un siguiente nodo y es la primera vez que lo visito
        {
            P[++top] = par(next[nodo],nodo);//me muevo al siguiente nodo
            continue;
        }
        else
         if( !next[nodo] )//si es el ultimo de la cadeno creo el vector del segment tree
            T.push_back( vector<st>(4*(len[ncad]+1)) );

        int tam = G[nodo].size();
        for( int i = I[top]; i < tam; i++ )//recorro los adyacentes
        {
            int ady = G[nodo][i];
            I[top] = i+1;
            if( ady == pad || ady == next[nodo] )
                continue;
            ncad++;
            link[ncad] = nodo;
            P[++top] = par(ady,nodo);
            break;
        }
        if( I[top] == tam )//bajo la recursividad
        {
            I[top] = 0;
            top--;
        }
    }
}

void hld( int nodo, int pad )
{
    int tam = G[nodo].size();
    cad[nodo] = ncad;
    pos[nodo] = ++len[ncad];
    if( next[nodo] )
    {
        hld(next[nodo],nodo);
        for( int i = 0; i < tam; i++ )
        {
            int ady = G[nodo][i];
            if( ady == pad || ady == next[nodo] )
                continue;
            ncad++;
            link[ncad] = nodo;
            hld(ady,nodo);
        }
    }
    else
        T.push_back( vector<st>( 4*len[ncad],0 ));
}

queue<int>Q;
int lg;
void processLCA( int nodo )
{
    Q.push(nodo);
    L[nodo] = 1;
    while( !Q.empty() )
    {
        nodo = Q.front();
        Q.pop();
        int tam = G[nodo].size();
        for( int i = 0; i < tam; i++ )
        {
            int ady = G[nodo][i];
            if( L[ady] )
                continue;
            L[ady] = L[nodo]+1;
            Q.push(ady);
            LCA[ady][0] = nodo;
            lg = log2(L[ady]);
            for( int j = 1; j <= lg; j++ )
                LCA[ady][j] = LCA[LCA[ady][j-1]][j-1];
        }
    }
}

int QLCA( int a, int b )
{
    if( L[a] < L[b] )
        swap(a,b);
    lg = log2(L[a]);
    for( int i = lg; i >= 0; i-- )
        if( L[a] - (1<<i) >= L[b] )
            a = LCA[a][i];
    if( a == b )
        return a;
    lg = log2(L[a]);
    for( int i = lg; i >= 0; i-- )
        if( LCA[a][i] != LCA[b][i] && LCA[a][i] )
            a = LCA[a][i], b = LCA[b][i];
    return LCA[a][0];
}

int ids;
void build( int ini, int fin, int lv )
{
    T[ids][lv].on = fin-ini+1;
    T[ids][lv].off = T[ids][lv].b = 0;
    if( ini == fin )
        return;
    int mit = (ini+fin)/2;
    build(ini,mit,lv*2);
    build(mit+1,fin,lv*2+1);
}

void lazy( int ini, int fin, int lv )
{
    T[ids][lv].b = 0;
    if( ini == fin )
        return;
    T[ids][lv*2].b ^= 1;
    T[ids][lv*2+1].b ^= 1;
    swap(T[ids][lv*2].on,T[ids][lv*2].off);
    swap(T[ids][lv*2+1].on,T[ids][lv*2+1].off);
}

void update( int ini, int fin, int lv, int a, int b )
{
    if( a > b )
        return;
    if( ini > b || fin < a )
        return;
    if( T[ids][lv].b )
        lazy(ini,fin,lv);
    if( ini >= a && fin <= b )
    {
        T[ids][lv].b = 1;
        swap(T[ids][lv].on,T[ids][lv].off);
        return;
    }
    int mit = (ini+fin)/2;
    update(ini,mit,lv*2,a,b);
    update(mit+1,fin,lv*2+1,a,b);
    T[ids][lv].on = T[ids][lv*2].on+T[ids][lv*2+1].on;
    T[ids][lv].off = T[ids][lv*2].off+T[ids][lv*2+1].off;
}

void UP( int nodo, int lca, int b )
{
    while( cad[nodo] != cad[lca] )
    {
        ids = cad[nodo];
        update(1,len[ids],1,1,pos[nodo]);
        nodo = link[ids];
    }
    ids = cad[nodo];
    update(1,len[ids],1,pos[lca]+b,pos[nodo]);
}

int query( int ini, int fin, int lv, int a, int b )
{
    if( a > b )
        return 0;
    if( ini > b || fin < a )
        return 0;
    if( T[ids][lv].b )
        lazy(ini,fin,lv);
    if( ini >= a && fin <= b )
        return T[ids][lv].on;
    int mit = (ini+fin)/2;
    return query(ini,mit,lv*2,a,b)+query(mit+1,fin,lv*2+1,a,b);
}

int QU( int nodo, int lca, int b )
{
    int ret = 0;
    while( cad[nodo] != cad[lca] )
    {
        ids = cad[nodo];
        ret += query(1,len[ids],1,1,pos[nodo]);
        nodo = link[ids];
    }
    ids = cad[nodo];
    ret += query(1,len[ids],1,pos[lca]+b,pos[nodo]);
    return ret;
}

int main()
{

    cin.tie(0);
	ios_base::sync_with_stdio(0);

	int N;
	cin >> N;

	int a, b;
	for( int i = 1; i < N; i++ )
	{
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
	}

	//dfs(1,-1);
	dfs_sin_rec(1,-1);
	hld_sin_rec(1,-1);
	//hld(1,-1);
	processLCA(1);

	for( int i = 0; i <= ncad; i++ )
    {
        ids = i;
        build(1,len[ids],1);
    }

    int c, Q;
    cin >> Q;
    while( Q-- )
    {
        cin >> c >> a >> b;
        int lca = QLCA(a,b);
        if( c == 1 )
        {

            UP(a,lca,0);
            UP(b,lca,1);
        }
        else
            cout << QU(a,lca,0)+QU(b,lca,1) << '\n';
    }

    return 0;
}
