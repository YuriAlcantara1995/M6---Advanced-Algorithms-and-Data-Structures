ifact[n+1] = fact[n+1]^(mod-2)
ifact[n] = (ifact[n+1]*(n+1))%mod;