#include <bits/stdc++.h>
using namespace std;

const int maxn = 200003, maxk = 1000006;
int N, K, dp[maxk], cost[maxk];
struct par{
    int b, c;
};
vector<par>G[maxn];
int mark[maxn], T[maxn];
void dfs( int nodo, int pad ){
    T[nodo] = 0;
    for( auto i : G[nodo] ){
        if( i.b == pad || mark[i.b] )continue;
        dfs(i.b,nodo);
        T[nodo] += T[i.b];
    }
    T[nodo]++;
}

int dfs_c( int nodo, int pad, int c ){
    for( auto i : G[nodo] ){
        if( i.b != pad && !mark[i.b] && 2*T[i.b] >= c )
            return dfs_c(i.b,nodo,c);
    }
    return nodo;
}

set<int>S;
int sol = 1 << 30;

void query( int nodo, int pad, int c, int ca ){
    if( c <= K && dp[K-c] )
        sol = min(sol,ca+cost[K-c]);
    if( c > K )return;
    for( auto i : G[nodo] ){
        if( i.b == pad || mark[i.b] )continue;
        query(i.b,nodo,c+i.c,ca+1);
    }
}

void update( int nodo, int pad, int c, int ca ){
    if( c <= K )
        S.insert(c), dp[c] = 1, cost[c] = min(cost[c],ca);
    if( c > K )return;
    for( auto i : G[nodo] ){
        if( i.b == pad || mark[i.b] )continue;
        update(i.b,nodo,c+i.c,ca+1);
    }
}

void centroid( int nodo, int pad ){
    dfs(nodo,pad);
    int centro = dfs_c( nodo, pad, T[nodo] );
    mark[centro] = 1;
    S.clear();
    S.insert(0);
    dp[0] = 1;
    cost[0] = 0;
    for( auto i : G[centro] ){
        if( i.b == pad || mark[i.b] )continue;
        query(i.b,nodo,i.c,1);
        update(i.b,nodo,i.c,1);
    }

    for( auto i : S )
        dp[i] = 0, cost[i] = 1 << 30;

    for( auto i : G[centro] ){
        if( i.b != pad && !mark[i.b] )
            centroid(i.b,centro);
    }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    #ifdef acm
    freopen("a.in","r",stdin);
    #endif // acm

    int a, b, c;

    cin >> N >> K;
    for( int i = 0; i <= K; i++ )
        cost[i] = 1 << 30, dp[i] = 0;
    for( int i = 1; i < N; i++ ){
        cin >> a >> b >> c;
        G[a].push_back(par{b,c});
        G[b].push_back(par{a,c});
    }

    centroid(1,-1);

    if( sol == 1 << 30 )cout << "-1";
    else cout << sol;
    return 0;
}
