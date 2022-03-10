const int mod = 167772161;
// so the algorithm works until n = 2 ^17 = 131072
const int G = 3; // primitive root
//const int MOD = 1073872897 = 2  ^ 30 + 2 ^ 17 + 1, g = 7
// another good choice is MOD = 167772161 = 2^27+2^25+1, g = 3
// a bigger choice would be MOD = 3221225473 = 2^31+2^30+1, g = 5
// but it requires unsigned long long for multiplications
// n must be a power of two
// sign = 1
// sign = -1
// fast modulo transform
//   (1) n = 2^k < 2^23
//   (2) only predetermined mod can be used
//   (3) Inverso Modular */
void fmt(vector<ll> &x, int sign = +1){
	int n = x.size();	
	for (int i = 0, j = 1; j < n - 1; ++j){
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(x[i], x[j]);
	}
	ll h = pow(G, (mod - 1) / n, mod);
	if (sign < 0) h = inv(h, mod);
	for (int m = 1; m < n; m *= 2){
		ll w = 1, wk = pow(h, n / (2 * m), mod);
		for (int i = 0; i < m; ++i){
			for (int j = i; j < n; j += 2 * m){
				ll u = x[j], d = ( x[j + m] * w ) % mod;
				x[j] = (u + d)%mod;
				x[j + m] = (u - d + mod)%mod;
			}
			w = w * wk % mod;
		}
	}
	if (sign < 0){
		ll n_inv = inv(n, mod);
		for (auto &a : x) a = (a * n_inv) % mod;
	}
}