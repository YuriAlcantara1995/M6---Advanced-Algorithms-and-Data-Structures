//Range Updates and Range Queries using Binary Indexed Trees
void updater( int x, int v ){
 int tmp = x-1;
 for( ; x <= N; x += (x&-x) ){
    Dp[1][x] += v, Dp[2][x] += v*tmp;
 }
}
int sum( int p, int x ){
 int s = 0;
 for( ; x >= 1; x -= (x&-x) )
    s += Dp[p][x];
 return s;
}
int sumsum( int a ){
  return sum( 1, a )*a - sum( 2, a );
}
void updater_interv( int a, int b, int v ){
 updater( a, v ), updater( b+1, -v );
}
