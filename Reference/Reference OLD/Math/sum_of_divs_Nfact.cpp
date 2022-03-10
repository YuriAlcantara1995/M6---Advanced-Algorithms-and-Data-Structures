#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 5e4 + 1;
const LL MOD = 1e9 + 7;

bool comp[MAXN];
vector<int> primes;
LL fact[MAXN];

void Criba(){
	for (int i = 4 ; i < MAXN ; i += 2)
		comp[i] = true;

	for (int i = 3 ; i * i < MAXN ; i += 2)
		if (!comp[i])
			for (int j = i * i ; j < MAXN ; j += 2 * i)
				comp[j] = true;

	primes.push_back(2);
	for (int i = 3 ; i < MAXN ; i += 2)
		if (!comp[i])
			primes.push_back(i);

	primes.push_back(MAXN);//centinela
}

LL E(int N, int p){
	LL r = 0;
	while (N / p > 0){
		r += N / p;
		N /= p;
	}
	return r;
}

LL ModExp(int b, int e){
	if (e == 0)
		return 1LL;
	if (e & 1)
		return ModExp(b, e - 1) * b % MOD;
	LL r = ModExp(b, e >> 1);
	return r * r % MOD;
}

LL InvMod(int p){
	LL r = ModExp(p, MOD - 2);
	return r;
}

int main(){
	Criba();

	fact[0] = 1;
	for (int i = 1 ; i < MAXN ; i++)
		fact[i] = (fact[i - 1] * i) % MOD;

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freopen("sumd.in", "r", stdin);
	freopen("sumd.out", "w", stdout);

    int N;
    cin >> N;

    LL sol = 1;
    for (int i = 0 ; primes[i] <= N ; i++){
        LL e = E(N, primes[i]);

        LL f = ModExp(primes[i], e + 1) - 1;
        sol *= f;
        sol %= MOD;
        sol *= InvMod(primes[i] - 1);
        sol %= MOD;
    }

    sol -= fact[N];
    sol += MOD;
    sol %= MOD;

    cout << sol << '\n';

	return 0;
}
