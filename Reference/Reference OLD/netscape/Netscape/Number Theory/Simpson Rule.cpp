// Error = O( (delta x)^4 )
const int ITR = 1e4; //must be an even number
double Simpson(double a,double b, double f(double)){
	double s = f(a) + f(b), h = (b - a) / ITR;
	for (int i = 1; i < ITR; ++i) {
		double x = a + h * i;
		s += f(x)*( i&1 ? 4 : 2);
	}
	return s * h/3;
}