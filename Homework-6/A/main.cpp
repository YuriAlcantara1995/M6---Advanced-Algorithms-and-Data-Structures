#include <bits/stdc++.h>
using namespace std;

const int MAXN=5e2+5;
int M[MAXN][MAXN];
bool mark[MAXN];
int P[MAXN];

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,a,b;
    cin >> N >> a >> b;

    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            cin >> M[i][j];

    queue<int>q;
    q.push(a);
    mark[a]=true;
    P[a]=a;

    while(!q.empty())
    {
        int nod = q.front();
        q.pop();

        for(int i=1;i<=N;i++)
            if(M[nod][i] == 1 && !mark[i])
            {
                P[i]=nod;
                mark[i]=true;
                q.push(i);
            }
    }
    vector<int>path;
    if(mark[b] == false)
    {
        cout << "-1\n";
    }
    else
    {
        int p = b;
        while(p!=P[p])
        {
            path.push_back(p);
            p=P[p];
        }
        path.push_back(p);
        reverse(path.begin(),path.end());
        cout << path.size()-1 << '\n';
        for(int i=0;i<path.size()-1;i++)
            cout << path[i] << ' ';
        cout << path[path.size()-1] << '\n';
    }




    return 0;
}
