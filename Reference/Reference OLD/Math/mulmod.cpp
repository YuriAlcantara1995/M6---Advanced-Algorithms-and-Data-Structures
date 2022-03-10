// Modular Multiplication of big numbers
inline ll mulmod(ll a, ll b, ll m) {
	ll x = 0, y = a % m;
	while (b > 0) {
		if (b % 2 == 1)	x = (x + y) % m;
		y = (y * 2) % m;
		b /= 2;
	}
	return x;
}
