#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
const int MAXN=1e3+5;
char A[MAXN][MAXN];
map<par,int>P;

const int mr[]={1,-1,0,0},
          mc[]={0,0,-1,1};

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=N;i++)
        cin >> (A[i]+1);

    par e;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            if(A[i][j] == '*')
                e=par(i,j);

    map<par,int>Map,D,P;
    queue<par>q;
    int E;
    cin >> E;
    int a,b;
    for(int i=1;i<=E;i++)
    {
        cin >> a >> b;
        q.push(par(a,b));
        Map[par(a,b)]=i;
        P[par(a,b)]=-1;
    }

    while(!q.empty())
    {
        par nod = q.front();
        int r = nod.first;
        int c = nod.second;
        q.pop();

        for(int i=0;i<4;i++)
        {
            int nr = r + mr[i];
            int nc = c + mc[i];

            if(A[nr][nc]=='1' || nr<1 || nr>N || nc<1 || nc>M)
                continue;

            if(P.find(par(nr,nc))!=P.end())
                continue;

            P[par(nr,nc)]=i;
            q.push(par(nr,nc));
        }
    }

    if(P.find(e) == P.end())
        cout << "-1\n";
    else
    {
        par p=e;
        while(P[p] != -1)
        {
            int idx=P[p];
            p.first = p.first+mr[idx]*-1;
            p.second = p.second+mc[idx]*-1;
        }

        cout << Map[p] << '\n';
    }


    return 0;
}
