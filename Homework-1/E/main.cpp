#include <bits/stdc++.h>
using namespace std;

int N,a,b;

bool can(int X)
{
    int f=X/a;
    int c=X/b;

    return f*c>=N;
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int T;
    cin >> T;

    while(T--)
    {
        cin >> N >> a >> b;
        int I=1, F=N*max(a,b), sol=N*max(a,b);
        while(I<=F)
        {
            int piv=(I+F)/2;
            if(can(piv))
            {
                sol=piv;
                F=piv-1;
            }
            else
                I=piv+1;
        }

        cout << sol << '\n';
    }

    return 0;
}
