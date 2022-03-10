namespace MaxFlowMinCost{
    #define MAXE 1000005
    #define MAXN 100010
	#define oo 1e9
    int pos, Index[MAXN], In, Fin, NN;///index = -1
    typedef int type_cost;
    typedef pair<type_cost, int> par;
    type_cost Phi[MAXN];
    struct edges{
        int nod, newn, cap, next;
        type_cost cost;
        edges( int a=0,int b=0,int c=0,type_cost d=0,int e=0 ){
            nod = a, newn = b, cap = c, cost = d, next = e;
        }
    }G[MAXE];
    void initialize( int cnod, int source, int sink ){
        In = source, Fin = sink, NN = cnod;
        memset( Index, -1, sizeof(Index) );
        pos = 0;
    }
    ///nod, newn, cap, cost
    void insertar( int a, int b, int c, type_cost d ){
        G[pos] = edges( a, b, c, d, Index[a] );
        Index[a] = pos ++;
        G[pos] = edges( b, a, 0, -d, Index[b] );
        Index[b] = pos ++;
    }
    priority_queue<par, vector<par>, greater<par> >Qp;
    int F[MAXN], parent[MAXN];
    type_cost dist[MAXN];
    par Max_Flow_Min_Cost( ){
        int FlowF = 0;
        type_cost CostF = 0;
        int	nod, newn, flow;
        type_cost newc, cost;
		memset( Phi, 0, sizeof(Phi) );
        for( ; ; ){
            fill( F, F + 1 + NN, 0 );
            fill( dist, dist + 1 + NN, oo );
            F[In] = oo, dist[In] = 0;
            Qp.push( par( 0, In ) );
            while( !Qp.empty() ){
                nod = Qp.top().second, cost = Qp.top().first;
                Qp.pop();
                flow = F[nod];
                for( int i = Index[nod]; i != -1; i = G[i].next ){
                    newn = G[i].newn;
                    newc = cost + G[i].cost + Phi[nod] - Phi[newn];
                    if( G[i].cap > 0 && dist[newn] > newc ){
                        dist[newn] = newc;
                        F[newn] = min( flow, G[i].cap );
                        parent[newn] = i;
                        Qp.push( par( newc, newn ) );
                    }
                }
            }
            if( F[Fin] <= 0 ) break;
            CostF += (( dist[Fin] + Phi[Fin] ) * F[Fin] );
            FlowF += F[Fin];
            for( int i = In; i <= Fin; i ++ )
                if( F[i] ) Phi[i] += dist[i];
            nod = Fin;
            while( nod != In ){
                G[parent[nod]].cap -= F[Fin];
                G[parent[nod]^1].cap += F[Fin];
                nod = G[parent[nod]].nod;
            }
        }
        return par( CostF, FlowF );
    }
}