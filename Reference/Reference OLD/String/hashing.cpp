using namespace std;
const int MAXN = 2e4 + 10;
int N,K ;
int A[MAXN];

typedef unsigned long long ull;
ull h[2][MAXN];
ull bas[2] = {1e9 + 7 , 1e9 + 11};
ull po[2][MAXN];

//hash desde i a f sin incluir f, con el primo u
ull hash_to(int i , int f , int u)
{
	return h[u][f-1] - h[u][i-1]*po[u][f-i];
}

int main()
{
    scanf("%d %d",&N,&K);
	for(int i =1 ; i <= N ;i++)
		scanf("%d",&A[i]);

	po[0][0] = po[1][0] = 1;
	for(int j = 0 ; j < 2 ;j++)
		for(int i = 1 ; i <=N ;i++)
			po[j][i] = po[j][i-1]*bas[j];

	h[1][0] = h[0][0] = 1;
	for(int j = 0 ; j < 2 ;j++)
		for(int i =1 ; i <= N ;i++)
			h[j][i] = (h[j][i-1]*bas[j]) + A[i];
}
