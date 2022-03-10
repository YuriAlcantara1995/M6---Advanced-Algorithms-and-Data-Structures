#include <bits/stdc++.h>
using namespace std;
/**
dp[i][k] = min( dp[j][k-1] + C[j+1][i] ) conquer and divide
		   j < i	
	
dp[k][i] = min( dp[k-1][j-1] + C[j][i] )
		   k <= j <= i	
*/
typedef long long ll;
const int maxn = 1003;
int N, K;
ll L[maxn], X[maxn], W[maxn], dp[maxn][maxn], O[maxn][maxn];
inline ll costo( int l, int r ){
    ll ret = L[r] -  (L[l] + (X[r]-X[l])*W[l-1]);
    return ret;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    #ifdef acm
    freopen("a.in","r",stdin);
    #endif // acm

    while ( cin >> N >> K ){
        for( int i = 1; i <= N; i++ )
            cin >> X[i] >> W[i], W[i] += W[i-1];

        L[1] = 0;
        for( int i = 2; i <= N; i++ ){
            L[i] = L[i-1] + (X[i]-X[i-1])*W[i-1];
        }

        for( int i = 0; i <= K; i++ )
            for( int j = 0; j <= N; j++ )
                dp[i][j] = 1LL << 60, O[i][j] = 0;

        dp[0][0] = 0;
        for( int i = 1; i <= N; i++ )
            dp[1][i] = costo(1,i), O[1][i] = 1;

        int opt = 0;
        for( int k = 2; k <= K; k++ ){
            for( int i = N; i >= k; i-- ){
                opt = (i == N)?N:O[k][i+1];
                for( int j = max((int)O[k-1][i],k); j <= opt; j++ )
                    if( dp[k][i] > dp[k-1][j-1] + costo(j,i) )
                        dp[k][i] = dp[k-1][j-1] + costo(j,i), O[k][i] = j;
            }
        }
        cout << dp[K][N] << '\n';
    }
    return 0;
}

///vers menos memoria
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 1003;
int N, K;
ll L[maxn], X[maxn], W[maxn], dp[2][maxn], O[2][maxn];
int now;
inline ll costo( int l, int r ){
    ll ret = L[r] -  (L[l] + (X[r]-X[l])*W[l-1]);
    return ret;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    #ifdef acm
    freopen("a.in","r",stdin);
    #endif // acm

    while ( cin >> N >> K ){
        for( int i = 1; i <= N; i++ )
            cin >> X[i] >> W[i], W[i] += W[i-1];

        L[1] = 0;
        for( int i = 2; i <= N; i++ ){
            L[i] = L[i-1] + (X[i]-X[i-1])*W[i-1];
        }

        for( int i = 1; i <= N; i++ )
            dp[1][i] = costo(1,i), O[1][i] = 1;

        int opt = 0;
        now = 1;
        for( int k = 2; k <= K; k++ ){
            now ^= 1;
            for( int i = N; i >= k; i-- ){
                dp[now][i] = 1LL << 60;
                opt = (i == N)?N:O[now][i+1];
                for( int j = max((int)O[now^1][i],k); j <= opt; j++ )
                    if( dp[now][i] > dp[now^1][j-1] + costo(j,i) )
                        dp[now][i] = dp[now^1][j-1] + costo(j,i), O[now][i] = j;
            }
        }
        cout << dp[now][N] << '\n';
    }
    return 0;
}

