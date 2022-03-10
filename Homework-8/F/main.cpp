#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll>par;
const int MAXN=1e5+5;
ll D[MAXN];
priority_queue<par,vector<par>,greater<par>>q;
vector<par>ady[MAXN];
ll P[MAXN];
bool mark[MAXN];
ll sol;

void Dijkstra(int start)
{
    P[start] = start;
    D[start]=0;
    q.push(par(0,start));

    while(!q.empty())
    {
        ll cos = q.top().first;
        ll nod = q.top().second;
        q.pop();
        if(mark[nod]) continue;

        mark[nod] = true;
        sol += cos;

        for(auto x:ady[nod])
        {
            ll nn = x.first;
            ll nc = x.second;
            if(!mark[nn] && D[nn] > nc)
            {
                D[nn] = nc;
                P[nn] = nod;
                q.push(par(D[nn],nn));
            }
        }
    }
}

void print_tree(int N)
{
    for(int i=2;i<=N;i++)
        cout << P[i] << ' ' << i << '\n';
}

int main() {

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=N;i++)
        D[i]=1ll<<60;

    int a,b,c;
    for(int i=1;i<=M;i++)
    {
        cin >> a >> b >> c;
        ady[a].push_back(par(b,c));
        ady[b].push_back(par(a,c));
    }

    Dijkstra(1);

    cout << sol << '\n';
    print_tree(N);

    return 0;
}
