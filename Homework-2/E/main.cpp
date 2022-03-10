#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll>par;
priority_queue<par,vector<par>,greater<par>>q;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    for(int i=1;i<=N;i++)
    {
        par x;
        cin >> x.first >> x.second;
        q.push(x);
    }

    int K;
    cin >> K;

    while(K--)
    {
        par x = q.top();
        if(K==0)
            cout << x.first << '\n';
        else
            cout << x.first << ' ';

        q.pop();
        q.push(par(x.first+x.second,x.second));
    }

    return 0;
}
