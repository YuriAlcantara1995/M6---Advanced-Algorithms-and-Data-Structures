#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4e5+5;
int L[MAXN],R[MAXN];
typedef pair<int,int>par;
par E[MAXN];

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int N,M;
    cin >> N >> M;

    for(int i=1;i<=N;i++)
        cin >> L[i] >> R[i];

    for(int i=1;i<=M;i++)
        cin >> E[i].first >> E[i].second;




    return 0;
}
