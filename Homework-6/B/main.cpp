#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
typedef long long ll;
ll P[MAXN];

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    ll N,A,B;
    cin >> N >> A >> B;

    for(int i=0;i<N;i++)
        P[i]=-1;
    queue<ll>q;
    P[A]=A;
    q.push(A);
    while(!q.empty())
    {
        ll c = q.front();
        q.pop();

        if(P[(c+1ll)%N] == -1)
        {
            q.push((c+1ll)%N);
            P[(c+1ll)%N]=c;
        }

        if(P[(c*c+1ll)%N] == -1)
        {
            q.push((c*c+1ll)%N);
            P[(c*c+1ll)%N]=c;
        }

        if(P[(c*c*c+1ll)%N] == -1)
        {
            q.push((c*c*c+1ll)%N);
            P[(c*c*c+1ll)%N]=c;
        }
    }

    vector<ll>path;
    ll p=B;
    while(p!=P[p])
    {
        path.push_back(p);
        p=P[p];
    }
    path.push_back(p);
    reverse(path.begin(),path.end());
    cout << path.size()-1 << '\n';
    for(int i=0;i<path.size()-1;i++)
        cout << path[i] << ' ';
    cout << path[path.size()-1] << '\n';

    return 0;
}
