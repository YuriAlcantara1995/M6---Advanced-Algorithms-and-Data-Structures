void compute(int k, int L, int R, int optL, int optR){
	if (L > R) return;
	int m = (L + R) / 2, opt = -1;
	dp[m][1] = oo;
	for (int i = optL; i <= min(m, optR); i++){
		i64 t = dp[i - 1][0] + w(i, m);
		if (dp[m][1] > t)
			dp[m][1] = t, opt = i;
	}
	compute(k, L, m - 1, optL, opt);
	compute(k, m + 1, R, opt, optR);
}