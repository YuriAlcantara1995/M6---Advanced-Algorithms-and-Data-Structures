#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
priority_queue<ll,vector<ll>,less<ll>>q;

int main() {

    ll a0,a1,A,B,C,M;
    cin >> a0 >> a1 >> A >> B >> C >> M;

    ll l,r,k;
    cin >> l >> r >> k;

    if(l==0)q.push(a0);
    if(l<=1)q.push(a1);

    for(int i=2;i<=r;i++)
    {
        int ai = (A * a0 + B * a1 + C) % M;
        a0 = a1;
        a1 = ai;
        if(i>=l)
            q.push(ai);

        while(q.size()>k)q.pop();
    }

    vector<int>v;
    while(k--)
    {
        v.push_back(q.top());
        q.pop();
    }

    reverse(v.begin(),v.end());
    for(int i=0;i<v.size()-1;i++)
        cout << v[i] << ' ';
    cout << v[v.size()-1] << '\n';

    return 0;
}
