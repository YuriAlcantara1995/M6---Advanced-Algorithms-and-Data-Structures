#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
int Z[MAXN];

int N;

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

bool can(int pos)
{
    return Z[N+pos+1] == N-pos;
}

int main() {
    cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    string S,T;
    cin >> S >> T;
    N=S.length();
    string RT=T;
    reverse(RT.begin(),RT.end());

    Z_function(T+"#"+S);

    for(int i=-1;i<N-1;i++)
    {
        if(i>=0 && S[i]!=RT[i])
            break;
        if(can(i+1))
        {
            cout << "Yes\n";
            cout << i+1 << '\n';
            return 0;
        }
    }

    cout << "No\n";



    return 0;
}
