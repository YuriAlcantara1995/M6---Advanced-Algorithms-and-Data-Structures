#include <bits/stdc++.h>
using namespace std;

int N, mays = -1 << 30, mayd = -1 << 30, mens = 1 << 30, mend = 1 << 30;

int main()
{
 
 scanf("%d", &N);

 int x, y;
 for( int i = 1; i <= N; i ++ )
 {
  scanf("%d%d", &x, &y);
  mens = min( mens, x + y );
  mays = max( mays, x + y );
  mend = min( mend, x - y );
  mayd = max( mayd, x - y );
 }

 printf("%d", max( mays - mens, mayd - mend ));

        return 0;
}
