inline ll mulmod(ll a, ll b, ll m) {
	ll x = 0, y = a % m;
	for( ; b ; b >>= 1 ){
		if( b & 1 ) x = (x + y) % m;
		y = (y * 2) % m;
	}
	return x;
}