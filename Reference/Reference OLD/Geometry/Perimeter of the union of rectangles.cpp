Perimetro de union de rectangulos

using namespace std;

#define MAXC 1 << 17

#define LEFT( v ) 2 * ( v ) + 1
#define RIGHT( v ) 2 * ( v ) + 2

int N, last, size;
long long perimeter;

struct event {
  int start, lo, hi, flag;
  bool operator < ( const event &e ) const { return start < e.start; }
};

vector< event > events[2];

int amount[ 3 * MAXC ], times[ 3 * MAXC ];

void update( int node, int lo, int hi, int& start, int& end, int& value ) {

  if ( lo > end || hi < start ) return;

  if ( start <= lo && hi <= end )
       times[node] += value;
  else {
    int mid = ( lo + hi ) / 2;
    update( LEFT( node ), lo, mid, start, end, value );
    update( RIGHT( node ), mid + 1, hi, start, end, value );
  }

  if ( !times[node] )
       amount[node] = ( lo == hi ) ? 0 :
                      amount[ LEFT( node ) ] + amount[ RIGHT( node ) ];
  else amount[node] = hi - lo + 1;
}

void lineSweep( vector< event >& ls ) {

  sort( ls.begin(), ls.end() );

  last = 0; size = ls.size();
  for ( int i = 0; i < size; i++ ) {
    update( 0, 0, MAXC, ls[i].lo, ls[i].hi, ls[i].flag );
    perimeter += abs( last - amount[0] );
    last = amount[0];
  }
}

int main() {

  scanf( "%d", &N );
  for ( int i = 0; i < N; i++ ) {

    int x1, x2, y1, y2;
    scanf( "%d %d %d %d", &x1, &y1, &x2, &y2 );

    if ( x1 > x2 ) swap( x1, x2 );
    if ( y1 > y2 ) swap( y1, y2 );

    events[0].push_back( ( event ) { y1, x1, x2 - 1, +1 } );
    events[0].push_back( ( event ) { y2, x1, x2 - 1, -1 } );
    events[1].push_back( ( event ) { x1, y1, y2 - 1, +1 } );
    events[1].push_back( ( event ) { x2, y1, y2 - 1, -1 } );
  }

  lineSweep( events[0] );
  lineSweep( events[1] );

  printf( "%lld\n", perimeter );

  return 0;
}
