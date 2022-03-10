#include <bits/stdc++.h>
using namespace std;

double C;
double f(double X)
{
    return 4*X + 8*log(X+1) + X*log(X+1) - C;
}

int main() {

    cin >> C;

    double l=0,r=1e9;              //set the error limit here
    int iteration=300;
    while (iteration--) {
        double piv = (l + r) / 2.;
        if (f(piv) > 0)
            r = piv;
        else
            l = piv;
    }

    cout <<  fixed << setprecision(9) << l << '\n';

    return 0;
}
