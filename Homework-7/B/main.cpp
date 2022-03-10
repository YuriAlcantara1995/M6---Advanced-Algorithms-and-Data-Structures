#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
const int MAXN=505;
int D[MAXN];
priority_queue<par,vector<par>,greater<par>>q;
vector<par>ady[MAXN];

void Dijkstra(int start)
{
    D[start]=0;
    q.push(par(0,start));

    while(!q.empty())
    {
        int cos = q.top().first;
        int nod = q.top().second;
        q.pop();

        for(auto x:ady[nod])
        {
            int nn = x.first;
            int nc = x.second;
            if(D[nn] > cos+nc)
            {
                D[nn] = cos+nc;
                q.push(par(D[nn],nn));
            }
        }
    }
}

int main() {

    int N,M,A,B;
    cin >> N >> M >> A >> B;

    for(int i=1;i<=N;i++)
        D[i]=1<<30;

    int a,b,c;
    for(int i=1;i<=M;i++)
    {
        cin >> a >> b >> c;
        ady[a].push_back(par(b,c));
        ady[b].push_back(par(a,c));
    }

    Dijkstra(A);

    if(D[B] != 1<<30)
        cout << D[B] << '\n';
    else
        cout << "-1\n";

    return 0;
}
