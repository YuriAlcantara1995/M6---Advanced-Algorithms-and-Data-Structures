#include<cstdio>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;

int n,m;
int a,b,c;
vector<int>ID[1001];
int start;
int G[1001];
stack<int>pila;

struct edge
{
 int nod,nn;
 bool mark;
 edge(int a=0,int b=0,bool c=0)
 {
  nod=a;
  nn=b;
  mark=c;
 }

 int next(int x)
 {
  if(x==nod)
   return nn;

  return nod;
 }

}A[1001];

void euler(int nod)
{
 int t=ID[nod].size();
 for(int i=0;i<t;i++)
 {
  int id=ID[nod][i];
  if(A[id].mark==0)
  {
   A[id].mark=1;
   euler(A[id].next(nod));
  }
 }
 pila.push(nod);
}

int main()
{
 freopen("Euler_P_C.in","r",stdin);
 freopen("Euler_P_C.out","w",stdout);

 scanf("%d%d",&n,&m);

 for(int i=1;i<=m;i++)
 {
  scanf("%d%d",&a,&b);
  ID[a].push_back(i);
  ID[b].push_back(i);
  G[a]++;
  G[b]++;
  A[i]=edge(a,b,0);
 }

 int I=0;
 for(int i=1;i<=n;i++)
 {
  if(G[i]%2==1)
   I++;
  if(I>2)
  {
   printf("NO HAY CAMINO EULERIANO\n");
   return 0;
  }
 }

 scanf("%d",&start);

 euler(start);

 if(I)
  printf("EXISTE UN CAMINO EULERIANO\n");
 else
  printf("EXISTE UN CIRCUITO EULERIANO\n");

 for(;!pila.empty();)
 {
  printf("%d\n",pila.top());
  pila.pop();
 }

 return 0;
}
