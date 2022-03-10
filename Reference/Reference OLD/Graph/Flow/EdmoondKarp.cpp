#include <bits/stdc++.h>
using namespace std;

struct edge{
    int nodo, ady, cap, ant;
    edge( int a = 0, int b = 0, int c = 0, int d = 0 )
    {
        nodo = a, ady = b, cap = c, ant = d;
    }
}E[600*600];
int sr, sk, flow[600], parent[600], T[600], pos;

void insertar( int a, int b, int c )
{
    E[pos] = edge(a,b,c,T[a]);
    T[a] = pos++;
    E[pos] = edge(b,a,0,T[b]);
    T[b] = pos++;
}

queue<int>Q;
int edmond( )
{
    int maxflow = 0;
    while( 1 )
    {
        while( !Q.empty() )
            Q.pop();
        int nodo, ady, band = 0;
        for( int i = sr; i <= sk; i++ )
            flow[i] = parent[i] = -1;
        flow[sr] = parent[sr] = 1 << 30;
        Q.push(sr);
        while( !Q.empty() && !band )
        {
            nodo = Q.front();
            Q.pop();
            for( int i = T[nodo]; i != -1; i = E[i].ant )
            {
                ady = E[i].ady;
                if( E[i].cap && parent[ady] == -1 )
                {
                    parent[ady] = i;
                    flow[ady] = min(flow[nodo],E[i].cap);
                    Q.push(ady);
                    if( ady == sk )
                    {
                        band = 1;
                        break;
                    }
                }
            }
        }
        if( parent[sk] == -1 )
            break;
        maxflow+=flow[sk];
        for( int i = sk; i != sr; i = E[parent[i]].nodo )
        {
            E[parent[i]].cap -= flow[sk];
            E[parent[i]^1].cap += flow[sk];
        }
    }
    return maxflow;
}

int main()
{
    fill(T,T+sk+2,-1);
    return 0;
}
