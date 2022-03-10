#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;
vector<int>E[MAXN];
int S[MAXN],R[MAXN];
vector<int>edges;
vector<vector<int>>edgesS;
vector<vector<int>>edgesP;

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
        E[i] = {0,0,0,i};
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
        edges.push_back(i);

        join_set(seta,setb);
    }

    int second = 1<<30;
    for(int i=0;i<edges.size();i++)
    {
        int id = edges[i];

        int solP=0;
        for(int j=1;j<=N;j++)
            S[j]=j,R[j]=1;
        edgesP.clear();

        for(int j=1;j<=M;j++)
        {
            if(j == id) continue;

            int a=E[j][1],b=E[j][2],c=E[j][0],p=E[j][3];

            int seta = find_set(a);
            int setb = find_set(b);

            if(seta == setb) continue;

            solP+=c;
            edgesP.push_back(vector<int>{p,a,b,c});

            join_set(seta,setb);
        }

        if(edgesP.size() == N-1 && solP<second)
        {
            second = solP;
            edgesS = edgesP;
        }
    }

    if(second != 1<<30)
    {
        cout << second << '\n';
        sort(edgesS.begin(),edgesS.end());
        for(auto e:edgesS)
            cout << e[1] << ' ' << e[2] << ' ' << e[3] << '\n';
    }
    else
        cout << "-1\n";


    return 0;
}
