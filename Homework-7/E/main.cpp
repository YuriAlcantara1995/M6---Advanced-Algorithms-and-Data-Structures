#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
const int MAXN=5e3+5;
int D[MAXN];
int V[MAXN];
vector<int>ady[MAXN];

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int T;
    cin >> T;

    while(T--)
    {
        int N,M,S,T;
        cin >> N >> M >> S >> T;

        for(int i=1;i<=N;i++)
        {
            cin >> V[i];
            D[i]=1<<30;
            ady[i].clear();
        }

        int a,b;
        for(int i=1;i<=M;i++)
        {
            cin >> a >> b;
            ady[a].push_back(b);
            ady[b].push_back(a);
        }

        priority_queue<par,vector<par>,greater<par>>q;
        D[S]=V[S];
        q.push(par(V[S],S));

        bool exist = false;
        while(!q.empty())
        {
            int nod = q.top().second;
            int cos = q.top().first;
            q.pop();

            if(nod == T)
            {
                cout << cos << '\n';
                exist = true;
                break;
            }

            for(auto nn:ady[nod])
            {
                if(D[nn] > cos + V[nn])
                {
                    D[nn] = cos + V[nn];
                    q.push(par(D[nn],nn));
                }
            }
        }
        if(!exist)
            cout << "-1\n";
    }


    return 0;
}
