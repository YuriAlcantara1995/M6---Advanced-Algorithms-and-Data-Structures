circle circumcircle ( const point &a, 
	const point &b, const point &c ) {
	if ( abs( cross( a - c, b - c ) ) > eps  ) {
		point o = three_point_circle ( a, b, c );
		return { o, abs ( o - a ) };
	}	
	point p = min ( { a, b, c } );
	point q = max ( { a, b, c } );
	return circle { (p+q)*0.5, abs(p-q)*0.5 };
}
circle min_enclosing_disk_with_2_points ( vector<point> &p,
				int n, int a, int b ) {
	circle ret =circle {(p[a]+p[b])*0.5,abs(p[a]-p[b])*0.5};
	for ( int i = 0; i <= n; i ++ ) {
		db d = abs ( ret.p - p[i] );
		if ( d <= ret.r + eps ) continue;
		ret = circumcircle ( p[a], p[b], p[i] );
	}
	return ret;
}
circle min_enclosing_disk_with_1_point ( vector<point> &p,
				int n, int a ) {
	circle ret = circle { p[a], 0 };
	for ( int i = 0; i <= n; i ++ ) {
		db d = abs ( ret.p - p[i] );
		if ( d <= ret.r + eps ) continue;
		ret =min_enclosing_disk_with_2_points( p, i, a, i );
	}
	return ret;
}
circle min_enclosing_disk ( vector<point> &p ) {
	srand(42);
	random_shuffle ( p.begin(), p.end() );

	int n = p.size() - 1;
	circle ret = circle { p[0], 0 };
	for ( int i = 1; i <= n; i ++ ) {
		db d = abs ( ret.p - p[i] );
		if ( d <= ret.r + eps ) continue;
		ret = min_enclosing_disk_with_1_point ( p, i, i );
	}
	return ret;
}