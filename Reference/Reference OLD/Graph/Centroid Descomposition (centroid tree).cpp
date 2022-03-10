#include<bits/stdc++.h>
using namespace std;

const int MAXN=250005;
int P[MAXN];
int HD[MAXN],HI[MAXN];

int subsize[MAXN],Ant[MAXN];
vector<int>ady[MAXN];
bool mk[MAXN];
int ref_pos;
long long sum[MAXN],contribution[MAXN],cont[MAXN];


 void DFS1(int np, int prev){
    subsize[np] = 1;
    int l = ady[np].size();
    for(int i = 0; i < l; i++){
        int nh = ady[np][i];
        if(nh != prev && !mk[nh]){
            DFS1(nh, np);
            subsize[np] += subsize[nh];
        }
    }
 }

 int DFS2(int np, int prev){

     int l = ady[np].size();
     for(int i = 0; i < l; i++){
        int nh = ady[np][i];
        if(nh != prev && !mk[nh] && subsize[nh] > subsize[ref_pos]/2)
            return DFS2(nh, np);
     }
     return np;
 }

 void Descomposition(int root, int prev){

    ref_pos = root;
    DFS1(root, root);
    int centroid = DFS2(root, root);
    Ant[centroid] = prev;
    mk[centroid] = true;
    int l = ady[centroid].size();
    for(int i = 0; i < l; i++){
        int nh = ady[centroid][i];
        if(!mk[nh])
            Descomposition(nh, centroid);
    }
 }

 struct LCA {
    int T[100005][20], L[100005];

    void DFS0(int np, int prev){
        T[np][0] = prev;
        L[np] = L[prev]+1;
        int l = ady[np].size();
        for(int i = 0; i < l; i++){
            int nh = ady[np][i];
            if(nh != prev)
                DFS0(nh, np);
        }
     }

    void Build(int n){
        DFS0(1, 0);
        int lg = log2(n);
        for(int j = 1; j <= lg; j++)
            for(int i = 1; i <= n; i++)
                if(T[i][j-1] != -1)
                    T[i][j] = T[T[i][j-1]][j-1];
    }

     int Query(int x, int y){
        int res = 0;
        if(L[x] < L[y])swap(x, y);

        int lg = (int)log2(L[x]);
        for(int i = lg; i >= 0; i--)
            if(L[x] - (1 << i) >= L[y] && T[x][i])
                x = T[x][i], res += (1 << i);

        if(x == y)return res;

        for(int i = lg; i >= 0; i--)
            if(T[x][i] != T[y][i] && T[x][i])
                x = T[x][i], y = T[y][i], res += 2*(1 << i);

        return res+2;
        return T[x][0];
     }
 }Lc;

 void update(int nod)
 {
  int pos = nod;
  cont[pos]++;
  while(Ant[pos]!=-1)
  {
   sum[Ant[pos]]+=Lc.Query(nod,Ant[pos]);
   contribution[pos]+=Lc.Query(nod,Ant[pos]);
   cont[Ant[pos]]++;
   pos=Ant[pos];
  }
 }

 long long query(int nod)
 {
  long long ret=0;
  int pos=nod;
  ret=sum[pos];

  while(Ant[pos]!=-1)
  {
   ret+=sum[Ant[pos]]-contribution[pos]+(cont[Ant[pos]]-cont[pos])*Lc.Query(nod,Ant[pos]);
   pos=Ant[pos];
  }

  return ret;
 }

int main()
{
 int N;
 cin >> N;

 for(int i=1;i<=N;i++)
 cin >> P[i];

 for(int i=1;i<=N;i++)
  HI[i]=HD[i]=-1;
 for(int i=2;i<=N;i++)
 {
  int pos=P[1];
  while(1)
  {
   if(P[i]>pos)
   {
    if(HD[pos]==-1)
    {
     HD[pos]=P[i];
     break;
    }
    else
     pos=HD[pos];
   }
   else
   {
    if(HI[pos]==-1)
    {
     HI[pos]=P[i];
     break;
    }
    else
     pos=HI[pos];
   }
  }
 }

  for(int i=1;i<=N;i++)
  {
   if(HI[i]!=-1)ady[i].push_back(HI[i]),ady[HI[i]].push_back(i);
   if(HD[i]!=-1)ady[i].push_back(HD[i]),ady[HD[i]].push_back(i);
   Ant[i]=-1;
  }

 Lc.Build(N);
 Descomposition(P[1], -1);

 long long sol=0;
 for(int i=1;i<=N;i++)
 {
  sol+=query(P[i]);
  cout << sol << '\n';
  update(P[i]);
 }


    return 0;
}
