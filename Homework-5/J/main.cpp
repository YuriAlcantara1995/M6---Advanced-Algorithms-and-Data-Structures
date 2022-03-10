    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN=2e5+5;
    int N,M;
    vector<int>ady[MAXN];
    bool mark[MAXN];
    bool in_path[MAXN];
    bool cycle;
    vector<int>tsort;

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
                }

                if(mark[nn])continue;

                in_path[nn]=true;
                dfs(nn);
                in_path[nn]=false;
            }
        }
        tsort.push_back(nod);
    }

    int main() {

        cin.tie(0);
        ios_base::sync_with_stdio(0);

        cin >> N >> M;

        int a,b;
        for(int i=1;i<=M;i++)
        {
            cin >> a >> b;
            a++,b++;
            ady[a].push_back(b);
        }

        for(int i=1;i<=N;i++)
            if(!mark[i])
            {
                in_path[i]=true;
                dfs(i);
                in_path[i]=false;
            }

        if(!cycle)
        {
            cout << "YES\n";
            reverse(tsort.begin(),tsort.end());
            for(int i=0;i<tsort.size()-1;i++)
                cout << tsort[i]-1 << ' ';
            cout << tsort[tsort.size()-1]-1 << '\n';
        }


        return 0;
    }
