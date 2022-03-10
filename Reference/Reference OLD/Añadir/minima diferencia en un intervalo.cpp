#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int>par;
typedef pair<par,int>trio;

bool com(const trio &s,const trio &p)
{
 return s.first.second<p.first.second;
}

const int MAXN=1e5+5;
const int MAXQ=3e5+5;

struct Stree
{
 multiset<int>MS;
 int md;
 Stree(int d=0)
 {
  MS.clear();
  md=d;
 }
}ST[4*MAXN];

int A[MAXN];
int minval;
int sol[MAXQ];
trio q[MAXQ];

void build(int nod,int I,int F)
{
 if(I==F)
  ST[nod].MS.insert(A[I]),
  ST[nod].md=1<<30;
 else
 {
  int piv=(I+F)/2;

  build(2*nod,I,piv);
  build(2*nod+1,piv+1,F);

  for(int i=I;i<=F;i++)
   ST[nod].MS.insert(A[i]);
  ST[nod].md=1<<30;
 }
}

int mindif(int nod,int val)
{
 multiset<int>::iterator it=ST[nod].MS.lower_bound(val);
 int d1=1<<30,d2=1<<30;
 if(it!=ST[nod].MS.end())d1=abs(*it-val);
 if(it!=ST[nod].MS.begin())
 {
  it--;
  d2=abs(*it-val);
 }
 return min(d1,d2);
}

void update(int nod,int I,int F,int a,int b,int val)
{
 if(I>b || F<a)return;
 if(mindif(nod,val)>=minval)
  return;

 if(I==F)
 {
  ST[nod].md=min(ST[nod].md,abs(*(ST[nod].MS.begin())-val));
  minval=min(minval,ST[nod].md);
  return;
 }

 int piv=(I+F)/2;

 update(2*nod+1,piv+1,F,a,b,val);
 update(2*nod,I,piv,a,b,val);

 ST[nod].md=min(ST[2*nod].md,ST[2*nod+1].md);

 minval=min(minval,ST[nod].md);
}

int query(int nod,int I,int F,int a,int b)
{
 if(I>b || F<a)return 1<<30;

 if(I>=a && F<=b)
  return ST[nod].md;

 int piv=(I+F)/2;

 int d1=query(2*nod,I,piv,a,b);
 int d2=query(2*nod+1,piv+1,F,a,b);

 return min(d1,d2);
}

int main()
{
 int N;
 cin >> N;

 for(int i=1;i<=N;i++)
  cin >> A[i];

 int Q;
 cin >> Q;
 for(int i=1;i<=Q;i++)
 {
  int a,b;
  cin >> a >> b;if(a>b)swap(a,b);
  q[i]=trio(par(a,b),i);
 }

 sort(q+1,q+Q+1,com);

 build(1,1,N);

 int ultimo_actualizado=0;
 for(int i=1;i<=Q;i++)
 {
  for(int j=ultimo_actualizado+1;j<=q[i].first.second;j++)
   minval=1<<30,update(1,1,N,1,j-1,A[j]);
  ultimo_actualizado=q[i].first.second;
  sol[q[i].second]=query(1,1,N,q[i].first.first,q[i].first.second);
 }

 for(int i=1;i<=Q;i++)
  cout << sol[i] << '\n';

    return 0;
}
