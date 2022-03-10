#include <bits/stdc++.h>
using namespace std;

const int MAXN=3e5+5;
vector<int>ady[MAXN];
int B[MAXN],E[MAXN];
int t;

void dfs(int nod)
{
    B[nod]=++t;

    for(auto nn:ady[nod])
        dfs(nn);

    E[nod]=++t;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;
    int p;
    for(int i=2;i<=N;i++)
    {
        cin >> p;
        ady[p].push_back(i);
    }

    dfs(1);

    int M;
    cin >> M;
    int a,b;
    while(M--)
    {
        cin >> a >> b;
        if(B[a]>=B[b] && E[a]<=E[b])
            cout << "2\n";
        else
            if(B[b]>=B[a] && E[b]<=E[a])
                cout << "1\n";
            else
                cout << "3\n";
    }

    return 0;
}
