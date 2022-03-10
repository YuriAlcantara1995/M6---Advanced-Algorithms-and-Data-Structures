#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
int B[MAXN];
int ST[4*MAXN];
int P[MAXN];

void build(int nod, int I, int F)
{
    if(I==F)
        ST[nod]=1;
    else
    {
        int piv = (I+F)/2;
        build(2*nod,I,piv);
        build(2*nod+1,piv+1,F);

        ST[nod]=ST[2*nod] + ST[2*nod+1];
    }
}

void update(int nod,int I, int F, int pos, int val)
{
    if(F<pos || I>pos)
        return;

    if(I==F)
        ST[nod]=val;
    else
    {
        int piv = (I+F)/2;
        update(2*nod,I,piv,pos,val);
        update(2*nod+1,piv+1,F,pos,val);

        ST[nod]=ST[2*nod] + ST[2*nod+1];
    }
}

int query(int nod, int I,int F, int l, int r)
{
    if(F<l || I>r)
        return 0;
    if(I>=l && F<=r)
        return ST[nod];

    int piv = (I+F)/2;

    int al = query(2*nod,I,piv,l,r);
    int ar = query(2*nod+1,piv+1,F,l,r);

    return al+ar;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N;
    cin >> N;

    build(1,1,N);

    for(int i=1;i<=N;i++)
        cin >> B[i];

    for(int i=1;i<=N;i++)
    {
        int I=1,F=N,sol=-1;
        while(I<=F)
        {
            int piv=(I+F)/2;
            int q = query(1,1,N,1,piv);
            if(q>=B[i]+1)
            {
                if(q==B[i]+1)
                    sol=piv;
                F=piv-1;
            }
            else
                I=piv+1;
        }
        P[sol]=i;
        update(1,1,N,sol,0);
    }

    for(int i=1;i<N;i++)
        cout << P[i] << ' ';
    cout << P[N] << '\n';


    return 0;
}
