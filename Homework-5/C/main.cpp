#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
int N,M;
vector<int>ady[MAXN];
int mark[MAXN];
int C[MAXN];
int CS[MAXN];

void dfs(int nod, int c)
{
    mark[nod]=c;
    C[nod]=c;
    CS[c]++;

    for(auto nn:ady[nod])
    {
        if(mark[nn] > 0)continue;
        dfs(nn, c);
    }
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
        ady[b].push_back(a);
    }

    int cc=0;
    for(int i=1;i<=N;i++)
        if(!mark[i])
            dfs(i,++cc);

    for(int i=1;i<N;i++)
        cout << CS[C[i]] << ' ';
    cout << CS[C[N]] << '\n';



    return 0;
}
