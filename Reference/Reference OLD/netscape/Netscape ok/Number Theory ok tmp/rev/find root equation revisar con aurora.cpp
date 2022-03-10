/*

template<class F, class G>
double find_root(F f, G df, double x)
{
	for (int iter = 0; iter < 100; ++iter)
	{
		double fx = f(x), dfx = df(x);
		x -= fx / dfx;
		if (fabs(fx) < 1e-12)
			break;
	}
	return x;
}

*/

#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
ll mod = 1e9+9;
#define EPS 1e-9
#define EPS1 1e-6

double n, x1, x2, y11, y2, v, x, y;
double dist(  ){
    return sqrt( (x1-x2)*(x1-x2)+(y11-y2)*(y11-y2) );
}

double PI = acos(-1);

double f(double ang){
    return -1 * 9.8 * x*x /(v*v) +sin(2*ang)*x - 2 * y * cos(ang)*cos(ang);
}
double df(double ang){
    return 2 * x * cos(2*ang) + 2*y * sin(2*ang);
}
double find_root(double x){
	for (int iter = 0; iter < 50; ++iter){
		double fx = f(x), dfx = df(x);
		//cout<<x <<"  "<<fx<<" "<<dfx<<endl;
		x -= fx / dfx;
		if (fabs(fx) < 1e-12)
			break;
	}
	return x;
}

int main()
{
    #ifdef acm
    freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    #endif // acm

    cin.tie();
    ios_base::sync_with_stdio(false);



    while(  scanf("%lf%lf%lf%lf%lf", &x1, &y11, &x2, &y2, &v) != EOF ){
        x = x2-x1;
        y = y2-y11;

        double sol = 5.0;
        for( double i = 0.00; i < PI*0.5; i += PI/50 ){
            double ro = find_root( i );

            if( f(ro) < EPS && ro < sol && ro > EPS )
                sol = ro;
        }
        double d = f( sol );

        if( abs(f( sol )) > EPS ){
            printf("Impossible\n");
            continue;
        }

        printf("%.2lf\n", sol*180.0/PI);

    }

    return 0;
}

