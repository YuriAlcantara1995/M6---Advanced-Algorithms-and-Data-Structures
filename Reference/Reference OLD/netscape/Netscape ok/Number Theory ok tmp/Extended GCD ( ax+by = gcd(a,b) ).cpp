//devuelve x,y tal que ax+by = gcd(a,b)
int64 extended_euclid( int64 a, int64 b, int64& x, int64& y ) {
  int64 g = a;
  x = 1, y = 0;
  if ( b != 0 ) {
    g = extended_euclid( b, a % b, y, x );
    y -= ( a / b ) * x;
  }
  return g;
}