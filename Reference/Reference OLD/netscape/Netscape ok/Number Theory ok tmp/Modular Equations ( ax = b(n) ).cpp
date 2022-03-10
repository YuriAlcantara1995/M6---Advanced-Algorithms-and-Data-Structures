/* Modular Linear Equation Solver O(log(n))
 * Given a, b and n, solves the equation ax = b(n)
 * for x. Returns the vector of solutions, all smaller
 * than n and sorted in increasing order. */
vector< int > msolve( int a, int b, int n ){
    if( n < 0 ) n = -n;
	int d, x, y;
    d = extended_euclid( a, n, x, y );
    vector< int > r;
    if( b % d ) return r;
    int x0 = ( b / d * x ) % n;
    if( x0 < 0 ) x0 += n;
	x0 = x0 % (n / d);
    for( int i = 0; i < d; i++ )
        r.push_back( ( x0 + i * n / d ) % n );
    return r;
}