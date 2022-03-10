#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
const int MAXN=1e5+5;
bool used[MAXN];
int match[MAXN];
vector<int>ady[MAXN];

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (auto to : ady[v]) {
        if (match[to] == -1 || try_kuhn(match[to])) {
            match[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=N;i++)
    {
        int a;
        cin >> a;
        while(a!=0)
        {
            ady[i].push_back(a);
            cin >> a;
        }
    }

    memset(match,-1,sizeof match);
    for(int i=1;i<=N;i++)
    {
        memset(used,0,sizeof used);
        try_kuhn(i);
    }

    vector<par>matches;
    for(int i=1;i<=M;i++)
        if(match[i] != -1)
            matches.push_back(par(match[i], i));

    cout << matches.size() << '\n';

    for(int i=0;i<matches.size();i++)
        cout << matches[i].first << ' ' << matches[i].second << '\n';


    return 0;
}
