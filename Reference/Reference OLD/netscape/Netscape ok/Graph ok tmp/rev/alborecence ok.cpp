//bestard
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double db;
#define eps 1e-9
ll mod = 1e9+7;
typedef pair<ll, ll> par;
typedef pair<int, par> tri;
#define fauto( i, x ) for(__typeof(x.end())i=x.begin();i!=x.end();++i)
#define mset( a, b ) memset( a, b, sizeof(a) )
#define MAXN 100005
/*int n, a, b, k;
char cad[100005];
int A[1000005];
vector<int> V;*/
/*
void solve( int k, int l, int r, int lo, int ro ){
    if( L > R ) return;
    int m = ( l+r )/2, s = 0;
    Dp[k][m] = 0;
    for( int i =  lo; i <= min(lr, m); i ++ ){
        if( Dp[k-1][m] )

    }
}*/

template<typename T>
struct minimum_aborescense
{
	struct edge
	{
		int src, dst;
		T weight;
	};

	vector<edge> edges;

	void add_edge(int u, int v, T w)
	{
		edges.push_back({ u, v, w });
	}

	T solve(int r)
	{
		int n = 0;
		for (auto e : edges)
			n = max(n, max(e.src, e.dst) + 1);

		int N = n;

		if( N == 0 ) return 0;

		for (T res = 0;;)
		{
			vector<edge> in(N, { -1, -1, numeric_limits<T>::max() });
			vector<int> C(N, -1);
			for (auto e : edges) // cheapest comming edges
				if (in[e.dst].weight > e.weight)
					in[e.dst] = e;

			in[r] = {r, r, 0};
			for (int u = 0; u < N; ++u)
			{ // no comming edge ==> no aborescense
				if (in[u].src < 0)
					return numeric_limits<T>::max();
				res += in[u].weight;
			}

			vector<int> mark(N, -1); // contract cycles
			int index = 0;
			for (int i = 0; i < N; ++i)
			{
				if (mark[i] != -1)
					continue;
				int u = i;
				while (mark[u] == -1)
				{
					mark[u] = i;
					u = in[u].src;
				}
				if (mark[u] != i || u == r)
					continue;
				for (int v = in[u].src; u != v; v = in[v].src)
					C[v] = index;
				C[u] = index++;
			}

			if (index == 0)
				return res; // found arborescence
			for (int i = 0; i < N; ++i) // contract
				if (C[i] == -1)
					C[i] = index++;

			vector<edge> next;
			for (auto &e : edges)
				if (C[e.src] != C[e.dst] && C[e.dst] != C[r])
					next.push_back({ C[e.src], C[e.dst],
						e.weight - in[e.dst].weight });
			edges.swap(next);
			N = index;
			r = C[r];
		}
	}
};



int n;
int A[100005];
bool mark[100005];
int ca;

int main()
{
    #ifdef acm
    freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    #endif // acm

    ios::sync_with_stdio(0);
    cin.tie(0);

     cin >> n;

    int ma = 0;
    for( int i = 1; i <= n; i ++ ){
        cin >> A[i];
        ma = max( A[i], ma );
    }
    minimum_aborescense<ll> T;
    int m;
    cin >> m;

    int a, b, c;
    for( int i = 1; i <= m; i ++ ){
        cin >> a >> b >> c;

        if( !mark[a] ) mark[a] = 1, ca ++;
        if( !mark[b] ) mark[b] = 1, ca ++;

        a--, b --;
        T.add_edge( a, b, c );
    }

    if( ca != n && n > 1 ){
        cout << -1;
        return 0;
    }

    minimum_aborescense<ll> T1 = T;

    ll sol = 1ll << 60;
    for( int i = 1; i <= n ; i ++ )
        if( ma == A[i] ){
            T = T1;
            sol = min( T.solve(i-1), sol );
        }


    if( sol == 1ll << 60 ) sol = -1;
    cout << sol;


    return 0;
}
