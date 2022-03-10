#define PI acos(-1)
typedef complex<double> base;
void fft (vector<base> & a, int invert){
	int n = (int) a.size();
	for (int i = 1, j = 0; i < n-1; ++i){
		for (int k = n >> 1; (j ^= k) < k; k >>= 1);
		if (i < j) swap(a[i], a[j]);
	}
	for (int len=2; len <= n; len<<=1) {
		double ang = 2*PI/len * invert;
		base wlen(cos(ang), sin(ang)), w(1);
		for (int i=0; i < n; i += len, w = base(1) )
			for (int j=0; j<len/2; ++j, w *= wlen ){
				base u = a[i+j], v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
	}		}
	if (invert == -1){ for (int i=0; i<n; ++i) a[i] /= n; }
} //a la hora de conv. de complex a int real + o - 0.5