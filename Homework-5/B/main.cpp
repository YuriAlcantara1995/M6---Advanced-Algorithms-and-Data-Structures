#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e2+5;
int N;
int M[MAXN][MAXN];
bool mark[MAXN];

void dfs(int nod)
{
    mark[nod]=true;

    for(int i=1;i<=N;i++)
        if(!mark[i] && M[nod][i]==1)
            dfs(i);
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N;
    int E = 0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        {
            cin >> M[i][j];
            E+=M[i][j];
        }

    dfs(1);

    E/=2;
    bool connected = true;
    for(int i=1;i<=N;i++)
        if(!mark[i])
            connected = false;

    if( E == N-1 && connected)
        cout <<  "YES\n";
    else
        cout << "NO\n";

    return 0;
}
