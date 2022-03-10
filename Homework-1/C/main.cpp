#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
int A[MAXN],B[MAXN];

int main() {

    int N;
    cin >> N;

    for(int i=1;i<=N;i++)
        cin >> A[i];

    sort(A+1,A+N+1);
    A[N+1]=1<<30;

    int M;
    cin >> M;
    for(int i=1;i<=M;i++)
    {
        int b;
        cin >> b;

        int I=1,F=N+1,sol=N+1;
        while(I<=F)
        {
            int piv=(I+F)/2;
            if(A[piv]<=b)
                I=piv+1;
            else
            {
                sol=piv;
                F=piv-1;
            }
        }

        if(sol==1)
            cout << A[sol]-b << '\n';
        else
            if(sol==N+1)
                cout << b-A[sol-1] << '\n';
            else
                cout << min(b-A[sol-1],A[sol]-b) << '\n';
    }


    return 0;
}
