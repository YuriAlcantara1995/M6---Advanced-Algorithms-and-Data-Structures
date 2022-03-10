#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
vector<int>ady[MAXN];
int dt;
bool mark[MAXN];
int DT[MAXN],LOW[MAXN];
typedef pair<int,int>par;
map<par,int>Map;
vector<int>bridges;

void dfs(int nod, int p = -1) {
    mark[nod] = true;

    DT[nod] = LOW[nod] = ++dt;

    for (auto nn:ady[nod]) {
        if (nn == p) continue;

        if (mark[nn])
        {
            LOW[nod] = min(LOW[nod], DT[nn]);
        }
        else
        {
            dfs(nn, nod);
            LOW[nod] = min(LOW[nod], LOW[nn]);
            if (LOW[nn] > DT[nod])
                bridges.push_back(Map[par(min(nod,nn), max(nod,nn))]);
        }
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    int a,b;
    for(int i=1;i<=M;i++)
    {
        cin >> a >> b;
        if(a>b)
            swap(a,b);
        Map[par(a,b)]=i;
        ady[a].push_back(b);
        ady[b].push_back(a);
    }

    for(int i=1;i<=N;i++)
        if(!mark[i])
            dfs(i);

    cout << bridges.size() << '\n';
    for(int i=0;i<(int)bridges.size()-1;i++)
        cout << bridges[i] << ' ';
    if(!bridges.empty())
        cout << bridges[bridges.size()-1] << '\n';

    return 0;
}
