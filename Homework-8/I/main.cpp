#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll>par;
const int MAXN=5e3+5;
ll D[MAXN];
priority_queue<par,vector<par>,greater<par>>q;
vector<par>ady[MAXN];
ll P[MAXN];
bool mark[MAXN];
ll sol;
ll X[MAXN],Y[MAXN];
int N,M;

ll square(ll x)
{
    return x*x;
}

ll dist(int i,int j)
{
    return square(X[i]-X[j]) + square(Y[i]-Y[j]);
}

void dfs(int nod)
{
    mark[nod]=true;

    for(auto e:ady[nod])
    {
        int nn=e.first;
        int nc=e.second;
        if(mark[nn])continue;

        sol+=nc;
        P[nn]=-1;
        dfs(nn);

        for(int i=1;i<=N;i++)
            if(!mark[i] && D[i] > dist(nn,i))
            {
                D[i] = dist(nn,i);
                P[i] = nn;
                q.push(par(D[i],i));
            }


    }
}

void Prim(int start)
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

        sol += cos;
        dfs(nod);

        for(int i=1;i<=N;i++)
            if(!mark[i] && D[i] > dist(nod,i))
            {
                D[i] = dist(nod,i);
                P[i] = nod;
                q.push(par(D[i],i));
            }

    }
}

void print_edges()
{
    for(int i=2;i<=N;i++)
        if(P[i]!=-1)
            cout << P[i] << ' ' << i << '\n';
}

int main() {

    cin >> N;

    for(int i=1;i<=N;i++)
    {
        cin >> X[i] >> Y[i];
        D[i]=1ll<<60;
    }

    cin >> M;
    int a,b,c;
    for(int i=1;i<=M;i++)
    {
        cin >> a >> b;
        c=dist(a,b);
        ady[a].push_back(par(b,c));
        ady[b].push_back(par(a,c));
    }

    Prim(1);

    print_edges();

    return 0;
}
