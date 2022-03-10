#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
char A[MAXN][MAXN];
int N,M;
int C[MAXN][MAXN];
int CS[MAXN*MAXN];

const int mf[]={0,0,1,-1},
          mc[]={-1,1,0,0};

void dfs(int f, int c, int component)
{
    C[f][c]=component;
    CS[component]++;

    for(int i=0;i<4;i++)
    {
        int nf=f+mf[i];
        int nc=c+mc[i];

        if(A[nf][nc] == '.' && C[nf][nc]==0)
            dfs(nf,nc,component);
    }
}


int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N >> M;
    for(int i=1;i<=N;i++)
        cin >> (A[i]+1);

    int cc=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            if(C[i][j] == 0 && A[i][j]=='.')
                dfs(i,j,++cc);

    sort(CS+1,CS+cc+1);

    cout << cc << '\n';
    if(cc > 0)
    {
        for(int i=1;i<cc;i++)
            cout << CS[i] << ' ';
        cout << CS[cc] << '\n';
    }

    return 0;
}
