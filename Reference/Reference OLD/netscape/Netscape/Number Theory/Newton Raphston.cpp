double eval(double P[],int n,  double x){
	double r = 0;
	for(int i = n - 1; i >=0; i--){
		r*=x;
		r+=P[i];
	}
	return r;
}
int main() {
    int test = 1, n;
    while(scanf("%d", &n) && n) {
        double a[10] = {};
        for(int i = n; i >= 0; i--) scanf("%lf", &a[i]);
        double ret[10];
        int m = n;
        for(int i = 0; i < m; i++) {
            double b[10] = {};   // f'(x)
            for(int j = 0; j <= n; j++)
                b[j] = a[j+1]*(j+1);
            double x = 25, tx;  //max_value
            if(i)   x = ret[i-1];
            while(true) {
                double fx =eval(a,n+1,x),ffx =eval(b,n,x);
                tx = x - fx/ffx;
                if(fabs(fx) < 1e-8)
                    break;
                x = tx;
            }
            ret[i] = x;
            for(int j = n; j >= 0; j--)
                a[j] = a[j] + a[j+1]*x;
            for(int j = 0; j <= n; j++)
                a[j] = a[j+1];
            n--;
        }
        printf("Equation %d:", test++);
        n = m;
        sort(ret, ret+n);
        for(int i = 0; i < n; i++) printf(" %.4lf", ret[i]);
        printf("\n");
    }
}
