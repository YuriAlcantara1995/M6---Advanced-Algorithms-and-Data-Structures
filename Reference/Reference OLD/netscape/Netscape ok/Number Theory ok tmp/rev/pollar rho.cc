#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;

//return a * b % m
ull mul_mod(ull a, ull b, ull m)
{
	ull res = 0, tmp = a % m;
	while (b)
	{
		if (b & 1)
		{
			res = res + tmp;
			res = (res >= m ? res - m : res);
		}
		b >>= 1;
		tmp <<= 1;
		tmp = (tmp >= m ? tmp - m : tmp);
	}
	return res;
}

//return a ^ b % m
ll exp_mod(ll a, ll b, ll m)
{
	ll res = 1 % m, tmp = a % m;
	while (b)
	{
		if (b & 1)
		{
			//res = (res * t) % m;
			res = mul_mod(res, tmp, m);
		}
		//t = t * t % m;
		tmp = mul_mod(tmp, tmp, m);
		b >>= 1;
	}
	return res;
}

bool Miller_Rabin(ll n)
{
	int a[5] = { 2, 3, 7, 61, 24251 };

	if (n == 2) return true;
	if (n == 1 || (n & 1) == 0) return false;

	ll b = n - 1;

	for (int i = 0; i < 5; i++)
	{
		if (a[i] >= n) break;

		while ((b & 1) == 0) b >>= 1;

		ll t = exp_mod(a[i], b, n);

		while (b != n - 1 && t != 1 && t != n - 1)
		{
			t = mul_mod(t, t, n);
			b <<= 1;
		}

		if (t == n - 1 || (b & 1)) continue;
		else return false;
	}
	return true;
}

ll factor[100];
ll nfactor, minfactor;

ll gcd(ll a, ll b)
{
	return b ? gcd(b, a%b) : a;
}

void Factor(ll n);

void pollard_rho(ll n)
{
	if (n <= 1) return;
	if (Miller_Rabin(n))
	{
		factor[nfactor++] = n;
		if (n < minfactor) minfactor = n;
		return;
	}
	ll x = 2 % n, y = x, k = 2, i = 1;
	ll d = 1;
	while (true)
	{
		i++;
		x = (mul_mod(x, x, n) + 1) % n;
		d = gcd((y - x + n) % n, n);
		if (d > 1 && d < n)
		{
			pollard_rho(d);
			pollard_rho(n / d);
			return;
		}
		if (y == x)
		{
			Factor(n);
			return;
		}
		if (i == k)
		{
			y = x;
			k <<= 1;
		}
	}
}

void Factor(ll n)
{
	ll d = 2;
	while (n % d != 0 && d * d <= n) d++;
	pollard_rho(d);
	pollard_rho(n / d);
}

// return true if n is prime
// nfactor is the size

bool factorize(ll n)
{
	nfactor = 0;
	minfactor = (1LL << 63);
	pollard_rho(n);
	if (nfactor == 1 && factor[0] == n)
	{
		return true;
	}
	sort(factor, factor + nfactor);
	return false;
}


int main()
{
    #ifdef acm
    freopen("a.in", "r", stdin);
    #endif // acm

    cin.tie();
    ios_base::sync_with_stdio(false);

    int T;
    ll n;
    cin >> T;
    while(  T-- ){
        cin >> n;
        factorize( n);
        for (int i = 0; i < nfactor; i++)
            cout << factor[i] << ' ';
        cout << '\n';
    }

    return 0;
}