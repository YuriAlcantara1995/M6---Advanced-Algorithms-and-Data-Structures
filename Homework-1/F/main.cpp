#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll cb,cs,cc;
ll nb,ns,nc;
ll pb,ps,pc;
ll r;

bool can(ll X)
{
    ll b_needed = max(X*cb-nb,0ll);
    ll s_needed = max(X*cs-ns,0ll);
    ll c_needed = max(X*cc-nc,0ll);

    ll amount_money = b_needed*pb + s_needed*ps + c_needed*pc;

    return amount_money <= r;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    string S;
    cin >> S;
    int N=S.length();
    for(int i=0;i<N;i++)
    {
        if(S[i]=='B')
            cb++;
        if(S[i]=='S')
            cs++;
        if(S[i]=='C')
            cc++;
    }
    cin >> nb >> ns >> nc;
    cin >> pb >> ps >> pc;
    cin >> r;

    ll I=1,F=2e12,sol=0;

    while(I<=F)
    {
        ll piv=(I+F)/2;
        if(can(piv))
        {
            sol=piv;
            I=piv+1;
        }
        else
            F=piv-1;
    }

    cout << sol << '\n';

    return 0;
}
