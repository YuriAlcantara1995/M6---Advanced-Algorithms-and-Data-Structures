// Miller-Rabin is prime? (probability test)
//using: mulmod( ), powmod()
bool suspect(ll a, int s, ll d, ll n) {
	ll x = powMod(a, d, n);
	if (x == 1)	return true;
	for (int r = 0; r < s; ++r) {
		if (x == n - 1)	return true;
		x = mulmod(x, x, n);
	}
	return false;
}
// {2,7,61,0}                 is for n < 4759123141 (= 2^32)
// {2,3,5,7,11,13,17,19,23,0} is for n < 10^16 (at least)
unsigned test[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 0 };
bool miller_rabin(ll n) {
	if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
	ll d = n - 1; int s = 0;
	while (d % 2 == 0) ++s, d /= 2;
	for (int i = 0; test[i] < n && test[i] != 0; i++)
		if (!suspect(test[i], s, d, n))
			return false;
	return true;
}
