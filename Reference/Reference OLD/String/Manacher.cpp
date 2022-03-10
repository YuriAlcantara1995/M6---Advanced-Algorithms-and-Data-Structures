/*	Description: 	rad[i] = If i is odd, it's the largest even palindrome centered at position i.
                    Otherwise, it's the size of the largest odd palindrome centered at
                    position i.
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000006;
char s[maxn];
int rad[2 * maxn], n;

//WARNING: n = 2 * strlen(s)
void build_rad ()
{
    int i, j, k;
	for ( i = 0, j = 0; i < 2 * n - 1; i += k ) {
    while ( i - j >= 0 && i + j + 1 < 2 * n &&
            s[ ( i - j ) / 2 ] == s[ ( i + j + 1 ) / 2 ] )
              j++;
        rad[i] = j;
    for ( k = 1; k <= rad[i] && rad[ i - k ] != rad[i] - k; k++ )
      rad[ i + k ] = min( rad[ i - k ], rad[i] - k );
        j = max( j - k, 0 );
  }
}

bool is_palindrome (int b, int e)
{
	return b >= 0 && e < n &&  rad[b + e] >= e - b + 1;
}