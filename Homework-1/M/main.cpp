#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e4+5;
int N;
double L,R;
int A[MAXN];

double f(double x)
{
    double p=0;
    double pot=1.;
    for(int i=0;i<=N;i++)
    {
        p+=A[i]*pot;
        pot=pot*x;
    }

    return p;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> L >> R;
    for(int i=0;i<=N;i++)
        cin >> A[i];

    double sol = min(f(L),f(R));
    double sz=(R-L)/100000.;

    for(int i=0;i<=100000;i++)
    {
        double l=min(L+sz*i,R);
        double r=min(l+sz,R);

        int iterations = 300;
        while (iterations--) {
            double m1 = l + (r - l) / 3.;
            double m2 = r - (r - l) / 3.;
            double f1 = f(m1);
            double f2 = f(m2);
            if (f1 > f2)
                l = m1;
            else
                r = m2;
        }

        sol=min(sol,f(l));
    }

    cout << fixed << setprecision(10) << sol << '\n';


    return 0;
}
