#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
bool bipartite = true;
int C[MAXN];
vector<int>ady[MAXN];

void dfs(int nod,int c)
{
    C[nod] = c;

    for(auto nn:ady[nod])
    {
        if(C[nn] > 0)
        {
            if(C[nn] == C[nod])
                bipartite = false;
            continue;
        }

        dfs(nn,c == 1 ? 2: 1);
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
        ady[a].push_back(b);
        ady[b].push_back(a);
    }

    for(int i=1;i<=N;i++)
        if(!C[i])
            dfs(i,1);

    if(bipartite)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
