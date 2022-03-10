#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int N,M;
vector<int>ady[MAXN];
bool mark[MAXN];
bool in_path[MAXN];
bool cycle;
vector<int>path;

void dfs(int nod)
{
    mark[nod]=true;
    if(!cycle)
    {
        for(auto nn:ady[nod])
        {
            if(!cycle && in_path[nn]==true)
            {
                cycle = true;
                cout << "NO\n";
                int p = 0;
                while(path[p]!=nn)p++;
                cout << path.size()-p << '\n';
                for(int i=p;i<path.size();i++)
                    cout << path[i] << ' ';
                cout << nn << '\n';
            }

            if(mark[nn])continue;

            path.push_back(nn);
            in_path[nn]=true;
            dfs(nn);
            in_path[nn]=false;
            path.pop_back();
        }
    }
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int T;
    cin >> T;

    while(T--)
    {
        cin >> N >> M;
        for(int i=1;i<=N;i++)
        {
            ady[i].clear();
            mark[i]=false;
            in_path[i]=false;
        }
        cycle=false;
        path.clear();

        int a,b;
        for(int i=1;i<=M;i++)
        {
            cin >> a >> b;
            ady[a].push_back(b);
        }

        for(int i=1;i<=N;i++)
            if(!mark[i])
            {
                path.push_back(i);
                in_path[i]=true;
                dfs(i);
                in_path[i]=false;
                path.pop_back();
            }

        if(!cycle)
            cout << "YES\n";
    }

    return 0;
}
