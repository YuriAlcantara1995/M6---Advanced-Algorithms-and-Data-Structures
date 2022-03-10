#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 5e4+5;
int N,M,K;
ll A[MAXN],B[MAXN];

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N >> M >> K;
    for(int i=1;i<=N;i++)
        cin >> A[i];
    sort(A+1,A+N+1);

    for(int i=1;i<=M;i++)
        cin >> B[i];
    sort(B+1,B+M+1);

    ll I=A[1]+B[1], F=A[N]+B[M], sol=-1;
    while(I<=F)
    {
        ll piv=(I+F)/2;
        int al=0;
        int p=M+1;
        for(int i=1;i<=N && p>1;i++)
        {
            while(B[p-1] + A[i] >= piv && p>1)
                p--;

            al+=p-1;
        }

        if(al<K)
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
