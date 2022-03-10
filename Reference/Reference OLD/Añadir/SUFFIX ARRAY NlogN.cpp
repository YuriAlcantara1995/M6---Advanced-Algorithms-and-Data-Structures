#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MAX 1000005

char s[MAX];
int SA[MAX],wa[MAX], wb[MAX], we[MAX], wv[MAX],S[MAX],A[MAX];
int LLCP[MAX],ID[MAX];

void Sufix_Array(char *cad,int *SA,int N){
	N++;
	int i, j, p, *x = wa, *y = wb, range = 256;
	memset(we, 0, range * sizeof(int));
	for (i = 0; i < N; i++)
		we[ x[i] = cad[i] ]++;
	for (i = 1; i < range; i++) we[i] += we[ i-1 ];
	for (i = N - 1; i >= 0; i--)
		SA[ --we[ x[i] ] ] = i;
	for (j = p = 1; p < N; j <<= 1, range = p){
		for (p = 0, i = N - j; i < N; y[p++] = i , i++) ;
		for (i = 0; i < N; i++)
			if (SA[i] >= j) y[p++] = SA[i] - j;
		for (i = 0; i < N; i++)
			wv[i] = x[ y[i] ];
		memset(we, 0, range * sizeof(int));
		for (i = 0; i< N; i++)
			we[ wv[i] ]++;
		for (i = 1; i < range; i++) we[i] += we[i-1];
		for (i = N-1; i >= 0; i--) SA[--we[wv[i]]] = y[i];
		swap(x, y); x[SA[0]] = 0;
		for (p = i = 1; i < N; i++)
			if(y[SA[i]] == y[SA[i-1]] && y[SA[i]+j] == y[SA[i-1]+j])
				x[SA[i]] = p - 1; else x[SA[i]] = p++;
	}
	N--;
}

int rank[MAX], LCP [MAX];
void FindLCP(char *cad, int *SA, int N){
	int i, j, k;
	for (i = 1; i <= N; i++)
		rank[ SA[i] ] = i;
	for (k = i = 0; i < N; LCP [rank[i++]] = k)
		for (k ? k-- : 0,j = SA[rank[i]-1]; cad[i + k] == cad[j + k];
				k++);
}

typedef pair<int,int>par;
stack<par>st;
char cad[MAX];
char aux[MAX];
int IZ[MAX],DE[MAX];
int sol[MAX];
int CadSol[MAX];
int n;
int M[MAX][20];

int lcp(int a,int b)
{
 int ret=1<<30;
 a++;

 if(a>b)swap(a,b);
 int lg=(int)log2(b-a+1);
 ret=min(LCP[M[a][lg]],LCP[M[b-(1<<lg)+1][lg]]);

 return ret;
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);


    int T;
    cin >> T;
    int laux=0;
    for(int i=1;i<=T;i++)
    {
     sol[i]=1<<30;
     n=strlen(cad);
     cin >> aux; strcat(aux,"#");
     
	 laux=strlen(aux);
     for(int j=n;j<n+laux;j++)
	   cad[j]=aux[j-n],	  
       ID[j]=i,LLCP[j]=n+laux-j-1; // Guardo la cadena a la que pertenece cada caracter
	                               // y calculo el limite del LCP para cada sufijo
    }
	n = strlen(cad);

	Sufix_Array(cad, SA, n);
	FindLCP(cad, SA, n);

	// RMQ para calcular LCP en intervalos
    for(int i=1;i<=n;i++)
     M[i][0]=i;

    for(int i=1;(1<<i)-1<=n;i++)
      for(int j=1;j+(1<<i)-1<=n;j++)
       if(LCP[M[j][i-1]]<LCP[M[j+(1<<(i-1))][i-1]])
        M[j][i]=M[j][i-1];
       else
        M[j][i]=M[j+(1<<(i-1))][i-1];


    for(int i=1;i<=n;i++)
    {
     LCP[i]=min(LCP[i],LLCP[SA[i]]);
    }
    
	//Para cada sufijo busco el primero a la izquierda que no pertenece
	//a la misma cadena
    st.push(par(ID[SA[1]],1));
    IZ[1]=-1;
    for(int i=2;i<=n;i++)
    {
     while(!st.empty() && st.top().first==ID[SA[i]])
      st.pop();
     if(!st.empty())
      IZ[i]=st.top().second;
     else
      IZ[i]=-1;
     st.push(par(ID[SA[i]],i));
    }

    //Para cada sufijo busco el primero a la derecha que no pertenece
	//a la misma cadena
    st.push(par(ID[SA[n]],n));
    DE[n]=-1;
    for(int i=n-1;i>=1;i--)
    {
     while(!st.empty() && st.top().first==ID[SA[i]])
      st.pop();
     if(!st.empty())
      DE[i]=st.top().second;
     else
      DE[i]=-1;
     st.push(par(ID[SA[i]],i));
    }
    //Calculo para cada cadena el menor substring que no aparece
	//en ninguna otra cadena
    for(int i=1;i<=n;i++)
    {
     if(cad[SA[i]]=='#')continue;
     if(DE[i]!=-1 && IZ[i]!=-1)
     {
       if(max(lcp(IZ[i],i),lcp(i,DE[i]))<LLCP[SA[i]] && sol[ID[SA[i]]]>max(lcp(IZ[i],i),lcp(i,DE[i]))+1)
        sol[ID[SA[i]]]=max(lcp(IZ[i],i),lcp(i,DE[i]))+1,CadSol[ID[SA[i]]]=SA[i];
     }
    else
      if(DE[i]!=-1){
       if(lcp(i,DE[i])<LLCP[SA[i]] && sol[ID[SA[i]]]>lcp(i,DE[i])+1)
       sol[ID[SA[i]]]=lcp(i,DE[i])+1,CadSol[ID[SA[i]]]=SA[i];
      }
      else
       if(lcp(IZ[i],i)<LLCP[SA[i]] && sol[ID[SA[i]]]>lcp(IZ[i],i)+1)
        sol[ID[SA[i]]]=lcp(IZ[i],i)+1,CadSol[ID[SA[i]]]=SA[i];
    }

    for(int i=1;i<=T;i++)
     if(sol[i]==1<<30)
      cout << "IMPOSSIBLE" << '\n';
     else
     {
      for(int j=CadSol[i];j<CadSol[i]+sol[i];j++)
      cout << cad[j];
      cout << '\n';
     }

  return 0;
}
