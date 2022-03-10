#include<bits/stdc++.h>
using namespace std;

const int MAXN=4e5+5;


int n,k;
vector<int>g[MAXN],gi[MAXN];
vector<bool> band;
vector<int> comp;
int TS[MAXN];

int NOT(int x)
{
 if(x>n)return x-n;
 return n+x;
}

void dfs1 (int nod)
{
 band[nod] = true;
 int t=g[nod].size();
 for (int i=0;i<t;++i)
 {
  int nn = g[nod][i];
  if(!band[nn])
  dfs1(nn);
 }
 TS[k--]=nod;
}

void dfs2 (int nod, int c)
{
 comp[nod] = c;
 int t=gi[nod].size();
 for (int i=0; i<t; ++i)
 {
  int nn = gi[nod][i];
  if (comp[nn] == -1)
   dfs2 (nn, c);
 }
}

void add_edge(int a,int b)
{
  g[NOT(a)].push_back(b);
  g[NOT(b)].push_back(a);
  gi[b].push_back(NOT(a));
  gi[a].push_back(NOT(b));
}

int main()
{
 freopen("a.in","r",stdin);
 freopen("a.out","w",stdout);

 int m;
 scanf("%d%d",&n,&m);

 int a,b;char ca,cb;
 for(int i=1;i<=m;i++)
 {
  scanf("%d %c %d %c",&a,&ca,&b,&cb);
  if(ca=='N')a=NOT(a);
  if(cb=='N')b=NOT(b);

  add_edge(a,b);
 }

 k=2*n;
 band.assign (2*n+1, false);
 for (int i=1; i<=2*n; ++i)
  if (!band[i])
   dfs1 (i);

 comp.assign (2*n+1, -1);
 for (int i=1, j=1; i<=2*n; ++i)
 {
  int nod = TS[i];
  if (comp[nod] == -1)
   dfs2 (nod, j++);
 }

 for (int i=1; i<=n; ++i)
  if(comp[i]==comp[NOT(i)])
  {
    printf("IMPOSSIBLE");
    return 0;
  }

 for (int i=1; i<=n; ++i)
 {
  if(comp[i]>comp[NOT(i)])
   printf("Y");
  else
   printf("N");
 }

}
