SUFFIX ARRAY (N log^2 N)

struct T
{
 int nr[2],p;
}L[200005];

bool com(const T &s,const T &p)
{
 if(s.nr[0]!=p.nr[0])
  return s.nr[0]<p.nr[0];

 return s.nr[1]<p.nr[1];
}

int N,K,stp,delta;
char st[200005];
int P[20][200005];
int pos[200005];

int LCP(int x,int y)
{
 int ret=0;
 for(int k=stp-1;k>=0 && x<N && y<N;k--)
  if (P[k][x]==P[k][y])
  {
   x+=(1<<k);
   y+=(1<<k);
   ret+=(1<<k);
  }
 return ret;
}

int main ()
{
    gets( st );
    N = strlen( st );

    /*copy( st, st + N , st + N );
    reverse( st + N, st + 2 * N );

    N *= 2;*/

 /* Suffix Array Computation */
 for(int i=0;i<N;i++)
  P[0][i]=st[i]-'A';

 /* build suffix array */
 for(stp=1,delta=1;(delta>>1) < N;stp++,delta<<=1)
 {
  for(int i=0;i<N;i++)
  {
   L[i].nr[0]=P[stp - 1][i];
   L[i].p = i;
   if(i+delta<N)
    L[i].nr[1]=P[stp-1][i+delta];
   else
    L[i].nr[1]=-1;
  }
  sort(L,L+N,com);

  for(int i=0;i<N;i++)
   if(i>0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] )
    P[stp][L[i].p]=P[stp][L[i - 1].p];
   else
    P[stp][L[i].p]=i;
 }

 /* pos gives me the position of suffix with order at P[stp - 1][i] */

  for(int i=0;i<N;i++)
   pos[P[stp - 1][i]]=i;

  for(int i=0;i<N;i++)
   printf("%d %s\n",pos[i],st+pos[i]);

 /*Computing the LCP ( Longest Comon Prefix ) between 2 suffixes, one starting at
 a, and the other starting at b ( a & b are provided by queries ) */

    /*int solution = 1;
    for (int i = 0 ; i < ( N / 2 ) - 1 ; i++ ) {
        // odd & even length
        if ( i ) // n - i < n
            solution =max( 2 * LCP( i + 1, N - i ) + 1, solution);

        solution = max( 2 * LCP( i + 1, N - i - 1), solution );
    }*/

 //printf("%d",solution);
 
// $ < # < @
// LCP 3 suffixes

    return 0;
}
