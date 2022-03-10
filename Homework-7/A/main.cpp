#include <bits/stdc++.h>
using namespace std;

typedef vector<int>vi;
const int MAXN = 1e4+5;
typedef pair<int,int>par;
vector<par>ady[MAXN];
int D[MAXN];
vi E[MAXN];

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    int a,b,c;
    for(int i=1;i<=M;i++)
    {
        cin >> a >> b >> c;
        E[i]=vi{a,b,c};
    }

    for(int i=1;i<=N;i++)
        D[i]=1<<30;
    D[1]=0;

    for(int i=1;i<=N-1;i++)
        for(int j=1;j<=M;j++)
        {
            int nod = E[j][0], nn = E[j][1], c = E[j][2];
            if(D[nod] != 1<<30 && D[nn] > D[nod]+c)
                D[nn] = D[nod]+c;
        }

    for(int i=2;i<=N;i++)
        if(D[i] != 1<<30)
            cout << D[i] << '\n';
        else
            cout << "NO\n";

    return 0;
}
