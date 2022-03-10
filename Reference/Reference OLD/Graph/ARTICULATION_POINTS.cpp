#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

int TD[1005],LOW[1005];
bool mark[1005];
int dc_time;
vector<int>ady[1005];

void A_Points(int nod)
{
 LOW[nod]=TD[nod]=++dc_time;

 int t=ady[nod].size();
 for(int i=0;i<t;i++)
 {
  int nn=ady[nod][i];
  if(!LOW[nn])
  {
   A_Points(nn);
   LOW[nod]=min(LOW[nod],LOW[nn]);
   if(nod==1)
   {
    if(TD[nn]>2)
     mark[1]=1;
    continue;
   }
   if(TD[nod]<=LOW[nn])
    mark[nod]=1;
  }
  else
   LOW[nod]=min(LOW[nod],TD[nn]);
 }
}

int main()
{

 int n,m;
 scanf("%d%d",&n,&m);

 int a,b;
 for(int i=1;i<=m;i++)
 {
  scanf("%d%d",&a,&b);
  ady[a].push_back(b);
  ady[b].push_back(a);
 }

 A_Points(1);

 for(int i=1;i<=n;i++)
  if(mark[i])
   printf("%d\n",i);

 printf("TD ->");
 for(int i=1;i<=n;i++)
  printf(" %d",TD[i]);

 printf("\nLOW->");
 for(int i=1;i<=n;i++)
  printf(" %d",LOW[i]);

    return 0;
}
