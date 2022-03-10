//.............SQRT Descomposition............//
int sq;
int N, Q;

struct dos{
    long long val;
    int id;
    dos( long long a = 0, int b = 0){
        val = a, id = b;
    }
    bool operator<( const dos &x )const
    {
        return val < x.val;
    }
}P[1003][1003];

long long A[1000006];
int tam[1003];

void update( int a, long long x )
{
    int ba = a/sq;
    for( int i = 0; i < tam[ba]; i++ )
        if( P[ba][i].id == a )
        {
            P[ba][i].val = x;
            break;
        }
    sort(P[ba],P[ba]+tam[ba]);
}

int query( int a, int b, int x )
{
    int ba = a/sq;
    int bb = b/sq;
    int sol = 0;
    if( ba == bb )
    {
        for( int i = 0; i < tam[ba]; i++ )
            if( P[ba][i].id >= a && P[ba][i].id <= b && P[ba][i].val <= x )
                sol ++;
        return sol;
    }

    for( int i = 0; i < tam[ba]; i++ )
        if( P[ba][i].id >= a && P[ba][i].val <= x )
            sol++;
    for( int i = 0; i < tam[bb]; i++ )
        if( P[bb][i].id <= b && P[bb][i].val <= x )
            sol ++;
    for( int i = ba+1; i < bb; i++ )
        sol += upper_bound(P[i],P[i]+tam[i],dos(x,1e7))-P[i];
    return sol;
}

int main()
{
    cin.tie(0);
	ios_base::sync_with_stdio(0);


    cin >> N >> Q;

    for( int i = 0; i < N; i++ )
        cin >> A[i];

    sq = sqrt(N);
    for( int i = 0; i < N; i++ )
        P[i/sq][i%sq] = dos(A[i],i), tam[i/sq]++;

    for( int i = 0; i <= (N-1)/sq; i++ )
        sort(P[i],P[i]+tam[i]);

    char c;
    int a, b;
    long long x;

    while( Q-- )
    {
        cin >> c;
        if( c == 'C' )
        {
            cin >> a >> x;
            update(a-1,x);
        }
        else
        {
            cin >> a >> b >> x;
            cout << query(a-1,b-1,x) << '\n';
        }
    }
    return 0;
}
