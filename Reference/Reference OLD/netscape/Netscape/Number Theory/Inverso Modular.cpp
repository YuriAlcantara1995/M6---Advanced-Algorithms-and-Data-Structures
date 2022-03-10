ll inv(ll b, ll M){ //mcd(b,m)==1
	ll u = 1, x = 0, s = b, t = M;
	while( s ){
		ll q = t / s;
		swap(x -= u * q, u);
		swap(t -= s * q, s);
	}
	return (x %= M) >= 0 ? x : x + M;
}