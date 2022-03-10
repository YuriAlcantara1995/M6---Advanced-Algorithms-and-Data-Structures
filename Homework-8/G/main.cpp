#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
vector<int>E[MAXN];
int S[MAXN],R[MAXN];
vector<vector<int>>edges;

void join_set(int seta, int setb)
{
    if(R[seta] >= R[setb])
    {
        R[seta]+=R[setb];
        S[setb]=seta;
    }
    else
    {
        R[setb]+=R[seta];
        S[seta]=setb;
    }
}

int find_set(int nod)
{
    if(S[nod]==nod)
        return S[nod];
    return S[nod] = find_set(S[nod]);
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=N;i++)
        S[i]=i,R[i]=1;

    for(int i=1;i<=M;i++)
    {
        E[i] = {0,0,0};
        cin >> E[i][1] >> E[i][2] >> E[i][0];
    }

    sort(E+1,E+M+1);

    int sol=0;
    for(int i=1;i<=M;i++)
    {
        int a=E[i][1],b=E[i][2],c=E[i][0];

        int seta = find_set(a);
        int setb = find_set(b);

        if(seta == setb) continue;

        sol+=c;
        edges.push_back(vector<int>{a,b});

        join_set(seta,setb);
    }

    cout << sol << '\n';
    for(auto e:edges)
    {
        cout << e[0] << ' ' << e[1] << '\n';
    }

    return 0;
}
