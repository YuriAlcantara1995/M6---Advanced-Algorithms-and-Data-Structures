#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
vector<int>ady[MAXN];
int dt;
bool mark[MAXN];
int DT[MAXN],LOW[MAXN];
set<int>cutPoints;

void dfs(int nod, int p = -1) {
    mark[nod] = true;

    DT[nod] = LOW[nod] = ++dt;
    int children = 0;

    for (auto nn:ady[nod])
    {
        if (nn == p) continue;

        if (mark[nn])
        {
            LOW[nod] = min(LOW[nod], DT[nn]);
        }
        else
        {
            dfs(nn, nod);
            LOW[nod] = min(LOW[nod], LOW[nn]);
            if (LOW[nn] >= DT[nod] && p!=-1)
                cutPoints.insert(nod);
            ++children;
        }
    }

    if(p == -1 && children > 1)
        cutPoints.insert(nod);

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
        ady[a].push_back(b);
        ady[b].push_back(a);
    }

    for(int i=1;i<=N;i++)
        if(!mark[i])
            dfs(i);

    cout << cutPoints.size() << '\n';
    for(auto cp:cutPoints)
        cout << cp << ' ';
    cout << '\n';

    return 0;
}
