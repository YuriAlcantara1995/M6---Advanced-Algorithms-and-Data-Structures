//mcd(n,m)==1
int inverso_mod(int n ,int m){
    int s, t, d;
	d = extended_euclid( n, m, s, t );
	return ((s % m)+m)% m;
}