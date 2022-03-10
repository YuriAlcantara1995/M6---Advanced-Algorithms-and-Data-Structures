ll phi(ll p, ll pk) { return pk - (pk/p); }
ll phi(ll n){
    ll coprimes = (n != 1); // phi(1) = 0
    if (n%2 == 0){
        ll pk = 1;
        while (n%2 == 0) n /= 2, pk *= 2;
        coprimes *= phi(2, pk);
    }
    for (ll i = 3; i*i <= n; i+=2)
        if (n%i == 0){
            ll pk = 1;
            while (n%i == 0) n /= i, pk *= i;
            coprimes *= phi(i, pk);
        }
    if (n > 1) coprimes *= phi(n, n); // n is prime
    return coprimes;
}