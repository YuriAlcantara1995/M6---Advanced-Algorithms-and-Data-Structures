#include<bits/stdc++.h>
using namespace std;

const int MAXN=2e3+10;
char P[MAXN][MAXN];
char T[MAXN][MAXN];

typedef unsigned long long ull;
ull hp[2][MAXN][MAXN];
ull ht[2][MAXN][MAXN];
ull bas[2] = {1e9 + 7 , 1e9 + 11};
ull po[2][MAXN];
int np,mp,nt,mt;
int F[MAXN];

ull hash_P(int k,int u){
	return hp[u][k][np] - hp[u][k][0]*po[u][np];
}

ull hash_T(int k,int i,int f,int u)
{
 return ht[u][k][f-1] - ht[u][k][i-1]*po[u][f-i];
}


int main()
{

 scanf("%d%d%d%d",&np,&mp,&nt,&mt);

 for(int i=1;i<=np;i++)
  scanf("%s",P[i]+1);
 for(int i=1;i<=nt;i++)
  scanf("%s",T[i]+1);

 po[0][0] = po[1][0] = 1;
 for(int j = 0 ; j < 2 ;j++)
  for(int i = 1 ; i <=nt ;i++)
	po[j][i] = po[j][i-1]*bas[j];

 for(int i=1;i<=mp;i++)
  hp[1][i][0] = hp[0][i][0] = 1;

 for(int j = 0 ; j < 2 ;j++)
  for(int k=1;k<=mp;k++)
   for(int i =1 ; i <= np ;i++)
 	hp[j][k][i] = (hp[j][k][i-1]*bas[j]) + P[i][k];
 for(int i=0;i<mt;i++)
  ht[1][i][0] = ht[0][i][0] = T[i][0];

 for(int j = 0 ; j < 2 ;j++)
  for(int k=1;k<=mt;k++)
   for(int i =1 ; i <= nt ;i++)
 	ht[j][k][i] = (ht[j][k][i-1]*bas[j]) + T[i][k];

   F[1] = 0;
   int k=0;
   for(int i=2;i<=mp;i++)
   {
      while(k>0 && (hash_P(k+1,0)!=hash_P(i,0) || hash_P(k+1,1)!=hash_P(i,1)))
         k=F[k];
      if(hash_P(k+1,0)==hash_P(i,0) &&hash_P(k+1,1)==hash_P(i,1)) k++;
     F[i]=k;
   }

   int cont=0;
   for(int f=1;f<=nt-np+1;f++)
   {
    int k=0;
    for(int i=1;i <= mt;i++){
      while((k>0) && (hash_P(k+1,0)!=hash_T(i,f,f+np,0) || hash_P(k+1,1)!=hash_T(i,f,f+np,1)))
         k = F[k];
      if(hash_P(k+1,0)==hash_T(i,f,f+np,0) && hash_P(k+1,1)==hash_T(i,f,f+np,1)) k++;
      if(k==mp)
       cont++,k = F[k];//found
   }
 }

  cout << cont << '\n';

    return 0;
}
