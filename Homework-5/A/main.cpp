#include <bits/stdc++.h>
using namespace std;

const int MAXN=505;
int N,a,b;
vector<int>path;
bool reached;
vector<int> ady[MAXN];
bool mark[MAXN];


void dfs(int nod)
{
    mark[nod]=true;
    if(nod == b && !reached)
    {
        reached = true;
        cout << path.size()-1 << '\n';
        for(int i=0;i<path.size()-1;i++)
            cout << path[i] << ' ';
        cout << path[path.size()-1] << '\n';
        return;
    }

    for(int i=0;i<ady[nod].size() && !reached;i++)
    {
        int nn = ady[nod][i];
        if(!mark[nn])
        {
            path.push_back(nn);
            dfs(nn);
            path.pop_back();
        }
    }
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N >> a >> b;

    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        {
            int x;
            cin >> x;
            if(x==1)
                ady[i].push_back(j);
        }


    path.push_back(a);
    dfs(a);

    if(!reached)
        cout << "-1\n";



    return 0;
}
