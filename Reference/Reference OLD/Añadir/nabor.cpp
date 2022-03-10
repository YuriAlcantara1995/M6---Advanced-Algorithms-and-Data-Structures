#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;

int N,C;
typedef pair<int,int>par;
typedef pair<int,par>trio;
int S[100005],R[100005];
trio P[100005];
bool MARK[100005];

multiset<par>MS;
multiset<par>::iterator F;


void join_set(int seta,int setb)
{
 if(seta<setb)
 {
  S[setb]=seta;
  R[seta]+=R[setb];
 }
 else
 {
  S[seta]=setb;
  R[setb]+=R[seta];
 }
}

int find_set(int nod)
{
 if(S[nod]!=nod)
  S[nod]=find_set(S[nod]);

 return S[nod];
}

int main()
{
 freopen("nabor.in","r",stdin);
 freopen("nabor.out","w",stdout);

 scanf("%d%d",&N,&C);

 for(int i=1;i<=N;i++)
 {
  int a,b;
  scanf("%d%d",&a,&b);
  P[i]=trio(a+b,par(a-b,i));
  S[i]=i,R[i]=1;
 }

 sort(P+1,P+N+1);
 int ini=1;
 for(int i=1;i<=N;i++)
 {
  int X=P[i].first,Y=P[i].second.first,ID=P[i].second.second;

  while(X-P[ini].first>C && ini<i)
   MS.erase(MS.find(par(P[ini].second.first,P[ini].second.second))),ini++;

  F=MS.upper_bound(par(Y,ID));

   if(F!=MS.end())
   {
    par x=*F;
    int seta=find_set(ID);
    int setb=find_set(x.second);
    if(seta!=setb && abs(x.first-Y)<=C)
     join_set(seta,setb);
   }
   if(F!=MS.begin())
    F--;

   if(F!=MS.end())
   {
    par x=*F;
    int seta=find_set(ID);
    int setb=find_set(x.second);
    if(seta!=setb && abs(Y-x.first)<=C)
     join_set(seta,setb);
   }

  MS.insert(par(Y,ID));
 }

 int SOLR=0,SOLS=0;
 for(int i=1;i<=N;i++)
 {
  SOLR=max(SOLR,R[i]);
  int s=find_set(i);
  if(!MARK[s])
   SOLS++,MARK[s]=1;
 }

 printf("%d %d",SOLS,SOLR);



    return 0;
}
