#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1ll<<60;
typedef vector<ll>vi;
const int MAXN = 1e4+5;
ll D[MAXN];
vi E[MAXN];
bool U[MAXN];

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M,S;
    cin >> N >> M >> S;

    ll a,b,c;
    for(int i=1;i<=M;i++)
    {
        cin >> a >> b >> c;
        E[i]=vi{a,b,c};
    }

    for(int i=1;i<=N;i++)
        D[i]=INF;
    D[S]=0;

    for(int i=1;i<=N-1;i++)
        for(int j=1;j<=M;j++)
        {
            ll nod = E[j][0], nn = E[j][1], c = E[j][2];
            if(D[nod] != INF && D[nn] > D[nod]+c)
                D[nn] = D[nod]+c;
        }

    for(int i=1;i<=N-1;i++)
        for(int j=1;j<=M;j++)
        {
            ll nod = E[j][0], nn = E[j][1], c = E[j][2];
            if(D[nod] != INF && D[nn] > D[nod]+c)
            {
                D[nn] = max(-INF,D[nod]+c);
                U[nn]=true;
                U[nod]=true;
            }
    }

    for(int i=1;i<=N;i++)
        if(U[i])
            cout << "-\n";
        else
        if(D[i] != INF)
            cout << D[i] << '\n';
        else
            cout << "*\n";

    return 0;
}
