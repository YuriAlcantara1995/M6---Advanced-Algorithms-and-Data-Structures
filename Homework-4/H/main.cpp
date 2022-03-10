#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN=1e5+5;
int A[MAXN];
ll STS[4*MAXN];
ll STWS[4*MAXN];
ll lazyS[4*MAXN];
bool mark[4*MAXN];

ll tsum(ll l, ll r)
{
    return (r*(r+1ll))/2ll -  (l*(l-1ll))/2ll;
}

void push(int nod, int I, int F)
{
    if(mark[nod]==false)
        return;

    lazyS[2*nod]+=lazyS[nod];
    lazyS[2*nod+1]+=lazyS[nod];
    mark[2*nod]=true;
    mark[2*nod+1]=true;

    int piv = (I+F)/2;
    STWS[2*nod]+=lazyS[nod]*tsum(I,piv);
    STWS[2*nod+1]+=lazyS[nod]*tsum(piv+1,F);
    STS[2*nod]+=lazyS[nod]*(piv-I+1);
    STS[2*nod+1]+=lazyS[nod]*(F-piv);

    mark[nod]=false;
    lazyS[nod]=0;

}

void build(int nod,int I, int F)
{
    if(I == F)
    {
        STWS[nod]=1ll*A[I]*I;
        STS[nod]=1ll*A[I];
    }
    else
    {
        int piv=(I+F)/2;
        build(2*nod,I,piv);
        build(2*nod+1,piv+1,F);

        STS[nod]=STS[2*nod] + STS[2*nod+1];
        STWS[nod]=STWS[2*nod] + STWS[2*nod+1];
    }
}

ll queryS(int nod, int I, int F, int l, int r)
{
    if(F<l || I>r)
        return 0;

    if(I>=l && F<=r)
        return STWS[nod] - STS[nod]*(l-1ll);

    int piv=(I+F)/2;
    push(nod,I,F);

    ll al = queryS(2*nod,I,piv,l,r);
    ll ar = queryS(2*nod+1,piv+1,F,l,r);

    return al+ar;
}

void update(int nod, int I, int F, int l, int r, ll d)
{
    if(F<l || I>r)
        return;

    if(I>=l && F<=r)
    {
        STS[nod]+=d*(F-I+1);
        STWS[nod]+=d*tsum(I,F);
        lazyS[nod]+=d;
        mark[nod]=true;
    }
    else
    {
        push(nod,I,F);
        int piv = (I+F)/2;
        update(2*nod,I,piv,l,r,d);
        update(2*nod+1,piv+1,F,l,r,d);

        STS[nod]=STS[2*nod] + STS[2*nod+1];
        STWS[nod]=STWS[2*nod] + STWS[2*nod+1];
    }

}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,Q;
    cin >> N >> Q;

    for(int i=1;i<=N;i++)
        cin >> A[i];

    build(1,1,N);

    int l,r;
    ll d;
    while(Q--)
    {
        int o;
        cin >> o;
        if(o == 1)
        {
            cin >> l >> r >> d;
            update(1,1,N,l,r,d);
        }
        else
        {
            cin >> l >> r;
            cout << queryS(1,1,N,l,r) << '\n';
        }
    }

    return 0;
}
