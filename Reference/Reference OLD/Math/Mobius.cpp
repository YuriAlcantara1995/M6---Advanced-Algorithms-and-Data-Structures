    //MOBIUS(X) is zero if X is not a square-free integer.
    //MOBIUS(X) is 1 if X is a square-free integer and the number of X's prime divisors is even.
    //MOBIUS(X) is -1 if X is a square-free integer and the number of X's prime divisors is odd.
	
int mobiusMu (Int n) 
{
	int ans = 1 ; 
	
	for (Int d = 2 ; d <= n; ++d) 
	{ 
		if (n % (d * d) == 0 ) 
			return 0; 
		else if (n % d == 0 ) 
			n /= d, ans *= -1; 
	}
	
	return ans; 
} 
	
	for(int i=2; i<=MAXA; i++)
        if(!P[i])
        {
            for(int j=i; j<=MAXA; j+=i)
                if(!P[j])
                    P[j]=i;
        }
		
    MOBIUS[1]=1;
    for(int i=2; i<=MAXA; i++)
        if(P[i]==P[i/P[i]])
            MOBIUS[i]=0;
        else
            MOBIUS[i]=-1 * MOBIUS[i/P[i]];