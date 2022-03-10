//Dado un radio R encontrar la mayor ctdad de ptos dentro de un circulo con ese radio
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2003;
typedef double db;
int N;
db R;
db X[maxn], Y[maxn];
db sq( db x ){
    return x*x;
}
db dist( int a, int b ){
    return sqrt( sq(X[a]-X[b]) + sq(Y[a]-Y[b]) );
}

db area( db a, db b, db c ){
    db sp = (a+b+c)/2.;
    return sqrt( sp*(sp-a)*(sp-b)*(sp-c) );
}

struct dos{
    db ang;
    int id, iof;
}I[2*maxn];

set<int>S;
int solve( ){
    db pi = 2*acos(0);
    int ret = 0;
    for( int i = 1; i <= N; i++ ){
        int c = 0;
        for( int j = 1; j <= N; j++ ){
            if( i == j )continue;
            db d = dist(i,j);
            if( d > 2*R )continue;
            db alpha = atan2( Y[j]-Y[i], X[j]-X[i] );
            db A = area(R,R,d);
            db beta = asin((2*A)/(R*d));
            db ini = alpha-beta;
            //if( ini < 0 )ini += 2*pi;
            db fin = alpha+beta;
            //if( fin > 2*pi )fin -= 2*pi;
            I[++c] = dos{ini,j,1};
            I[++c] = dos{fin,j,-1};
        }

        S.clear();
        sort(I+1,I+c+1,[]( const dos &s1, const dos &s2){
             if( s1.ang != s2.ang )return s1.ang < s2.ang;
             return s1.iof > s2.iof;
        });

        int mc = 0;
        for( int j = 1; j <= c; j++ ){
            if( I[j].iof == 1 ){
                S.insert(I[j].id);
            }
            mc = max(mc, (int)S.size());
            if( I[j].iof == -1 ){
                if( S.find(I[j].id) != S.end() )
                    S.erase(S.find(I[j].id));
            }
        }

        for( int j = 1; j <= c; j++ ){
            if( I[j].iof == 1 ){
                S.insert(I[j].id);
            }
            mc = max(mc, (int)S.size());
            if( I[j].iof == -1 ){
                if( S.find(I[j].id) != S.end() )
                    S.erase(S.find(I[j].id));
            }
        }
        ret = max(ret,mc+1);
    }
    return ret;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    #ifdef acm
    freopen("a.in","r",stdin);
    #endif // acm

    while( cin >> N >> R && (N+R) ){
        for( int i = 1; i <= N; i++ )
            cin >> X[i] >> Y[i];

        cout << "It is possible to cover " << solve() << " points.\n";
    }

    return 0;
}