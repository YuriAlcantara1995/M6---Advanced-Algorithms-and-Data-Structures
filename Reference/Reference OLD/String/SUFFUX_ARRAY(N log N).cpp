#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

#define ll long long
#define MAX 500005

char s[MAX];
int SA[MAX],wa[MAX], wb[MAX], we[MAX], wv[MAX],S[MAX],A[MAX];

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

char cad[MAX];
int n;

int main() {

	scanf("%s", cad);
	n = strlen(cad);

	Sufix_Array(cad, SA, n);
	FindLCP(cad, SA, n);
    
	for(int i=1;i<=n;i++)
     printf("%d %s\n",SA[i],cad+SA[i]);	
    
  return 0;
}
