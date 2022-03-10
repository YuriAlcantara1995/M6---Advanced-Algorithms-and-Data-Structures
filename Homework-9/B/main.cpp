#include<bits/stdc++.h>
using namespace std;

int N,M;
const int MAXN = 2e5+5;
vector<int> ady[MAXN];
int D[MAXN],Mx[MAXN], My[MAXN];

bool BFS(){
    int u, v, i, e;
    queue<int> q;
    bool f = 0;
    for (i = 0; i < N+M; i++) D[i] = 0;
    for (i = 0; i < N; i++)
        if (Mx[i] == -1) q.push(i);
    while (!q.empty()){
        u = q.front(); q.pop();
        for (e = ady[u].size()-1; e >= 0; e--) {
            v = ady[u][e];
            if (D[v + N]) continue;
            D[v + N] = D[u] + 1;
            if (My[v] != -1){
                D[My[v]] = D[v + N] + 1;
                q.push(My[v]);
            }else f = 1;
        }
    }
    return f;
}
int DFS(int u){
    for (int v, e = ady[u].size()-1; e >=0; e--){
        v = ady[u][e];
        if (D[v+N] != D[u]+1) continue;
        D[v+N] = 0;
        if (My[v] == -1 || DFS(My[v])){
            Mx[u] = v;  My[v] = u;  return 1;
        }
    }
    return 0;
}
int Hopcroft_Karp(){
    int i, flow = 0;
    for (i = max(N,M); i >=0; i--) Mx[i] = My[i] = -1;

    while (BFS())
        for (i = 0; i < N; i++)
            if (Mx[i] == -1 && DFS(i))
                ++flow;
     return flow;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N >> M;

    for(int i=0;i<N;i++)
    {
        int a;
        cin >> a;
        while(a!=0)
        {
            ady[i].push_back(a-1);
            cin >> a;
        }
    }

    cout << Hopcroft_Karp() << '\n';
    for(int i=0;i<N;i++)
        if(Mx[i]!=-1)
            cout << i+1 << ' ' << Mx[i]+1 << '\n';

    return 0;
}