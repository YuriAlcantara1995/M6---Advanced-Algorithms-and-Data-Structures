    #include<cstdio>
    #include<algorithm>
    #include<cmath>
    using namespace std;

    int A[10005],M[10005][20];

    int main()
    {
     int N;
     scanf("%d",&N);

     for(int i=0;i<N;i++)
      scanf("%d",&A[i]),M[i][0]=i;

     for(int i=1;(1<<i)-1<N;i++)
      for(int j=0;j+(1<<i)-1<N;j++)
       if(A[M[j][i-1]]<A[M[j+(1<<(i-1))][i-1]])
        M[j][i]=M[j][i-1];
       else
        M[j][i]=M[j+(1<<(i-1))][i-1];

     int Q;
     scanf("%d",&Q);

     int a,b;
     for(int i=1;i<=Q;i++)
     {
      scanf("%d%d",&a,&b);a--;b--;
      if(a>b)swap(a,b);
      int lg=(int)log2(b-a+1);
      int sol=min(A[M[a][lg]],A[M[b-(1<<lg)+1][lg]]);
      printf("%d\n",sol);
     }

     return 0;
    }
