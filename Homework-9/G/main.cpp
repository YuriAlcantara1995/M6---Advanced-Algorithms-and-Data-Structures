#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
const int MAXN=1e3+5;
int N,M;
vector<int>ady[MAXN];
int match[MAXN];
int imatch[MAXN];
bool used[MAXN];
bool mark[MAXN];
vector<int>P[MAXN];
int p;
bool visited[MAXN];
int TS[MAXN];
int k;

void TSort(int nod)
{
    visited[nod]=true;
    for(auto nn:ady[nod])
        if(!visited[nn])
            TSort(nn);
    TS[++k]=nod;
}

void paths(int nod)
{
    mark[nod]=true;
    P[p].push_back(nod);
    while(imatch[nod])
    {
        P[p].push_back(imatch[nod]);
        nod = imatch[nod];
        mark[nod]=true;
    }
}

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (auto to : ady[v]) {
        if (match[to] == -1 || try_kuhn(match[to])) {
            match[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N >> M;

    int a,b;
    for(int i=1;i<=M;i++)
    {
        cin >> a >> b;
        ady[a].push_back(b);
    }

    memset(match,-1,sizeof match);
    for(int i=1;i<=N;i++)
    {
        memset(used,0,sizeof used);
        try_kuhn(i);
    }

    vector<par>matches;
    for(int i=1;i<=N;i++)
        if(match[i] != -1)
            imatch[match[i]]=i;

    for(int i=1;i<=N;i++)
        if(!visited[i])
            TSort(i);

    reverse(TS+1,TS+k+1);

    for(int i=1;i<=N;i++)
        if(!mark[TS[i]])
        {
            p++;
            paths(TS[i]);
        }

    cout << p << '\n';
    for(int i=1;i<=p;i++)
    {
        for(int j=0;j<P[i].size()-1;j++)
            cout << P[i][j] << ' ';
        cout << P[i][P[i].size()-1] << '\n';
    }


    return 0;
}
