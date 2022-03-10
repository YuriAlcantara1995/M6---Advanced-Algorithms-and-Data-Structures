#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e6+5;
int Z[MAXN];

void Z_function(string S) {
    int N = (int) S.length();
    
    for (int i = 1, l = 0, r = 0; i < N; ++i) {
        if (i <= r)
            Z[i] = min (r - i + 1, Z[i - l]);
        while (i + Z[i] < N && S[Z[i]] == S[i + Z[i]])
            ++Z[i];
        if (i + Z[i] - 1 > r)
            l = i, r = i + Z[i] - 1;
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    string S;
    cin >> S;

    int N = S.length();
    Z_function(S);

    for(int i=0;i<N-1;i++)
        cout << Z[i] << ' ';
    cout << Z[N-1] << '\n';

    return 0;
}
