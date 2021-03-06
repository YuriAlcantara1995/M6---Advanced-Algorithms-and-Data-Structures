int resto_chino (vector<int> x, vector<int> m, int k){
    int i, tmp, MOD = 1, RES = 0;
    for (i=0; i <k ; i++) MOD *= m[i];
    for (i =0; i <k ; i++){
        tmp = MOD/m[i];
        tmp *= inverso_mod(tmp, m[i]);
        RES += (tmp*x[i]) % MOD;
    }
    return RES % MOD;
}