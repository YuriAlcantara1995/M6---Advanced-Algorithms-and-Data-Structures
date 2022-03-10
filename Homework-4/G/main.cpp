#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN=2e5+5;
ll lazyA[4*MAXN];
ll lazyD[4*MAXN];
ll lazyDL[4*MAXN];
bool mark[4*MAXN];

void push(int nod)
{
    if(mark[nod]==false)
        return;

    lazyA[2*nod]+=lazyA[nod];
    lazyD[2*nod]+=lazyD[nod];
    lazyDL[2*nod]+=lazyDL[nod];
    mark[2*nod]=true;

    lazyA[2*nod+1]+=lazyA[nod];
    lazyD[2*nod+1]+=lazyD[nod];
    lazyDL[2*nod+1]+=lazyDL[nod];
    mark[2*nod+1]=true;

    lazyA[nod] = 0;
    lazyD[nod] = 0;
    lazyDL[nod] = 0;
    mark[nod]=false;
}

ll query(int nod,int I,int F, int pos)
{
    if(F<pos || I>pos)
        return 0;

    if(I == F)
        return lazyA[nod] + I*lazyD[nod] + lazyDL[nod];

    int piv=(I+F)/2;
    push(nod);

    ll al = query(2*nod,I,piv,pos);
    ll ar = query(2*nod+1,piv+1,F,pos);

    return al+ar;
}

void update(int nod, int I, int F, int l, int r, ll a, ll d)
{
    if(F<l || I>r)
        return;

    if(I>=l && F<=r)
    {
        lazyA[nod]+=a;
        lazyD[nod]+=d;
        lazyDL[nod]+=-d*l;
        mark[nod]=true;
    }
    else
    {
        push(nod);
        int piv = (I+F)/2;
        update(2*nod,I,piv,l,r,a,d);
        update(2*nod+1,piv+1,F,l,r,a,d);
    }

}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    int l,r,pos;
    ll a,d;
    while(M--)
    {
        int o;
        cin >> o;
        if(o == 1)
        {
            cin >> l >> r >> a >> d;
            update(1,1,N,l,r,a,d);
        }
        else
        {
            cin >> pos;
            cout <<  query(1,1,N,pos) << '\n';
        }
    }

    return 0;
}
