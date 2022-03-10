#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;

struct T
{
 int x,y1,y2,IoF;
 T(int a=0,int b=0,int c=0,int d=0)
 {
  x=a;y1=b;y2=c;IoF=d;
 }
}L[200005];

int B[200005],r1;
int B1[200005],r2;

bool com(const T &s,const T &p)
{
 return s.x<p.x;
}

int MAXY;
int Stree[3000005];
long long cant[3000005];
int r;

void update(int node,int ini,int fin,int y1,int y2,int IoF)
{
 if(ini>y2 || fin<y1)
  return;
 if(ini>=y1 && fin<=y2)
  Stree[node]+=IoF;
 else
 {
  int piv=(ini+fin)/2;
  update(2*node,ini,piv,y1,y2,IoF);
  update(2*node+1,piv+1,fin,y1,y2,IoF);
 }
 if(Stree[node]==0)
 {
  if(ini==fin)
   cant[node]=0;
  else
   cant[node]=(long long)cant[2*node]+cant[2*node+1];
 }
 else
  cant[node]=(long long)B[fin]-B[ini-1];
}

int main()
{

 int N;
 scanf("%d",&N);

 for(int i=1;i<=N;i++)
 {
  int x1,y1,x2,y2;
  scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
  if(x1>x2)
   swap(x1,x2);
  if(y1>y2)
   swap(y1,y2);
  L[++r]=T(x1,y1,y2,1);
  L[++r]=T(x2,y1,y2,-1);
  B1[++r2]=y1;B1[++r2]=y2;

 }
 B1[0]=-1;
 sort(B1+1,B1+r2+1);
 for(int i=1;i<=r2;i++)
  if(B1[i]!=B1[i-1])
   B[++r1]=B1[i];

 sort(L+1,L+r+1,com);

 int last=L[1].x;
 long long area=0;
 for(int i=1;i<=r;i++)
 {
  long long temp=(long long)L[i].x-last;
  temp=(long long)temp*cant[1];
  area=(long long)area+temp;
  last=L[i].x;
  int I=lower_bound(B+1,B+r1+1,L[i].y1)-B;
  int F=lower_bound(B+1,B+r1+1,L[i].y2)-B;
  update(1,1,r1,I+1,F,L[i].IoF);
 }

 cout << area;

 return 0;
}
