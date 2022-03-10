#include <bits/stdc++.h>
using namespace std;

const int minN=2e5+5;
int A[minN];
int ST[4*minN];
bool mark[4*minN];

void push(int nod)
{
    if(mark[nod]==false)
        return;

    ST[2*nod]=ST[nod];
    mark[2*nod]=true;

    ST[2*nod+1]=ST[nod];
    mark[2*nod+1]=true;

    mark[nod]=false;
}

void build(int nod,int I, int F)
{
    if(I == F)
    {
        ST[nod]=A[I];
    }
    else
    {
        int piv=(I+F)/2;
        build(2*nod,I,piv);
        build(2*nod+1,piv+1,F);

        ST[nod]=min(ST[2*nod],ST[2*nod+1]);
    }
}

int query(int nod,int I,int F, int l, int r)
{
    if(F<l || I>r)
        return 1<<30;

    if(I>=l && F<=r)
        return ST[nod];

    int piv=(I+F)/2;
    push(nod);

    int al = query(2*nod,I,piv,l,r);
    int ar = query(2*nod+1,piv+1,F,l,r);

    return min(al,ar);
}

void update(int nod, int I, int F, int l, int r, int v)
{
    if(F<l || I>r)
        return;

    if(I>=l && F<=r)
    {
        ST[nod]=v;
        mark[nod]=true;
    }
    else
    {
        push(nod);
        int piv = (I+F)/2;
        update(2*nod,I,piv,l,r,v);
        update(2*nod+1,piv+1,F,l,r,v);

        ST[nod] = min(ST[2*nod], ST[2*nod+1]);
    }

}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    for(int i=1;i<=N;i++)
        cin >> A[i];

    build(1,1,N);

    int Q;
    cin >> Q;
    int l,r,v;
    while(Q--)
    {
        int o;
        cin >> o;
        if(o == 1)
        {
            cin >> l >> r;
            cout << query(1,1,N,l,r) << '\n';
        }
        else
        {
            cin >> l >> r >> v;
            update(1,1,N,l,r,v);
        }
    }

    return 0;
}
