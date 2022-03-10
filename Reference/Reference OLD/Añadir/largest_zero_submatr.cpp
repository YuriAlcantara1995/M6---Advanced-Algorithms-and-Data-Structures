#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 5005
int N,M;
int D[MAXN];
int A[MAXN][MAXN];

int max_submatr()
{
  int h[MAXN], s[MAXN], ptr = 0;
  int ret = 0;

  for(int i=0;i<M;i++)
  {
   int l=i;
   while(ptr>0 && D[i]<h[ptr-1])
   {
    ret=max(ret,(i-s[ptr-1])*(h[ptr-1]));
    l=s[ptr-1];
    ptr--;
   }
   h[ptr]=D[i];
   s[ptr++]=l;
  }

  while(ptr>0)
  {
   ret=max(ret,(M-s[ptr-1])*(h[ptr-1]));
   ptr--;
  }

  return ret;
}

int main()
{
 scanf("%d%d",&N,&M);

 for(int i=0;i<N;i++)
  for(int j=0;j<M;j++)
   scanf("%d",&A[i][j]);

 int sol=0;
 for(int i=0;i<N;i++)
 {
  for(int j=0;j<M;j++)
   if(!A[i][j])
    D[j]++;
   else
    D[j]=0;
  sol=max(sol,max_submatr());
 }

 printf("%d\n",sol);

    return 0;
}
