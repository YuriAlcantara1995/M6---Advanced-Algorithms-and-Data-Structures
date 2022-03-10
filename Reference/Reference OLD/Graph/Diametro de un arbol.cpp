#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5+10;
bool mark[MAXN];
typedef pair<int,int>par;
vector<par>ady[MAXN];
int sol;

int diam(int nod)
{
 int max_path=0;
 mark[nod]=1;
 int t=ady[nod].size();
 for(int i=0;i<t;i++)
 {
  int nn=ady[nod][i].first;
  int nc=ady[nod][i].second;
  if(mark[nn])continue;
  int temp=nc+diam(nn);
  sol=max(sol,max_path+temp);
  max_path=max(max_path,temp);
 }

 return max_path;
}

int main()
{
 int N,M;
 scanf("%d%d",&N,&M);

 for(int i=1;i<=M;i++)
 {
  int a,b,c;
  scanf("%d%d%d%s",&a,&b,&c);
  ady[a].push_back(par(b,c));
  ady[b].push_back(par(a,c));
 }
 diam(1);
 cout << sol << '\n';

    return 0;
}
