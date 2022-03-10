#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e6+5;
int PF[MAXN];

void prefix_function(string S) {
    int N = (int)S.length();

    for (int i = 1; i < N; i++) {
        int j = PF[i-1];
        while (j > 0 && S[i] != S[j])
            j = PF[j-1];
        if (S[i] == S[j])
            j++;
        PF[i] = j;
    }
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    string S,T;
    cin >> S >> T;

    string C = S + "#" + T;
    prefix_function(C);
    int N = C.length();

    cout << (N-1)/2-PF[N-1] << '\n';

    return 0;
}
