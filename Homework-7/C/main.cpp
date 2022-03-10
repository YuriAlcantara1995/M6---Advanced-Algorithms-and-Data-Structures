#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e2+5;
int D[MAXN][MAXN];

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        {
            cin >> D[i][j];
            if(!D[i][j])
                D[i][j]=1<<30;
            if(i==j)
                D[i][j]=0;
        }

    for(int k=1;k<=N;k++)
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                if(D[i][k]!=1<<30 && D[k][j]!=1<<30 && D[i][j]>D[i][k]+D[k][j])
                    D[i][j]=D[i][k]+D[k][j];

    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(D[i][j]==1<<30)
                D[i][j]=0;

    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<N;j++)
            cout << D[i][j] << ' ';
        cout << D[i][N] << '\n';
    }



    return 0;
}
