#include <bits/stdc++.h>
using namespace std;

const int MAXN=505;
typedef pair<int,int>par;
vector<par>ady[MAXN];
int D[MAXN][5];

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=N;i++)
        D[i][1] = D[i][2] = D[i][3] = 1<<30;

    int a,b,c;
    for(int i=1;i<=M;i++)
    {
        cin >> a >> b >> c;
        ady[a].push_back(par(b,c));
    }

    queue<par>q;
    q.push(par(1,-1));
    D[1][1] = D[1][2] = D[1][3] = 0;

    while(!q.empty())
    {
        int nod = q.front().first;
        int c = q.front().second;
        q.pop();

        for(auto x:ady[nod])
        {
            int nn = x.first;
            int nc = x.second;

            if(nc == c) continue;

            if(D[nn][nc] > D[nod][c] + 1)
            {
                D[nn][nc] = D[nod][c] + 1;
                q.push(par(nn,nc));
            }
        }
    }

    int sol = min(D[N][1],min(D[N][2],D[N][3]));
    if(sol == 1<<30)
        cout << "-1\n";
    else
        cout << sol << '\n';

    return 0;
}
