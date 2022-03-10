//los nodos en true en el arreglo fals pertenecen a un ciclo neg
#include <bits/stdc++.h>
using namespace std;
#define MN 1000
struct edge{
	int u,v;
	long long w;
	edge(int uu,int vv,long long ww){
		u = uu;v = vv;w = ww;
	}
};
long long  B[MN],D[MN];
vector<edge> E;
int n,m,u,v,w;
bool fals[MN];
int main() {
    E.clear();
    scanf("%d",&n);
    for(int i =0;i<=n;i++)
        D[i] = 1e9;
    scanf("%d",&m);
    for(int i =0;i<m;i++){
        scanf("%d%d%d",&u,&v,&w);
        E.push_back(edge(u,v,w));
    }
    D[1] = 0;
    edge e(0,0,0);
    for(int i =0;i<n-1;i++){
        for(int j = 0;j<m;j++){
            e = E[j];
            if(D[e.u] + e.w < D[e.v] && D[e.u]<1e9)
                D[e.v] = D[e.u] + e.w;
        }
    }
    for(int j = 0;j<m;j++){
        edge e  = E[j];
        if(D[e.u] + e.w < D[e.v] && D[e.u]<1e9)
            fals[e.v] = true;
    }
    for(int i =0;i<n-1;i++){
        for(int j = 0;j<m;j++){
            edge e  = E[j];
            if(fals[e.u] ) fals[e.v] = true;
        }
    }
	return 0;
}

