#include<bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
int N,M,Q;
map<string,int>MAP;
int S[MAXN],A[MAXN];

void inicializar()
{
 for(int i=1;i<=N;i++)
  S[i]=i,A[i]=0;;
}

void join_set(int seta,int setb)
{
 S[setb]=seta;
}

int find_set(int nod)
{
 if(S[nod]==nod)
   return S[nod];
 return S[nod]=find_set(S[nod]);
}

bool antonimos(int a,int b)
{
 int seta=find_set(a);
 int setb=find_set(b);

 if(A[seta]==setb)
  return 1;
 return 0;
}

bool sinonimos(int a,int b)
{
 int seta=find_set(a);
 int setb=find_set(b);

 if(seta==setb)
    return 1;

 return 0;
}

void set_sinonimos(int a,int b)
{
 int seta=find_set(a);
 int setb=find_set(b);

 if(!A[seta] && !A[setb])
  join_set(seta,setb);
 else
  if(A[seta] && A[setb])
   join_set(seta,setb),join_set(A[seta],A[setb]);
  else
    if(A[seta])
     join_set(seta,setb);
    else
     join_set(setb,seta);
}

void set_antonimos(int a,int b)
{
 int seta=find_set(a);
 int setb=find_set(b);

 if(A[seta] && A[setb])
  join_set(seta,A[setb]),join_set(A[seta],setb);
 else
  if(!A[seta] && !A[setb])
   A[seta]=setb,A[setb]=seta;
  else
    if(A[seta])
     join_set(A[seta],setb);
    else
      join_set(A[setb],seta);
}

int main()
{
 cin.tie(0);
 ios_base::sync_with_stdio(0);

 cin >> N >> M >> Q;

 inicializar();

 string s;int c=0;
 for(int i=1;i<=N;i++)
  cin >> s,MAP[s]=++c;

 string a,b;
 for(int i=1;i<=M;i++)
 {
  cin >> c >> a >> b;
  int ma=MAP[a],mb=MAP[b];
  if(c==1)
  {
   if(antonimos(ma,mb))
   {
    cout << "NO\n";
    continue;
   }
   else
    cout << "YES\n";
   set_sinonimos(ma,mb);
  }
  else
  {
   if(sinonimos(ma,mb))
   {
    cout << "NO\n";
    continue;
   }
   else
    cout << "YES\n";
   set_antonimos(ma,mb);
  }
 }

 for(int i=1;i<=Q;i++)
 {
  cin  >> a >> b;
  int ma=MAP[a],mb=MAP[b];
  if(sinonimos(ma,mb))
   cout << "1\n";
  else
    if(antonimos(ma,mb))
     cout << "2\n";
    else
      cout << "3\n";
 }

    return 0;
}
