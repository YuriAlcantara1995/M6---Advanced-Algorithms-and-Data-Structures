#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN=2e5+5;
int N;
ll A[MAXN];
ll ST[4*MAXN];

void build(int nod, int I, int F)
{
    if(I==F)
        ST[nod]=A[I];
    else
    {
        int piv=(I+F)/2;
        build(2*nod,I,piv);
        build(2*nod+1,piv+1,F);

        ST[nod]=ST[2*nod] + ST[2*nod+1];
    }
}

void update(int nod,int I,int F,int pos, ll val)
{
    if(F<pos || I>pos) return;

    if(I==F)
    {
        A[I]=val;
        ST[nod]=val;
        return;
    }

    int piv=(I+F)/2;

    update(2*nod,I,piv,pos,val);
    update(2*nod+1,piv+1,F,pos,val);

    ST[nod]=ST[2*nod] + ST[2*nod+1];

}

ll query(int nod,int I,int F, int l,int r)
{
    if(I>=l && F<=r)
        return ST[nod];
    if(F<l || I>r)
        return 0;

    int piv=(I+F)/2;

    return query(2*nod,I,piv,l,r) + query(2*nod+1,piv+1,F,l,r);
}

int main() {

    int Q;
    cin >> N >> Q;
    for(int i=1;i<=N;i++)
        cin >> A[i];

    build(1,1,N);

    while(Q--)
    {
        int t,a,b;
        cin >> t >> a >> b;

        if(t==1)
            update(1,1,N,a,b);
        else
            cout << query(1,1,N,a,b) << '\n';
    }


    return 0;
}
