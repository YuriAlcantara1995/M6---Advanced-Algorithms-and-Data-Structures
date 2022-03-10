#include <bits/stdc++.h>
using namespace std;

typedef vector<int>vi;
const int MAXN = 3e5+5;
int B[MAXN],L[MAXN];

int find_level(int nod)
{
    if(B[nod] == nod)
        return L[nod] = 0;
    L[nod] = L[nod] + find_level(B[nod]);
    B[nod] = B[B[nod]];

    return L[nod];
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=N;i++)
        B[i]=i,L[i]=0;

    int t,a,b;
    for(int i=1;i<=M;i++)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            cin >> a >> b;
            B[a]=b;
            L[a]=L[b]+1;
        }
        else
        {
            cin >> a;
            cout << find_level(a) << '\n';
        }
    }

    return 0;
}
