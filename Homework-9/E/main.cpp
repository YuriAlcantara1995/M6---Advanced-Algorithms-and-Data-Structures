#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e3+5;
string S[MAXN];
string C[MAXN];
int N,c;
vector<int>ady[MAXN];
bool used[MAXN];
int match[MAXN];

bool can(int i, int j)
{
    if(tolower(S[i][0])!=C[j][0])
        return false;

    for(int k=1;k<S[i].size();k++)
        if(tolower(S[i][k])==C[j][1])
            return true;

    return false;
}

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

    cin >> N;

    for(int i='a';i<='z';i++)
        for(int j='a';j<='z';j++)
        {
            string x(1,(char)i);
            x+=(char)j;
            C[++c]=x;
        }

    while(N != 0)
    {
        for(int i=1;i<=N;i++)
            cin >> S[i];

        for(int i=1;i<=N;i++)
        {
            ady[i].clear();
            for(int j=1;j<=c;j++)
            {
                if(can(i,j))
                    ady[i].push_back(j);
            }
        }


        memset(match,-1,sizeof match);
        for(int i=1;i<=N;i++)
        {
            memset(used,0,sizeof used);
            try_kuhn(i);
        }

        int sol=0;
        for(int i=1;i<=c;i++)
            if(match[i] != -1)
                sol++;

        cout << sol << '\n';



        cin >> N;
    }

    return 0;
}
