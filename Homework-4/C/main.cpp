#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN=2e5+5;
int N;
ll A[MAXN];
ll STM[4*MAXN];
ll STS[4*MAXN];

void build(int nod, int I, int F)
{
    if(I==F)
    {
        STM[nod]=I;
        STS[nod]=1;
    }
    else
    {
        int piv=(I+F)/2;
        build(2*nod,I,piv);
        build(2*nod+1,piv+1,F);

        STS[nod]=STS[2*nod] + STS[2*nod+1];
        if(A[STM[2*nod]] < A[STM[2*nod+1]])
            STM[nod] = STM[2*nod];
        else
            STM[nod] = STM[2*nod+1];
    }
}

void update(int nod,int I,int F,int pos)
{
    if(F<pos || I>pos) return;

    if(I==F)
    {
        A[I]=1<<30;
        STS[nod]=0;
        return;
    }

    int piv=(I+F)/2;

    update(2*nod,I,piv,pos);
    update(2*nod+1,piv+1,F,pos);

    STS[nod]=STS[2*nod] + STS[2*nod+1];
    if(A[STM[2*nod]] < A[STM[2*nod+1]])
        STM[nod] = STM[2*nod];
    else
        STM[nod] = STM[2*nod+1];

}

ll queryM(int nod,int I,int F, int l,int r)
{
    if(I>=l && F<=r)
        return STM[nod];
    if(F<l || I>r)
        return -1;

    int piv=(I+F)/2;

    int la = queryM(2*nod,I,piv,l,r);
    int ra = queryM(2*nod+1,piv+1,F,l,r);

    if(la == -1 || A[ra]<=A[la])
        return ra;

    return la;
}

ll queryS(int nod,int I,int F, int l,int r)
{
    if(I>=l && F<=r)
        return STS[nod];
    if(F<l || I>r)
        return 0;

    int piv=(I+F)/2;

    int la = queryS(2*nod,I,piv,l,r);
    int ra = queryS(2*nod+1,piv+1,F,l,r);

    return la + ra;
}

int main() {

    cin >> N;
    for(int i=1;i<=N;i++)
        cin >> A[i];

    build(1,1,N);

    int Q = N;
    while(Q--)
    {
        int p = queryM(1,1,N,1,N);

        if(Q==0)
            cout << queryS(1,1,N,1,p) << '\n';
        else
            cout << queryS(1,1,N,1,p) << ' ';

        update(1,1,N,p);
    }


    return 0;
}
