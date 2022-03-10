#include<cstdio>
#include<algorithm>
using namespace std;

char S[1000005];
bool B;

int main()
{
 freopen("period.in","r",stdin);
 freopen("period.out","w",stdout);

 int N;
 scanf("%d",&N);
 scanf("%s",S+1);

 int l=1;
 for(int i=2;i<=N;i++)
 {
  if(S[i]==S[i-l])
  {
   if(i%l==0)
    printf("%d %d\n",i,i/l),B=1;
  }
  else
  {
   if(S[i]==S[1])
    l=i-1;
   else
    l=i;
  }
 }

 if(!B)
  printf("0");

    return 0;
}
