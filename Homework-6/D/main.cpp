#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
const int MAXN=55;
char A[MAXN][MAXN];
map<par,int>P;

const int mr[]={1,1,1,-1,-1,-1,0,0},
          mc[]={0,1,-1,0,1,-1,1,-1};
string D[]={"S","SE", "SW", "N", "NE", "NW","E","W"};

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=N;i++)
        cin >> (A[i]+1);

    par s,e;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            if(A[i][j] == 'S')
                s=par(i,j);
            else
                if(A[i][j] == 'F')
                    e=par(i,j);

    queue<par>q;
    q.push(s);
    P[s]=-1;

    while(!q.empty())
    {
        par nod=q.front();
        int r = nod.first;
        int c = nod.second;
        q.pop();

        for(int i=0;i<8;i++)
        {
            int nr = r + mr[i];
            int nc = c + mc[i];

            if(A[nr][nc]=='#' || nr<1 || nr>N || nc<1 || nc>M)
                continue;

            if(P.find(par(nr,nc)) != P.end())continue;

            P[par(nr,nc)]=i;
            q.push(par(nr,nc));
        }
    }

    vector<string>path;
    if(P.find(e) == P.end())
        cout << "-1\n";
    else
    {
        par p=e;
        while(P[p] != -1)
        {
            int idx=P[p];
            path.push_back(D[idx]);
            p.first = p.first+mr[idx]*-1;
            p.second = p.second+mc[idx]*-1;
        }

        reverse(path.begin(),path.end());
        cout << path.size() << '\n';
        for(int i=0;i<path.size();i++)
            cout << path[i] << '\n';

    }


    return 0;
}
