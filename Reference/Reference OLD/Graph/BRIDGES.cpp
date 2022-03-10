#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;

typedef pair<int,int>par;
vector<int>ID[1005];//id de las aristas en que esta presente cada nodo
int TD[1005],LOW[1005];
int dc_time;
bool mark[10005];
stack<par>S;
int a,b;
struct T
{
 int nod,nn;
 T(int x=0,int y=0)
 {
  nod=x;nn=y;
 }
 int nextn(int x)
 {
  if(x==nod)
   return nn;
  else
   return nod;
 }
}edge[10005];

void Bridges(int nod)
{
 TD[nod]=LOW[nod]=++dc_time;

 int t=ID[nod].size();
 for(int i=0;i<t;i++)
 {
  int id=ID[nod][i];
  int nn=edge[id].nextn(nod);
  if(!LOW[nn])
  {
   mark[id]=1;
   Bridges(nn);
   if(TD[nod]<LOW[nn])
    S.push(par(nod,nn));
   LOW[nod]=min(LOW[nod],LOW[nn]);
  }
  else
   if(!mark[id])
    LOW[nod]=min(LOW[nod],TD[nn]);
 }
}

int main()
{
 freopen("Bridges.in","r",stdin);
 freopen("Bridges.out","w",stdout);

 int n,m;
 scanf("%d%d",&n,&m);

 for(int i=1;i<=m;i++)
 {
  scanf("%d%d",&a,&b);
  ID[a].push_back(i);
  ID[b].push_back(i);
  edge[i]=T(a,b);
 }

 Bridges(1);

 while(!S.empty())
 {
  par A=S.top();
  S.pop();
  printf("%d %d\n",A.first,A.second);
 }
    return 0;
}
