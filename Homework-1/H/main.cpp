#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-9;

const int MAXN=1e5+5;
int N;
int X[MAXN],V[MAXN];

bool can(double T)
{
    double l=-1e9,r=1e9;

    for(int i=1;i<=N;i++)
    {
        double nl = X[i] - T * V[i];
        double nr = X[i] + T * V[i];
        if(r < nl || nr < l)
            return false;

        l=max(l,nl);
        r=min(r,nr);
    }

    return true;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> N;

    for(int i=1;i<=N;i++)
        cin >> X[i];

    for(int i=1;i<=N;i++)
        cin >> V[i];

    double I=0.,F=1e9,sol=1e9;

    int iteration=300;
    while(iteration--)
    {
        double piv=(I+F)/2.;
        if(can(piv))
        {
            sol=piv;
            F=piv;
        }
        else
        {
            I=piv;
        }
    }

    cout << fixed << setprecision(9) << sol << '\n';

    return 0;
}
