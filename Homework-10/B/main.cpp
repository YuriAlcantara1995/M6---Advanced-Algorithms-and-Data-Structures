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

    string S;
    cin >> S;

    int N = S.length();
    prefix_function(S);

    for(int i=0;i<N-1;i++)
        cout << PF[i] << ' ';
    cout << PF[N-1] << '\n';

    return 0;
}
