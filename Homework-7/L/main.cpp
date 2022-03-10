#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll>par;
const int MAXN=1e5+5;
ll D[MAXN];
priority_queue<par,vector<par>,greater<par>>q;
vector<par>ady[MAXN];
ll P[MAXN];

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

        for(auto x:ady[nod])
        {
            ll nn = x.first;
            ll nc = x.second;
            if(D[nn] > cos+nc)
            {
                D[nn] = cos+nc;
                P[nn] = nod;
                q.push(par(D[nn],nn));
            }
        }
    }
}

void print_path(int nod, bool last=false)
{
    if(nod == P[nod])
        cout << nod << ' ';
    else
    {
        print_path(P[nod]);

        if(last)
            cout << nod << '\n';
        else
            cout << nod << ' ';
    }
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

    if(D[N] != 1ll<<60)
        print_path(N,true);
    else
        cout << "-1\n";

    return 0;
}
