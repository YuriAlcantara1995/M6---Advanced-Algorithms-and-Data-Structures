#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN=505;
ll C[MAXN];
typedef pair<ll,ll>par;
priority_queue<par,vector<par>,greater<par>>q;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=M;i++)
        cin >> C[i];

    sort(C+1,C+M+1);

    for(int i=1;i<=M;i++)
        q.push(par(C[i],i));

    ll sol = 0;
    while(N--)
    {
        par x=q.top();
        q.pop();
        sol+=x.first;

        for(int i=x.second;i<=M;i++)
            q.push(par(x.first+C[i],i));
    }

    cout << sol << '\n';

    return 0;
}
