#include<cstdio>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;

int square(int n)
{
 return n*n;
}

struct T
{
 int x,y,id;
 T(int a=0,int b=0)
 {
  x=a;y=b;
 }
 bool operator <(const T &p)const
 {
  return x<p.x;
 }
}P[100005];

double dist(T a,T b)
{
 return sqrt(square(a.x-b.x)+square(a.y-b.y));
}

struct compy
{
 bool operator()(const T &s,const T &p)const
 {
  return s.y<p.y;
 }
};

multiset<T,compy>MS;
multiset<T,compy>::iterator I,F;


int main()
{
 freopen("Closest_P_P.in","r",stdin);
 freopen("Closest_P_P.out","w",stdout);

 int N;
 scanf("%d",&N);

 for(int i=1;i<=N;i++)
  scanf("%d%d",&P[i].x,&P[i].y),P[i].id=i;

 sort(P+1,P+N+1);

 double min_dist=1<<30;
 int s1,s2;
 int p=1;
 for(int i=1;i<=N;i++)
 {
  while(p<i && P[i].x-P[p].x>=min_dist)
  {
   MS.erase(MS.find(P[p]));
   p++;
  }
  I=MS.lower_bound(T(P[i].x,P[i].y-min_dist));
  F=MS.upper_bound(T(P[i].x,P[i].y+min_dist));

  while(I!=F)
  {
   //min_dist=min(min_dist,dist(P[i],*I));
   T x=*I;
   if(min_dist>dist(P[i],x))
   {
    min_dist=dist(P[i],x);
    s1=P[i].id;s2=x.id;
   }
   I++;
  }
  MS.insert(P[i]);
 }

 printf("%d %d",s1,s2);

    return 0;
}
