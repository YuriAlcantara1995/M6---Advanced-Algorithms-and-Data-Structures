#include <bits/stdc++.h>
using namespace std;

const int MAXN=8e3+5;
vector<int>ady[MAXN];
int match[MAXN];
bool Z[MAXN];
int N,M;

void dfs(int nod)
{
    Z[nod]=true;

    if(nod>N && match[nod] && !Z[match[nod]])
        dfs(match[nod]);
    else
    {
        for(auto nn:ady[nod])
        {
            if(match[nod]==nn || Z[nn])continue;
            dfs(nn);
        }
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N >> M;

    int K;
    for(int i=1;i<=N;i++)
    {
        cin >> K;
        for(int j=1;j<=K;j++)
        {
            int a;
            cin >> a;
            ady[i].push_back(a+N);
            ady[a+N].push_back(i);
        }
    }

    for(int i=1;i<=N;i++)
    {
        cin >> match[i];
        if(match[i])
        {
            match[i]+=N;
            match[match[i]]=i;
        }
    }

    for(int i=1;i<=N;i++)
        if(!match[i])
            dfs(i);

    vector<int>FP,SP;
    for(int i=1;i<=N+M;i++)
    {
        if(i<=N && !Z[i])
            FP.push_back(i);

        if(i>N && Z[i])
            SP.push_back(i-N);
    }

    cout << FP.size() + SP.size() << '\n';
    cout << FP.size();
    for(auto nod:FP)
        cout << ' ' << nod;
    cout << '\n' << SP.size();
    for(auto nod:SP)
        cout << ' ' << nod;
    cout << '\n';

    return 0;
}
