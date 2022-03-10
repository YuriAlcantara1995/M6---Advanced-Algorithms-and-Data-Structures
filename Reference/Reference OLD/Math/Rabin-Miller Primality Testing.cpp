Rabin-Miller primality testing

#include <cstdio>

typedef unsigned long long ull;

#define MAXP 10

const int prime[MAXP] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

int T;
ull N;

ull mul( ull a, ull b, ull m ) {

  if ( !b ) return 0;

  ull ret = 2 * mul( a, b / 2, m ) % m;
  if ( b % 2 ) ret = ( ret + a ) % m;

  return ret;
}

ull power( ull x, ull n, ull m ) {

  ull ret = 1;

  for ( ; n; x = mul( x, x, m ), n /= 2 )
    if ( n % 2 ) ret = mul( ret, x, m );

  return ret;
}

bool rabin_miller( ull p ) {

  if ( p < 2 || ( p > 2 && !( p % 2 ) ) )
    return false;

  for ( int i = 0; i < MAXP && prime[i] < p; i++ )
    if ( power( prime[i], p - 1, p ) != 1 )
      return false;

  return true;
}

int main() {

  for ( scanf( "%d", &T ); T; T-- ) {
    scanf( "%lld", &N );
    printf( rabin_miller( N ) ? "YES\n" : "NO\n" );
  }

  return 0;
}//melkor
