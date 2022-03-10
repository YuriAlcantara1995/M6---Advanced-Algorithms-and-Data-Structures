#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
typedef vector<int>vi;
const int MAXN = 3e5+5;
int S[MAXN],R[MAXN];
vi E[MAXN];
int C[MAXN];
vi ady[MAXN];

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

int nc(int c)
{
    if(c==1)
        return 2;
    else
        return 1;
}


int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=N;i++)
        S[i]=i,R[i]=1,C[i]=1;

    for(int i=1;i<=M;i++)
    {
        E[i]=vi{0,0};
        cin >> E[i][0] >> E[i][1];
    }

    int a,b;
    for(int i=1;i<=M;i++)
    {
        a=E[i][0];
        b=E[i][1];
        int seta = find_set(a);
        int setb = find_set(b);

        if(seta == setb && C[a]==C[b])
        {
            cout << i;
            return 0;
        }

        if(seta == setb) continue;


        vector<bool>mark(N+1,false);
        queue<par>q;
        if(R[seta]>=R[setb])
        {
            q.push(par(b,nc(C[a])));
            mark[b]=true;
            C[b]=nc(C[a]);
        }
        else
        {
            q.push(par(a,nc(C[b])));
            mark[a]=true;
            C[a]=nc(C[b]);
        }

        while(!q.empty())
        {
            int nod = q.front().first;
            int c = q.front().second;
            q.pop();

            for(auto nn:ady[nod])
            {
                if(mark[nn]) continue;
                mark[nn] = true;
                C[nn]=nc(c);
                q.push(par(nn,C[nn]));
            }
        }

        join_set(seta,setb);
        ady[a].push_back(b);
        ady[b].push_back(a);
    }

    cout << "-1\n";

    return 0;
}
