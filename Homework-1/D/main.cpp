#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e3+5;
int N,K;
int A[MAXN];

bool can(int X)
{
    int c=0;
    for(int i=1;i<=N;i++)
        c+=A[i]/X;

    return c>=K;
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N >> K;

    for(int i=1;i<=N;i++)
        cin >> A[i];

    int I=1,F=100000,sol=0;

    while(I<=F)
    {
        int piv=(I+F)/2;
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
