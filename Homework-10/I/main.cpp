#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 5e5+5;

char s[MAXN];
int SA[MAXN],wa[MAXN], wb[MAXN], we[MAXN], wv[MAXN],S[MAXN],A[MAXN];

ll ts(int i, int f)
{
    if(i>f)return 0;

    ll si = 1ll*i*(i-1ll)/2ll;
    ll sf = 1ll*f*(f+1ll)/2ll;

    return sf-si;
}

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

int R[MAXN], LCP [MAXN];
void FindLCP(char *cad, int *SA, int N){
	int i, j, k;
	for (i = 1; i <= N; i++)
		R[ SA[i] ] = i;
	for (k = i = 0; i < N; LCP [R[i++]] = k)
		for (k ? k-- : 0,j = SA[R[i]-1]; cad[i + k] == cad[j + k];
				k++);
}

char cad[MAXN];
int n;

int main() {

	scanf("%s", cad);
	n = strlen(cad);

	Sufix_Array(cad, SA, n);
	FindLCP(cad, SA, n);

    ll sol=0;
    for(int i=1;i<=n;i++)
        sol+=ts(LCP[i]+1,n-SA[i]);

    cout << sol << '\n';
  return 0;
}