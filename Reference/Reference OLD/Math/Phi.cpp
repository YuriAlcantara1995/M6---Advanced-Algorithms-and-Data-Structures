// computes the number of coprimes of p^k, being p prime
//int phi(int p, int k) { return pow(p, k) - pow(p, k-1); } // phi(p^k)
int phi(int p, int pk) { return pk - (pk/p); } // phi(p^k), where pk=p^k
// computes the number of coprimes of n
// phi(n) = (p_1 - 1) * p_1 ^ (k_1 - 1) * (p_2 - 1) * p_2 ^ (k_2-1)
int phi(int n){
    int coprimes = (n != 1); // phi(1) = 0
    for (int i = 2; i*i <= n; i++)
        if (n%i == 0){
            int pk = 1;
            while (n%i == 0)
                n /= i, pk *= i;
            coprimes *= phi(i, pk);
        }
    if (n > 1) coprimes *= phi(n, n); // n is prime
    return coprimes;
}
