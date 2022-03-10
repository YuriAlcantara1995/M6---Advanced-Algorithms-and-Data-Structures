#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e4+5;
int N;
int X[MAXN], T[MAXN];

double f(double x)
{
    double p=0;
    for(int i=1;i<=N;i++)
    {
        double d=abs(x-X[i]);
        if(T[i]==1)
            p+=d;
        else
        if(T[i]==2)
            p+=d*log(d+1);
        else
        if(T[i]==3)
            p+=d*sqrt(d);
        else
            p+=d*d;
    }

    return p;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for(int i=1;i<=N;i++)
        cin >> X[i] >> T[i];

    int iterations = 300;
    double l=-1e6,r=1e6;
    while (iterations--) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1);
        double f2 = f(m2);
        if (f1 > f2)
            l = m1;
        else
            r = m2;
    }

    cout << fixed << setprecision(9) << f(l) << '\n' << l << '\n';

    return 0;
}
