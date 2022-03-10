#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
int A[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    for(int i=1;i<=N;i++)
        cin >> A[i];

    int M;
    cin >> M;

    for(int i=1;i<=M;i++)
    {
        int b;
        cin >> b;

        int I=1,F=N,sol=-1;
        while(I<=F)
        {
            int piv=(I+F)/2;
            if(A[piv]<=b)
            {
                if(A[piv]==b)
                    sol=piv;
                I=piv+1;
            }
            else
                F=piv-1;
        }

        if(i==M)
            cout << sol << '\n';
        else
            cout << sol << ' ';
    }



    return 0;
}