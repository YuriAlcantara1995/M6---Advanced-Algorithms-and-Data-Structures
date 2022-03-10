#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

#define MAXN 500005

int sum[3000005], L[3000005], R[3000005];
int root[MAXN];
int A[MAXN],aux[MAXN];
int sz = 1;

int newnode(int s = 0)
{
 sum[sz] = s;
 return sz++;
}

int build(int I, int F)
{
	if(I == F)
	 return newnode();

	int piv=(I+F)/2;

	int nod = newnode();
	L[nod] = build(I, piv);
	R[nod] = build(piv+1, F);

	return nod;
}

int update(int nod, int I, int F, int pos)
{
	if(I==F)
	 return newnode(sum[nod]+1);

    int piv=(I+F)/2;

	int nnod = newnode();

	if(pos<=piv)
	{
		L[nnod] = update(L[nod],I,piv,pos);
		R[nnod] = R[nod];
	}
	else
	{
		R[nnod] = update(R[nod],piv+1,F, pos);
		L[nnod] = L[nod];
	}

	sum[nnod] = sum[L[nnod]] + sum[R[nnod]];

	return nnod;
}

int query(int nod1,int nod2,int I,int F,int k)
{
	if(I==F)
	 return I;

	int suma = sum[L[nod2]] - sum[L[nod1]];
	int piv=(I+F)/2;

	if(suma >= k)
	 return query(L[nod1], L[nod2],I,piv,k);
	else
	 return query(R[nod1], R[nod2],piv+1,F, k-suma);
}



int main()
{
	int N, M;
	cin >> N >> M;

	root[0]=build(1, N);

	for(int i=0;i<N;i++)
	{
     cin >> A[i];
     aux[i]=A[i];
	}

	sort(aux, aux+N);
	for(int i=0;i<N;i++)
	 A[i]=lower_bound(aux,aux+N,A[i])-aux;

	for(int i=0;i<N;i++)
   	 root[i+1] = update(root[i],1,N, A[i]+1);

	for(int i=1;i<=M;i++)
	{
	 int a,b,k;
     cin >> a >> b >> k;
	cout << aux[query(root[a-1], root[b], 1, N, k)-1] << '\n';
	}

	return 0;
}

