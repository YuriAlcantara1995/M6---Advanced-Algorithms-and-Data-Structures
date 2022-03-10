#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e2+10;

int N,K;
int A[MAXN];

bool can(int X)
{
    int cpu_needed=0;
    int s=0;
    for(int i=1;i<=N;i++)
    {
        s+=A[i];
        if(s>X)
        {
            s=A[i];
            cpu_needed++;
        }
    }
    if(s>0)
        cpu_needed++;

    return cpu_needed <= K;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N >> K;
    int maxi=0;
    for(int i=1;i<=N;i++)
    {
        cin >> A[i];
        maxi=max(maxi,A[i]);
    }

    int I=maxi,F=1<<30,sol=1<<30;

    while(I<=F)
    {
        int piv=(I+F)/2;
        if(can(piv))
        {
            sol=piv;
            F=piv-1;
        }
        else
            I=piv+1;
    }

    cout << sol << '\n';

    return 0;
}
