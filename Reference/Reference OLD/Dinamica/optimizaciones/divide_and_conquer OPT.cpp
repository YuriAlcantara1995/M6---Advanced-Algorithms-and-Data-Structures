dp[i][k] = min(dp[j][k-1] + C[j+1][i])
		   j<i
// si se cumple C[i][j] <= C[i][j+1]
void get(int k, int l, int r, int optL, int optR) {
	if(l > r)
		return;
		
	int i = (l + r) >> 1;
	int opt = -1;
	
	for(int j = max(optL, 0); j <= optR && j < i; j++) {
		int ct = dp[j][k-1] + C[j + 1][i];
		
		if(ct < dp[i][k]) {
			dp[i][k] = ct;
			opt = j;
		}
	}
	
	get(k, l, i - 1, optL, opt);
	get(k, i + 1, r, opt, optR);
}

for( int k = 1; k <= K; k++ )
	get(k,1,N,0,N);
	
sol = dp[N][K];
